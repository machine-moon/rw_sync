cmake_minimum_required(VERSION 3.28)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the C and C++ compilers to clang if not already set
if(NOT CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "/usr/bin/clang")
endif()

if(NOT CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()

# Set the project name
project(zuper VERSION 1.0 LANGUAGES CXX)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Turn off compiler-specific extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific settings
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # Use libc++ with Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Use libstdc++ with GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
endif()

# Define compiler flags for different build types
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Werror -pedantic -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -Wall -Wextra -Werror -pedantic")

# Find all source files
file(GLOB projectSources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${projectSources})

# Include header files
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
