#ifndef TNET_THREAD_H
#define TNET_THREAD_H

#include <tnet/common/Common.h>
#include <pthread.h>
#include <tr1/memory>
#include <tr1/functional>

TNET_BEGIN_NAMESPACE(util);

class Thread;
typedef std::tr1::shared_ptr<Thread> ThreadPtr;

class Thread
{
public:
    static ThreadPtr createThread(const std::tr1::function<void ()>& threadFunction);
private:
    static void* threadWrapperFunction(void* arg);
    
public:
    pthread_t getId() const {return _id;}
    void join() {
        if (_id) {
            int ret = pthread_join(_id, NULL);
            (void) ret; assert(ret == 0);
        }
        _id = 0;
    }
public:
    ~Thread() {
        join();
    }
private:
    Thread() {_id = 0;} 
    pthread_t _id;
};


TNET_END_NAMESPACE(util);

#endif //TNET_THREAD_H
