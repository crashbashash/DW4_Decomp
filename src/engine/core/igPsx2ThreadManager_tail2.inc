void igPsx2ThreadManager_InitDefaults(igPsx2ThreadManagerView *self) {
    igResult created;
    igSemaphoreView *semaphore;

    semaphore = self->_sema;
    created = semaphore->Create();
}

void igPsx2ThreadManager_CreateGlobal(void) {
    ((void * *)g_threadManager)[0] = igThreadManager_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    igSmartPointer<igPsx2ThreadView> added(((igPsx2ThreadView *)igThread_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)))));
    added.get()->_isMaster = 1;
    added.get()->AdoptCurrentThread();
    g_threadManager[0]->AddThread(added.get());
}

void igPsx2ThreadManager_DestroyGlobal(void) {
    igObject *manager;
    igObject *o;

    manager = (igObject *)g_threadManager[0]->GetCurrentThread();
    g_threadManager[0]->RemoveThread((igPsx2ThreadView *)manager);
    manager->_refCount = (int)((int) manager->_refCount - 1);
    if (((unsigned long long) ((long long) (int) manager->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(manager);
    }
    o = (igObject *)((void * *)g_threadManager)[0];
    o->_refCount = (int) o->_refCount - 1;
    if (((unsigned long long) ((long long) (int) o->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(o);
    }
    ((void * *)g_threadManager)[0] = (void *)(0);
}

