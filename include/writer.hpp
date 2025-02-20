#ifndef WRITER_HPP
#define WRITER_HPP

#include <mutex>
#include <semaphore>

class Writer {
public:
    Writer();
    void operator()();

private:
    static std::mutex rw_mutex;
    static std::counting_semaphore<1> write_semaphore;
};

#endif // WRITER_HPP
