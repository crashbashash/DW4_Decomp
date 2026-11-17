#include "dw4/eekernel.h"
#include "dw4/newlib_mallocr.h"

extern int __malloc_lock_owner;
extern int call_count;
extern int __sce_sema_id;

void __malloc_lock(struct _reent *ptr)
{
    int thread = GetThreadId();

    if (__malloc_lock_owner == thread) {
        call_count++;
        return;
    }
    WaitSema(__sce_sema_id);
    __malloc_lock_owner = thread;
    call_count++;
}

void __malloc_unlock(struct _reent *ptr)
{
    if (--call_count == 0) {
        __malloc_lock_owner = -1;
        SignalSema(__sce_sema_id);
    }
}
