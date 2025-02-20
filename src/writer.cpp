#include "../include/writer.hpp"
#include <chrono>
#include <iostream>
#include <thread>

std::mutex Writer::rw_mutex;
std::counting_semaphore<1> Writer::write_semaphore(1);

Writer::Writer() {}

void Writer::operator()() {
    while (true) {
        write_semaphore.acquire(); // Writer locks the semaphore

        // Critical section for writer
        {
            std::lock_guard<std::mutex> lock(rw_mutex);
            std::cout << "Writer is writing." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate writing
        }

        write_semaphore.release(); // Writer unlocks the semaphore

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate time between writes
    }
}
