#include "custom_mutex.hpp"

std::mutex custom_mutex::_mutex {};

custom_mutex::custom_mutex()
{

}

void custom_mutex::lock()
{
    if (!isLocked)
    {
        _mutex.lock();
        isLocked = true;
    }
}

void custom_mutex::unlock()
{
    if (isLocked)
    {
        isLocked = false;
        _mutex.unlock();
    }
}
