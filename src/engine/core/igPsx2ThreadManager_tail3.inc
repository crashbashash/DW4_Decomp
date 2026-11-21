int igPsx2ThreadManager_GetCurrentThread(igPsx2ThreadManager *self) {
    int savedPriority;
    int thread;
    int threadId;

    threadId = GetThreadId();
    savedPriority = ChangeThreadPriority(threadId, 1);
    thread = igObjectList_FindByIntField((igTDataList<int> *)self->_threadList, (igMetaField *)g_igPsx2Thread_threadIDField, GetThreadId());
    ChangeThreadPriority(threadId, savedPriority);
    return thread;
}

void igPsx2ThreadManager_FinishThread(igPsx2ThreadManagerView *manager, igPsx2ThreadView *thread) {
    igResult signalled;
    igSemaphoreView *done;

    manager->RemoveThread(thread);
    int *tid = &thread->_threadID;
    ChangeThreadPriority(*tid, 1);
    *tid = -1;
    done = thread->_threadDoneSema;
    signalled = done->Signal();
    thread->_refCount = (int)((int) (thread->_refCount - 1));
    if (((unsigned long long) ((long long) (int) thread->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(thread);
    }
    ExitDeleteThread();
}

void igPsx2ThreadManager_AddThread(igPsx2ThreadManagerView *self, igPsx2ThreadView *thread) {
    int prio; igTDataList<igPsx2ThreadView *> *lst; int n; int id;
    thread->_refCount = thread->_refCount + 1;
    id = GetThreadId();
    prio = ChangeThreadPriority(id, 1);
    lst = self->_threadList;
    n = lst->_count;
    if (n < lst->_capacity) {
        lst->_count = lst->count() + 1;
    } else {
        ((Gap::Core::igDataList *)lst)->resizeAndSetCount(n + 1, 4);
    }
    lst->_data[n] = thread;
    ChangeThreadPriority(id, prio);
}

void igPsx2ThreadManager_RemoveThread(igPsx2ThreadManagerView *self, igPsx2ThreadView *thread) {
    int i;
    int old;
    igTDataList<igPsx2ThreadView *> *list;
    int tid;
    tid = GetThreadId();
    old = ChangeThreadPriority(tid, 1);
    i = (list = self->_threadList)->find(thread);
    if (i >= 0) {
        List_RemoveWordAt((igDataList *)list, i);
    }
    ChangeThreadPriority(tid, old);
}

int Memory_GetAllocatorOrDefault(int extra0) {
    int r = ((int)Memory_GetAllocatorBySelector(extra0));
    if (r != 0) return r;
    return ((int)Memory_GetDefaultAllocator());
}

void *Memory_AllocateAligned16(unsigned int size, int selector) {
    igMemoryPoolView *allocator;

    allocator = (igMemoryPoolView *)Memory_GetAllocatorOrDefault(selector);
    return allocator->AllocateAligned(size, 0x10);
}

void Memory_FreeToSelector(void *block, int selector) {
    igMemoryPoolView *allocator;

    allocator = (igMemoryPoolView *)Memory_GetAllocatorOrDefault(selector);
    allocator->Free(block);
}

void *Memory_ReallocateAligned16(void *block, unsigned int size, int selector) {
    igMemoryPoolView *allocator;

    allocator = (igMemoryPoolView *)Memory_GetAllocatorOrDefault(selector);
    return allocator->ReallocateAligned(block, size, 0x10);
}

int igPsx2ThreadManager_GetMeta(void) {
    return (int)g_igPsx2ThreadManager_metaObject;
}

