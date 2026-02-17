cmake_minimum_required(VERSION 3.20)
project(c2x64 LANGUAGES CXX)

# ---- Compiler / build settings ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)  # GNU++20 for MinGW; set OFF if you want strict -std=c++20
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Main compiler executable ----
add_executable(c2x64
  src/main.cpp
)

# ---- Tests (doctest single header) ----
# Expect: external/doctest/doctest.h
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/external/doctest/doctest.h")
  message(FATAL_ERROR
    "Missing doctest header.\n"
    "Download doctest/doctest.h (Raw) and save it as:\n"
    "  external/doctest/doctest.h"
  )
endif()

add_executable(c2x64_tests
  tests/test_sanity.cpp
)

target_include_directories(c2x64_tests PRIVATE
  "${CMAKE_SOURCE_DIR}/external/doctest"
)

# ---- MinGW: avoid runtime DLL dependency during test execution ----
# This links libstdc++ and libgcc statically, so CTest won't fail with 0xc0000139.
if (MINGW)
  target_link_options(c2x64 PRIVATE -static-libstdc++ -static-libgcc)
  target_link_options(c2x64_tests PRIVATE -static-libstdc++ -static-libgcc)
endif()

# ---- CTest ----
enable_testing()
add_test(NAME c2x64_sanity COMMAND c2x64_tests)
