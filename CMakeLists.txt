cmake_minimum_required(VERSION 3.5)

project(Tic-tac-toe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W4 /WX)
  if(CMAKE_BUILD_TYPE MATCHES "Debug")
      add_compile_options(/O0)
  else()
      add_compile_options(/O2)
  endif()
else() #gcc or clang
  add_compile_options(
      -Wall #warnings
      -Wextra #more warnings
      -Wno-long-long #more warnings
      -Wpedantic #more warnings
      -Werror=format-security #Reject potentially unsafe format string arguents
      -D_FORTIFY_SOURCE=2 #Run-time buffer overflow detection
      -D_GLIBCXX_ASSERTIONS #Run-time bounds checking for C++ strings and containers
      -grecord-gcc-switches #Store compiler flags in debugging information
      -pipe #Avoid temporary files, speeding up builds
    )
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        message("Debug mode")
        add_compile_options(
            -O #Recommended optimizations for debugging
            -g #Generate debugging information
        )
    else()
        message("Realize mode")
        add_compile_options(
            -O2 #Recommended optimizations for realize
        )
    endif()
endif()


add_subdirectory(src)
