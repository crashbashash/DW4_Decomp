int igPsx2ThreadManager_GetCurrentThread(igPsx2ThreadManager *arg0) {
    int temp_s2;
    int temp_s1;
    int temp_v0;

    temp_v0 = GetThreadId();
    temp_s2 = ChangeThreadPriority(temp_v0, 1);
    temp_s1 = igObjectList_FindByIntField((igTDataList<int> *)arg0->_threadList, (igMetaField *)DAT_00586ca8[0], GetThreadId());
    ChangeThreadPriority(temp_v0, temp_s2);
    return temp_s1;
}

void igPsx2ThreadManager_FinishThread(igPsx2ThreadManagerView *manager, igPsx2ThreadView *thread) {
    igResult signalled;
    igSemaphoreView *done;

    manager->removeThread(thread);
    int *tid = &thread->_threadID;
    ChangeThreadPriority(*tid, 1);
    *tid = -1;
    done = thread->_threadDoneSema;
    signalled = done->signal();
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
        List_Resize(lst, n + 1, 4);
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

void Memory_AllocateAligned16(int arg0, int arg1) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorOrDefault(arg1)));
    ((igMemoryPoolView *)(temp_v0))->AllocateAligned(arg0, 0x10);
}

void Memory_FreeToSelector(int arg0, int arg1) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorOrDefault(arg1)));
    ((igMemoryPoolView *)(temp_v0))->Free((void *)arg0);
}

void Memory_ReallocateAligned16(int arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorOrDefault(arg2)));
    ((igMemoryPoolView *)(temp_v0))->ReallocateAligned((void *)arg0, arg1, 0x10);
}

int igPsx2ThreadManager_GetMeta(void) {
    return ((int *)g_igPsx2ThreadManager_metaObject)[0];
}

