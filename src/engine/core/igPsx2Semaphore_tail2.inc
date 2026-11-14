void Gap__Core__igPsx2Semaphore__vfunc_26(int *arg0, void *arg1, int arg2) {
    if (*(int *)((char *)(arg1) + 12) == -1) {
        *(int *)((char *)(arg1) + 16) = arg2;
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

/* IgPsx2Semaphore vtable slot 27, a plain getter that returns the reflected field _initCount (the
 * initial count the semaphore was created with, +16). */

int Gap__Core__igPsx2Semaphore__vfunc_27(igPsx2Semaphore *self) {
    return self->_initCount;
}

void Gap__Core__igPsx2Semaphore__vfunc_28(int *arg0, igPsx2Semaphore *self, int arg2) {
    if (self->_semaID == -1) {
        self->_maxCount = arg2;
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

/* IgPsx2Semaphore vtable slot 29, a plain getter that returns the reflected field _maxCount (the
 * maximum count the semaphore was created with, +20). */

int Gap__Core__igPsx2Semaphore__vfunc_29(igPsx2Semaphore *self) {
    return self->_maxCount;
}

int Gap__Core__igPsx2Semaphore__vfunc_30(igPsx2Semaphore *arg0) {
    int sp[8];
    int temp_v0;
    temp_v0 = arg0->_semaID;
    if (temp_v0 < 0) {
        return arg0->_initCount;
    }
    ReferSemaStatus(temp_v0, sp);
    return sp[0];
}

void Gap__Core__igPsx2Semaphore__vfunc_23(int *arg0, igPsx2Semaphore *self) {
    SemaParam param;
    char *var_v1_2;
    unsigned int var_v0;
    if (self->_semaID != -1) {
        *arg0 = g_resultFailure.v;
    } else {
        var_v1_2 = (char *)&param;
        var_v0 = 0x18;
        if (var_v1_2 != 0) {
            do {
                *var_v1_2 = 0;
                var_v0 -= 1;
                var_v1_2 += 1;
            } while (var_v0 != 0);
        }
        param.maxCount = self->_maxCount;
        param.initCount = self->_initCount;
        self->_semaID = CreateSema(&param);
        if (self->_semaID < 0) {
            self->_semaID = -1;
            *arg0 = g_resultFailure.v;
        } else {
            *arg0 = g_resultSuccess.v;
        }
    }
}

void Gap__Core__igPsx2Semaphore__vfunc_24(int *arg0, int *arg1) {
    int id = arg1[3];
    const int *p;
    if (id == -1) {
        *arg0 = g_resultFailure.v;
        return;
    }
    id = DeleteSema(id);
    arg1[3] = -1;
    p = id >= 0 ? &g_resultSuccess.v : &g_resultFailure.v;
    *arg0 = *p;
}

void Gap__Core__igPsx2Semaphore__vfunc_32(int *arg0, void *arg1) {
    const int *p;
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg1) + 12);
    if (temp_a0 == -1) {
        *arg0 = g_resultFailure.v;
    } else {
        if (iSignalSema(temp_a0) >= 0) {
            p = &g_resultSuccess.v;
        } else {
            p = &g_resultFailure.v;
        }
        *arg0 = *p;
    }
}

void Gap__Core__igPsx2Semaphore__vfunc_35(int *arg0, void *arg1) {
    const int *p;
    int h = *(int *)((char *)(arg1) + 12);
    if (h == -1) {
        *arg0 = g_resultFailure.v;
    } else {
        if (WaitSema(h) >= 0) {
            p = &g_resultSuccess.v;
        } else {
            p = &g_resultFailure.v;
        }
        *arg0 = *p;
    }
}

void Gap__Core__igPsx2Semaphore__vfunc_34(int *arg0, igPsx2Semaphore *self) {
    const int *p;
    if (self->_semaID == -1) { *arg0 = g_resultFailure.v; return; } p = (iPollSema(self->_semaID) >= 0) ? &g_resultSuccess.v : &g_resultFailure.v; *arg0 = *p;
}

SystemAllocator::SystemAllocator() {}

void FUN_0032f300(void) {
    if (g_activeSystemAllocator[0] == 0) {
        g_activeSystemAllocator[0] = &g_systemAllocator;
    }
}

void FUN_0032f330(void) {
    if (((void ** *)g_activeSystemAllocator)[0] != 0) {
        ((DW4VC_12_0 *)(((void ** *)g_activeSystemAllocator)[0]))->vX();
    }
}

int FUN_0032f370(void) {
    return 6;
}

void FUN_0032f380(SystemAllocator *self, ThreadMemoryMap *map) {
    unsigned top;
    unsigned marker;
    unsigned bottom;
    int size;
    unsigned regionSize;
    unsigned end;
    end = (unsigned)DAT_0058d280;
    marker = end;
    regionSize = (unsigned)DAT_00100000;
    top = (unsigned)&marker;
    top -= top % regionSize;
    bottom = top - regionSize;
    size = self->GetStackSize();
    if (size == -1) {
        size = g_rangeEnd[0];
    }
    FUN_003295d0((Tr *)self, (int *)map);
    map->stackTop = top;
    map->stackBottom = bottom - size;
    map->stackSize = size;
    map->textStart = (unsigned)(DAT_000ffff0 + 16);
    map->textSize = (unsigned)(Gap__Bec__beFont__vfunc_32 + 0x90);
    map->dataStart = (unsigned)__new_handler;
    map->dataSize = end - (unsigned)__new_handler;
    map->bssStart = (unsigned)__new_handler;
    map->bssSize = (unsigned)DAT_000d2c64;
    map->gp = (unsigned)DAT_00554e81;
    map->sbssSize = (unsigned)DAT_000383ff;
    map->stackRegion = top;
    map->stackRegionSize = regionSize;
    map->scratchpad = (unsigned)DAT_70000000;
    map->scratchpadSize = (unsigned)DAT_00004000;
    map->reserved = 0;
}

int FUN_0032f780(int arg0, int arg1) {
    int s1 = sbrk(arg1);
    int low;
    int pad;
    if (s1 != -1) {
        low = s1 & 0xFFF;
        if (low != 0) {
            pad = 0x1000 - low;
            if (sbrk(pad) == -1) {
                return -1;
            }
            s1 += pad;
        }
    }
    return s1;
}

