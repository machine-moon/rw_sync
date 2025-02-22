#ifndef READER_HPP
#define READER_HPP

#include <cstdint>
#include <mutex>
#include <semaphore>
#include <sys/types.h>
#include "shared_data.hpp"

template<typename T>
class Reader {
public:
    Reader(uint8_t id, SharedData<T> &shared_data);
    void operator()();

private:
    uint8_t id;
    SharedData<T> &data;
    std::binary_semaphore &turn;
    static std::mutex readers_mutex;
    static uint8_t readers;
    uint8_t read_count;
};

#endif // READER_HPP
