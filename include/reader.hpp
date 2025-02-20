#ifndef READER_HPP
#define READER_HPP

#include <mutex>
#include <semaphore>

class Reader {
public:
    Reader(int id);
    void operator()();

private:
    int id;
    static std::mutex rw_mutex;
    static std::mutex read_count_mutex;
    static std::counting_semaphore<1> write_semaphore;
    static int read_count;
};

#endif // READER_HPP
