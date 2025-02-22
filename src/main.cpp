#include <iostream>
#include <thread>
#include <vector>
#include "../include/config.hpp"
#include "../include/reader.hpp"
#include "../include/shared_data.hpp"
#include "../include/writer.hpp"

int main() {
    // Load environment variable as int
    auto readers_count = Config::get_env<int>("READERS_COUNT");
    if (readers_count) {
        std::cout << "READERS_COUNT (int): " << *readers_count << std::endl;
    } else {
        std::cout << "READERS_COUNT is not set." << std::endl;
        // give a default value
        readers_count = 1;
    }

    auto writers_count = Config::get_env<int>("WRITERS_COUNT");
    if (writers_count) {
        std::cout << "WRITERS_COUNT (int): " << *writers_count << std::endl;
    } else {
        std::cout << "WRITERS_COUNT is not set." << std::endl;
        // give a default value
        writers_count = 1;
    }


    SharedData<int> shared_data(std::string("log.txt"));

    std::vector<std::thread> threads;
    for (int i = 0; i < readers_count; ++i) {
        threads.emplace_back(Reader<int>((i + 1), shared_data));
    }
    for (int i = 0; i < writers_count; ++i) {
        threads.emplace_back(Writer<int>((i + *readers_count), shared_data));
    }

    for (auto &thread: threads) {
        thread.join();
    }

    std::cout << "All threads have finished." << std::endl;
    // No need to delete stack-allocated shared_data
    return 0;
}
