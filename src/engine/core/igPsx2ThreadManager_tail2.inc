void igPsx2ThreadManager_InitDefaults(igPsx2ThreadManagerView *self) {
    igResult created;
    igSemaphoreView *semaphore;

    semaphore = self->_sema;
    created = semaphore->Create();
}

void igPsx2ThreadManager_CreateGlobal(void) {
    (*(void * *)&g_threadManager) = igThreadManager_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    igSmartPointer<igPsx2ThreadView> added(((igPsx2ThreadView *)igThread_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)))));
    added.get()->_isMaster = 1;
    added.get()->AdoptCurrentThread();
    g_threadManager->AddThread(added.get());
}

void igPsx2ThreadManager_DestroyGlobal(void) {
    igObject *manager;
    igObject *o;

    manager = (igObject *)g_threadManager->GetCurrentThread();
    g_threadManager->RemoveThread((igPsx2ThreadView *)manager);
    manager->release();
    o = (igObject *)(*(void * *)&g_threadManager);
    o->release();
    (*(void * *)&g_threadManager) = (void *)(0);
}

