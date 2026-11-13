void Gap__Core__igPsx2ThreadManager__vfunc_11(igPsx2ThreadManager *self) {
    DW4SR4 discarded_result;
    void **semaphore;

    semaphore = (void **)(self->_sema);
    discarded_result = ((DW4VCSR_92_0 *)(semaphore))->vX();
}

void FUN_0030e480(void) {
    ((void * *)g_threadManager)[0] = FUN_002b7b70(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    igSmartPointer<R_30e480> added(((R_30e480 *)FUN_002b7f40(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)))));
    added.get()->f44 = 1;
    ((VC_220_0 *)added.get())->vX();
    ((VC_96_1_30e480 *)((void * *)g_threadManager)[0])->vX(added.get());
}

void FUN_0030e540(void) {
    igObject *temp_v0;
    igObject *o;

    temp_v0 = (igObject *)(((DW4VC_92_0 *)(((char *)(((void * *)g_threadManager)[0]) + 0)))->vX());
    ((DW4VC_100_1 *)(((char *)(((void * *)g_threadManager)[0]) + 0)))->vX((int)(temp_v0));
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

