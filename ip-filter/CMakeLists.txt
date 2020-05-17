add_executable(ip-filter)

target_sources(ip-filter PRIVATE src/main.cpp)

install(TARGETS ip-filter RUNTIME DESTINATION bin)