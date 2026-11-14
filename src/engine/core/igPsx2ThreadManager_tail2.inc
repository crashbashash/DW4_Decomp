void Gap__Core__igPsx2ThreadManager__vfunc_11(igPsx2ThreadManagerView *self) {
    igResult created;
    igSemaphoreView *semaphore;

    semaphore = self->_sema;
    created = semaphore->create();
}

void FUN_0030e480(void) {
    ((void * *)g_threadManager)[0] = FUN_002b7b70(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    igSmartPointer<igPsx2ThreadView> added(((igPsx2ThreadView *)FUN_002b7f40(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)))));
    added.get()->_isMaster = 1;
    added.get()->adoptCurrentThread();
    g_threadManager[0]->addThread(added.get());
}

void FUN_0030e540(void) {
    igObject *temp_v0;
    igObject *o;

    temp_v0 = (igObject *)g_threadManager[0]->getCurrentThread();
    g_threadManager[0]->removeThread((igPsx2ThreadView *)temp_v0);
    temp_v0->_refCount = (int)((int) temp_v0->_refCount - 1);
    if (((unsigned long long) ((long long) (int) temp_v0->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    o = (igObject *)((void * *)g_threadManager)[0];
    o->_refCount = (int) o->_refCount - 1;
    if (((unsigned long long) ((long long) (int) o->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(o);
    }
    ((void * *)g_threadManager)[0] = (void *)(0);
}

