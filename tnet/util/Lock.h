#ifndef TNET_LOCK_H
#define TNET_LOCK_H

#include <tnet/common/Common.h>
#include <pthread.h>
#include <sys/time.h>

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


class ThreadCond : public ThreadMutex
{
public:
    ThreadCond() {
        pthread_cond_init(&_cond, NULL);
    }

    ~ThreadCond() {
        pthread_cond_destroy(&_cond);
    }

    timespec getTimespec(int64_t usec) {
        timespec tspec;
        struct timeval tval;
        gettimeofday(&tval, NULL);
        int64_t uTime  = tval.tv_sec * 1000000LL + tval.tv_usec;
        uTime = uTime + usec;
        tspec.tv_sec = uTime / 1000000;
        tspec.tv_nsec = (uTime % 1000000) * 1000;
        return tspec;
    }

    int wait(int64_t usec = 0)
    {
        int ret = 0; 
        if (usec <= 0) {
            ret = pthread_cond_wait(&_cond, &_mutex);
        } else {
            timespec ts = getTimespec(usec);
            ret = pthread_cond_timedwait(&_cond, &_mutex, &ts);
        }
        
        return ret;
    }
    
    int signal() {
        return pthread_cond_signal(&_cond);
    }

    int broadcast() {
        return pthread_cond_broadcast(&_cond);
    }

protected:
    pthread_cond_t  _cond;
};


TNET_TYPEDEF_PTR(ThreadMutex);

TNET_END_NAMESPACE(util);

#endif //TNET_LOCK_H
