#include "../include/shared_data.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

template<typename T>
SharedData<T>::SharedData(const std::string &logfile) : data(10, 0), size(10), turn(1), logfile(logfile) {}

template<typename T>
SharedData<T>::~SharedData() {
    std::cout << "Writing to log file." << std::endl;
    std::string logFilePath = "logs/" + this->logfile;
    std::filesystem::create_directories("logs");
    int counter = 1;
    while (std::ifstream(logFilePath)) {
        logFilePath = "logs/" + this->logfile + "_" + std::to_string(counter);
        counter++;
    }
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);
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
