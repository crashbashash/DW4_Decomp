/* p2LockVu0, held out of src/engine/p2vu0.c: it reproduces only as C++, where the const accessor
 * makes the second load of the lock semaphore, and C++ breaks p2InitVu0's struct copy. */
extern "C" {
#include "dw4/eekernel.h"
#include "dw4/p2timer.h"

extern int p2BlockedSema;
}

/* The VU0 lock: its semaphore and the tag of the code holding it. */
struct p2Vu0Lock {
    int sema;
    int f4;
    const char *owner;
    int semaphore() const { return sema; }
};

extern "C" p2Vu0Lock p2Vu0LockState;

/* Waits for the VU0 lock, takes it for `owner` (a trace tag such as "p2lighting") and adds the time
 * waited to p2Vu0LockWaitTime. */
extern "C" void p2LockVu0(const char *owner) {
    long long start;
    long long end;

    p2ReadClock(&start);
    p2BlockedSema = p2Vu0LockState.semaphore();
    WaitSema(p2Vu0LockState.sema);
    p2BlockedSema = -1;
    p2ReadClock(&end);
    p2Vu0LockState.owner = owner;
    p2Vu0LockWaitTime += (long long)((end - start) << 32) >> 32;
}
