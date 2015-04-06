#ifndef TNET_LOCK_H
#define TNET_LOCK_H

#include <tnet/common/Common.h>
#include <pthread.h>

TNET_BEGIN_NAMESPACE(util);

class ThreadMutex
{
public:
    ThreadMutex(const pthread_mutexattr_t *mta = NULL) {
        pthread_mutex_init(&_mutex, mta);
    }
    
    ~ThreadMutex() {
        pthread_mutex_destroy(&_mutex);
    }
    
    int lock() {
        return pthread_mutex_lock(&_mutex);
    }

    int trylock () {
        return pthread_mutex_trylock(&_mutex);
    }

    int unlock() {
        return pthread_mutex_unlock(&_mutex);
    }
private:
    ThreadMutex(const ThreadMutex&);
    ThreadMutex& operator = (const ThreadMutex&);
protected:
    pthread_mutex_t _mutex;
};

class ScopedLock
{
private:
    ThreadMutex &_lock;
private:
    ScopedLock(const ScopedLock &);
    ScopedLock& operator= (const ScopedLock &);
    
public:
    explicit ScopedLock(ThreadMutex& lock) : _lock(lock) {
        int ret = _lock.lock();
        assert(ret == 0); (void) ret;
    }

    ~ScopedLock() {
        int ret = _lock.unlock();
        assert(ret == 0); (void) ret;
    }
};

TNET_TYPEDEF_PTR(ThreadMutex);

TNET_END_NAMESPACE(util);

#endif //TNET_LOCK_H
