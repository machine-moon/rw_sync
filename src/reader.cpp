#include "../include/reader.hpp"
#include <chrono>
#include <iostream>
#include <thread>


std::mutex Reader::rw_mutex;
std::mutex Reader::read_count_mutex;
std::counting_semaphore<1> Reader::write_semaphore(1);
int Reader::read_count = 0;

Reader::Reader(int id) : id(id) {}

void Reader::operator()() {
    while (true) {
        // Entry section for readers
        {
            std::unique_lock<std::mutex> lock(read_count_mutex);
            read_count++;
            if (read_count == 1) {
                write_semaphore.acquire(); // First reader locks the writer
            }
        }

        // Critical section for readers
        {
            std::lock_guard<std::mutex> lock(rw_mutex);
            std::cout << "Reader " << id << " is reading." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate reading
        }

        // Exit section for readers
        {
            std::lock_guard<std::mutex> lock(read_count_mutex);
            read_count--;
            if (read_count == 0) {
                write_semaphore.release(); // Last reader unlocks the writer
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between reads
    }
}
