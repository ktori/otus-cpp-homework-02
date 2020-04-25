cmake_minimum_required(VERSION 3.12)

project(ip-filter VERSION 0.2.0)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest EXCLUDE_FROM_ALL)
enable_testing()

if ("$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
    set(BUILD_NUMBER 0 CACHE STRING "Build number")
else ()
    set(BUILD_NUMBER "$ENV{TRAVIS_BUILD_NUMBER}" CACHE STRING "Build number")
endif ()

add_subdirectory(ip-filter)

set(INSTALL_GMOCK OFF)
set(INSTALL_GTEST OFF)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tori@ktori.me)

include(CPack)
