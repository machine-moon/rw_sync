#ifndef SHARED_DATA_HPP
#define SHARED_DATA_HPP

#include <cstddef>
#include <semaphore>
#include <string>
#include <vector>

template<typename T>
class SharedData {
public:
    explicit SharedData(std::string const &logfile);
    ~SharedData();
    size_t getSize() const;
    std::binary_semaphore &getSema();
    T Front() const;
    T Back() const;
    T At(size_t index) const;
    void add(T value);

private:
    std::vector<T> data;
    size_t size;
    std::binary_semaphore turn;
    std::string logfile;
};


#endif // SHARED_DATA_HPP
