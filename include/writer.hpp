#ifndef WRITER_HPP
#define WRITER_HPP

#include <cstdint>
#include <mutex>
#include <semaphore>
#include "shared_data.hpp"

template<typename T>
class Writer {
public:
    Writer(uint8_t id, SharedData<T> &shared_data);
    void operator()();

private:
    uint8_t id;
    SharedData<T> &data;
    std::binary_semaphore &turn;
    static std::mutex rw_mutex;
    uint8_t write_count;
};

#endif // WRITER_HPP
