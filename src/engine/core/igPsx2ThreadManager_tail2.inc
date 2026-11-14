void igPsx2ThreadManager_InitDefaults(igPsx2ThreadManagerView *self) {
    igResult created;
    igSemaphoreView *semaphore;

    semaphore = self->_sema;
    created = semaphore->create();
}

void igPsx2ThreadManager_CreateGlobal(void) {
    ((void * *)g_threadManager)[0] = igThreadManager_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    igSmartPointer<igPsx2ThreadView> added(((igPsx2ThreadView *)igThread_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)))));
    added.get()->_isMaster = 1;
    added.get()->adoptCurrentThread();
    g_threadManager[0]->addThread(added.get());
}

void igPsx2ThreadManager_DestroyGlobal(void) {
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

