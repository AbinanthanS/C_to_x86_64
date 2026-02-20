cmake_minimum_required(VERSION 3.20)
project(c2x64 LANGUAGES CXX)

# ---- Compiler / build settings ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)  # GNU++20 on MinGW; set OFF for strict -std=c++20
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Doctest single-header (vendored) ----
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/external/doctest/doctest.h")
  message(FATAL_ERROR
    "Missing doctest header.\n"
    "Download doctest/doctest.h (Raw) and save it as:\n"
    "  external/doctest/doctest.h"
  )
endif()

# ---- Library containing compiler modules ----
add_library(c2x64_lib
  src/lexer/lexer.cpp
)

target_include_directories(c2x64_lib PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

# ---- Main compiler executable ----
add_executable(c2x64
  src/main.cpp
)

target_link_libraries(c2x64 PRIVATE c2x64_lib)

# ---- Tests executable ----
add_executable(c2x64_tests
  tests/test_sanity.cpp
  tests/test_lexer.cpp
)

target_include_directories(c2x64_tests PRIVATE
  "${CMAKE_SOURCE_DIR}/external/doctest"
)

target_link_libraries(c2x64_tests PRIVATE c2x64_lib)

enable_testing()
add_test(NAME c2x64_all COMMAND c2x64_tests)