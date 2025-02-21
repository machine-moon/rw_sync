# Reader-Writer Synchronization

This project demonstrates the classical Reader-Writer problem using C++ threads, mutexes, and semaphores. The goal is to manage concurrent access to a shared resource by multiple readers and a single writer, ensuring data consistency and preventing race conditions.

## Project Structure

- **include/**
    - `reader.hpp`: Header file for the `Reader` class.
    - `writer.hpp`: Header file for the `Writer` class.
- **src/**
    - `main.cpp`: Entry point of the application.
    - `reader.cpp`: Implementation of the `Reader` class.
    - `writer.cpp`: Implementation of the `Writer` class.
- **secrets**
    - Environment variable configuration file.

## Getting Started

### Prerequisites

- C++17 or later
- CMake
- Make

### Building the Project

1. Clone the repository:
        ```sh
        git clone git@github.com:machine-moon/rw_sync.git
        cd rw_sync
        ```

2. Create a build directory and navigate into it:
        ```sh
        mkdir build
        cd build
        ```

3. Run CMake to generate the build files:
        ```sh
        cmake ..
        ```

4. Build the project using Make:
        ```sh
        make
        ```

### Running the Application

1. Set the environment variable for the number of readers:
        ```sh
        export READERS_COUNT=2
        ```

2. Run the application:
        ```sh
        ./rw_sync
        ```

## Code Overview

### Reader Class

The `Reader` class simulates a reader that periodically reads from a shared resource. It uses mutexes and semaphores to ensure safe concurrent access.

### Writer Class

The `Writer` class simulates a writer that periodically writes to a shared resource. It uses a semaphore to ensure exclusive access to the resource.

### Main Function

The `main.cpp` file initializes the readers and writer, starts their threads, and manages their lifecycle.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

