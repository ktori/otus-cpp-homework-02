#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

struct address_ctype : std::ctype<char>
{
	address_ctype() : std::ctype<char>(mask_table().data())
	{
	}

	static std::array<std::ctype_base::mask, 256> mask_table()
	{
		static std::array<std::ctype_base::mask, 256> result{};

		std::copy(classic_table(), classic_table() + result.size(), result.begin());
		result['.'] = space;

		return result;
	}
};

struct address
{
	static constexpr size_t octet_count = 4;

	std::array<uint8_t, octet_count> octets{};
};

struct address_octets_greater_than
{
	inline bool operator()(const address& first, const address& second)
	{
		for (auto i = 0; i < address::octet_count; ++i)
			if (first.octets[i] > second.octets[i])
				return true;

		return false;
	}
};

std::istream& operator>>(std::istream& stream, address& addr)
{
	// Treat '.' as whitespace, save old locale
	auto loc = stream.imbue(std::locale(stream.getloc(), new address_ctype()));

	for (auto& octet : addr.octets)
	{
		if (!stream)
			return stream;

		// If octet is read directly, it's read as a char, not as an 8-bit unsigned integer
		unsigned temp;
		stream >> temp;
		octet = temp;
	}

	// Restore locale
	stream.imbue(loc);

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const address& addr)
{
	for (auto i = 0; i < address::octet_count; ++i)
	{
		stream << static_cast<unsigned>(addr.octets[i]);
		if (i < address::octet_count - 1)
			stream << '.';
	}
	return stream;
}

template<typename ConstIter, typename Pred>
void print_items(std::ostream& stream, ConstIter begin, ConstIter end, Pred predicate)
{
	for (auto it = begin; it != end; ++it)
		if (predicate(*it))
			stream << *it << '\n';
}

template<typename ConstIter>
void print_items(std::ostream& stream, ConstIter begin, ConstIter end)
{
	for (auto it = begin; it != end; it++)
		stream << *it << '\n';
}

int main(int argc, char const* argv[])
{
	try
	{
		std::vector<address> ip_pool{};

		address addr{};
		while (std::cin >> addr)
		{
			ip_pool.push_back(addr);

			// Ignore rest of the line
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::sort(ip_pool.begin(), ip_pool.end(), address_octets_greater_than());

		print_items(std::cout, ip_pool.begin(), ip_pool.end());

		print_items(std::cout, ip_pool.begin(), ip_pool.end(), [](address addr)
		{
		  return addr.octets[0] == 1;
		});

		print_items(std::cout, ip_pool.begin(), ip_pool.end(), [](address addr)
		{
		  return addr.octets[0] == 46 && addr.octets[1] == 70;
		});

		print_items(std::cout, ip_pool.begin(), ip_pool.end(), [](address addr)
		{
		  for (auto octet : addr.octets)
			  if (octet == 46)
				  return true;
		  return false;
		});
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
