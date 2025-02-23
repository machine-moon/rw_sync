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
project(rw_sync VERSION 1.0 LANGUAGES CXX)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Turn off compiler-specific extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
# Set default build type if not specified
IF (NOT DEFAULT_BUILD_TYPE)
  SET(DEFAULT_BUILD_TYPE Release)
ENDIF()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE})
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

# Set executable name if not defined
if(NOT EXECUTABLE_NAME)
  set(EXECUTABLE_NAME ${PROJECT_NAME})
endif()

# Set executable name based on build type
if(CMAKE_BUILD_TYPE STREQUAL DEFAULT_BUILD_TYPE)
  set(EXECUTABLE_NAME ${EXECUTABLE_NAME})
else()
  set(EXECUTABLE_NAME ${EXECUTABLE_NAME}_${CMAKE_BUILD_TYPE})
endif()


# Create executable
add_executable(${EXECUTABLE_NAME} ${projectSources})

# Include header files
target_include_directories(${EXECUTABLE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")



# testing


# Enable testing
enable_testing()

# Fetch Google Test
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

# Add test executable
file(GLOB test_sources tests/*.cpp)
add_executable(testFiles ${test_sources})
target_link_libraries(testFiles gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(testFiles)
