cmake_minimum_required(VERSION 3.5)

project(Tic-tac-toe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W4 /WX /O2)
else()
  add_compile_options(
      -Wall #warnings
      -Wextra #more warnings
      -Wno-long-long #more warnings
      -Wpedantic #more warnings
      -Werror=format-security #Reject potentially unsafe format string arguents
      -D_FORTIFY_SOURCE=2 #Run-time buffer overflow detection
      -D_GLIBCXX_ASSERTIONS #Run-time bounds checking for C++ strings and containers
      -g #Generate debugging information
      -grecord-gcc-switches #Store compiler flags in debugging information
      -O2 #Recommended optimizations
      -pipe #Avoid temporary files, speeding up builds
    )
endif()

add_subdirectory(src)
