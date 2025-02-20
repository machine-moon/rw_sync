#include <iostream>
#include <thread>
#include <vector>
#include "../include/config.hpp"
#include "../include/reader.hpp"
#include "../include/writer.hpp"

int main() {
    // Load environment variable as int
    auto readers_count = Config::get_env<int>("READERS_COUNT");
    if (readers_count) {
        std::cout << "READERS_COUNT (int): " << *readers_count << std::endl;
    } else {
        std::cout << "READERS_COUNT is not set." << std::endl;
    }

    std::vector<std::thread> readers;
    for (int i = 0; i < readers_count; ++i) {
        readers.emplace_back(Reader(i + 1));
    }

    std::thread writer_thread((Writer()));

    for (auto &reader_thread: readers) {
        reader_thread.join();
    }

    writer_thread.join();

    return 0;
}
