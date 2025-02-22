#include "../include/shared_data.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

template<typename T>
SharedData<T>::SharedData(std::string logfile) : data(10, 0), size(10), turn(1), logfile(logfile) {}

template<typename T>
SharedData<T>::~SharedData() {
    std::cout << "Writing to log file." << std::endl;
    std::ofstream logFile(this->logfile, std::ios::out | std::ios::app);
    if (logFile.is_open()) {
        for (const auto &item: this->data) {
            logFile << item << std::endl;
        }
        logFile.close();
    }
    this->data.clear();
    this->size = 0;
    std::cout << "Log file written." << std::endl;
}

template<typename T>
std::vector<T> &SharedData<T>::getData() {
    return this->data;
}

template<typename T>
size_t SharedData<T>::getSize() const {
    return this->size;
}

template<typename T>
std::binary_semaphore &SharedData<T>::getSema() {
    return this->turn;
}

template<typename T>
T SharedData<T>::Front() const {
    return this->data.front();
}

template<typename T>
T SharedData<T>::Back() const {
    return this->data.back();
}

template<typename T>
typename std::vector<T>::const_iterator SharedData<T>::Begin() const {
    return this->data.begin();
}

template<typename T>
typename std::vector<T>::const_iterator SharedData<T>::End() const {
    return this->data.end();
}

template<typename T>
T SharedData<T>::At(size_t index) const {
    if (index >= this->size) {
        throw std::out_of_range("Index out of range");
    }
    return this->data.at(index);
}

template<typename T>
void SharedData<T>::add(T value) {
    this->data.emplace_back(value);
    this->size++;
}


template class SharedData<int>;
template class SharedData<float>;
template class SharedData<double>;
template class SharedData<char>;
