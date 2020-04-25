CMAKE_CACHE=$(find . -type f -name "CMakeCache.txt")

for PART in MAJOR MINOR PATCH
do
  VALUE=$(sed -n 's/CMAKE_PROJECT_VERSION_'"$PART"':STATIC=\(.*\)/\1/p' "$CMAKE_CACHE")
  sed -i 's/VERSION_'"$PART"'/'"$VALUE"'/g' "descriptor.json"
done

VALUE=$(sed -n 's/BUILD_NUMBER:STRING=\(.*\)/\1/p' "$CMAKE_CACHE")
sed -i 's/BUILD_NUMBER/'"$VALUE"'/g' "descriptor.json"