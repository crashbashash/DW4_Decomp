#ifndef DW4_IGTHREAD_H
#define DW4_IGTHREAD_H
#include "dw4/core/igTDataList.h"

struct igThread;
class igPsx2ThreadView;
class igSemaphoreView;
struct igMetaObject;

/* igPsx2ThreadManager: slot 21 finds the calling thread, slots 22 and 23 add and remove a thread. */
class igPsx2ThreadManagerView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual igPsx2ThreadView *GetCurrentThread();
    virtual void AddThread(igPsx2ThreadView *thread);
    virtual void RemoveThread(igPsx2ThreadView *thread);
    unsigned int _refCount;
    igTDataList<igPsx2ThreadView *> *_threadList;
    igSemaphoreView *_sema;
};

extern "C" {
extern igPsx2ThreadManagerView *g_threadManager;

igThread *igThread_Create(int allocator);
void igThread_EnsureRegistered(void);
struct igMetaObject *igThread_GetOrCreateMetaObject(void);
}

#endif
