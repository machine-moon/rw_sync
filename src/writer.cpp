#include "../include/writer.hpp"
#include <chrono>
#include <iostream>
#include <thread>

template<typename T>
std::mutex Writer<T>::rw_mutex;

template<typename T>
Writer<T>::Writer(uint8_t id, SharedData<T> &shared_data) :
    id(id), data(shared_data), turn(this->data.getSema()), write_count(0) {}


template<typename T>
void Writer<T>::operator()() {
    while (true) {
        turn.acquire(); // Writer locks the semaphore

        // Critical section for writer
        {
            std::cout << "Writer is adding their ID." << std::endl;
            data.add(static_cast<T>(this->id));
        }

        turn.release(); // Writer unlocks the semaphore
        this->write_count++;
        if (this->write_count >= this->id) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate time between writes
    }
}

template class Writer<int>;
template class Writer<float>;
template class Writer<double>;
template class Writer<char>;
