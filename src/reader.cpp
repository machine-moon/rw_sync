#include "../include/reader.hpp"
#include <chrono>
#include <iostream>
#include <thread>


template<typename T>
std::mutex Reader<T>::readers_mutex;

template<typename T>
uint8_t Reader<T>::readers = 0;

template<typename T>
Reader<T>::Reader(uint8_t id, SharedData<T> &data) : id(id), data(data), turn(this->data.getSema()) {}

template<typename T>
void Reader<T>::operator()() {
    while (true) {
        // Entry section for readers
        {
            std::unique_lock<std::mutex> lock(readers_mutex);
            readers++;
            if (readers == 1) {
                turn.acquire(); // Readers turn
            }
        }

        {
            std::cout << "Reader " << id << " is reading. " << "Front: " << data.Front() << ", Back: " << data.Back()
                      << ", Size: " << data.getSize() << ", Data: at(0): " << data.At(0) << ", at(1): " << data.At(1)
                      << ", at(2): " << data.At(2) << std::endl;
        }

        // Exit section for readers
        {
            std::lock_guard<std::mutex> lock(readers_mutex);
            readers--;
            if (readers == 0) {
                turn.release(); // Last reader unlocks for writer turn
            }
        }
        this->read_count++;
        if (this->read_count >= this->id) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between reads
    }
}

template class Reader<int>;
template class Reader<float>;
template class Reader<double>;
template class Reader<char>;
