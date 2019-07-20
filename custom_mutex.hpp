#ifndef CUSTOM_MUTEX_HPP
#define CUSTOM_MUTEX_HPP

#include <mutex>

class custom_mutex
{
public:
    custom_mutex();
    void lock();
    void unlock();
protected:

private:
    static std::mutex _mutex;
    bool isLocked { false };
};


#endif // CUSTOM_MUTEX_HPP
