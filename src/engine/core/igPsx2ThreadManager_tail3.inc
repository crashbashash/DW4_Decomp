int Gap__Core__igPsx2ThreadManager__vfunc_23(igPsx2ThreadManager *arg0) {
    int temp_s2;
    int temp_s1;
    int temp_v0;

    temp_v0 = GetThreadId();
    temp_s2 = ChangeThreadPriority(temp_v0, 1);
    temp_s1 = FUN_002feeb0((L_2feeb0 *)arg0->_threadList, (K *)DAT_00586ca8[0], GetThreadId());
    ChangeThreadPriority(temp_v0, temp_s2);
    return temp_s1;
}

void FUN_003304e0(void **arg0, igPsx2Thread *arg1) {
    DW4SR4 sp3C;
    void **temp_a1;

    ((DW4VC_100_0 *)(arg0))->vX();
    int *tid = &arg1->_threadID;
    ChangeThreadPriority(*tid, 1);
    *tid = -1;
    temp_a1 = (void **)(arg1->_threadDoneSema);
    sp3C = ((DW4VCSR_124_0 *)(temp_a1))->vX();
    arg1->_refCount = (int)((int) (arg1->_refCount - 1));
    if (((unsigned long long) ((long long) (int) arg1->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(arg1);
    }
    ExitDeleteThread();
}

static inline int count_of_330570(const struct List_330570 *list) { return list->count; }

void Gap__Core__igPsx2ThreadManager__vfunc_24(struct Mgr_330570 *arg0, struct Obj_330570 *arg1) {
    int prio; struct List_330570 *lst; int n; int id;
    arg1->refs = arg1->refs + 1;
    id = GetThreadId();
    prio = ChangeThreadPriority(id, 1);
    lst = arg0->list;
    n = lst->count;
    if (n < lst->cap) {
        lst->count = count_of_330570(lst) + 1;
    } else {
        List_Resize(lst, n + 1, 4);
    }
    lst->items[n] = (int)arg1;
    ChangeThreadPriority(id, prio);
}

void Gap__Core__igPsx2ThreadManager__vfunc_25(Psx2ThreadTable *self, ManagedThread *thread) {
    int i;
    int old;
    igTDataList<ManagedThread *> *list;
    int tid;
    tid = GetThreadId();
    old = ChangeThreadPriority(tid, 1);
    i = (list = self->_threads)->find(thread);
    if (i >= 0) {
        List_RemoveWordAt((L_2d6cf0 *)list, i);
    }
    ChangeThreadPriority(tid, old);
}

int FUN_003306f0(int extra0) {
    int r = ((int)Memory_GetAllocatorBySelector(extra0));
    if (r != 0) return r;
    return ((int)Memory_GetDefaultAllocator());
}

void FUN_00330730(int arg0, int arg1) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)FUN_003306f0(arg1)));
    ((DW4VC_220_2 *)(temp_v0))->vX((int)(arg0), (int)(0x10));
}

void FUN_00330770(int arg0, int arg1) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)FUN_003306f0(arg1)));
    ((DW4VC_264_1 *)(temp_v0))->vX((int)(arg0));
}

void FUN_003307b0(int arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)FUN_003306f0(arg2)));
    ((DW4VC_236_3 *)(temp_v0))->vX((int)(arg0), (int)(arg1), (int)(0x10));
}

int Gap__Core__igPsx2ThreadManager__vfunc_22(void) {
    return ((int *)g_igPsx2ThreadManager_metaObject)[0];
}

