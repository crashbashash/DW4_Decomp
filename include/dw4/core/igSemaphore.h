#ifndef DW4_IGSEMAPHORE_H
#define DW4_IGSEMAPHORE_H

#include "dw4/support/reflected.h"

/* The mutually exclusive lock of alchemy-kit_202309 igCore/igSemaphore.h: constructed on the stack, it
 * obtains the semaphore (a null semaphore is no lock) and releases it with the scope. */
class igScopeLock {
public:
    igScopeLock(Gap::Core::igSemaphore *semaphore) : _semaphore(semaphore) {
        if (_semaphore)
            _semaphore->obtainResource(true);
    }
    ~igScopeLock() {
        if (_semaphore)
            _semaphore->releaseResource();
    }
private:
    Gap::Core::igSemaphore *_semaphore;
};

#endif
