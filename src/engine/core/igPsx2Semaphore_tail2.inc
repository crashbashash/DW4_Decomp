void Gap__Core__igPsx2Semaphore__vfunc_26(int *arg0, void *arg1, int arg2) {
    if (*(int *)((char *)(arg1) + 12) == -1) {
        *(int *)((char *)(arg1) + 16) = arg2;
        *arg0 = g_statusSucceeded.v;
    } else {
        *arg0 = g_allocatorFailureStatus.v;
    }
}

/* IgPsx2Semaphore vtable slot 27, a plain getter that returns the reflected field _initCount (the
 * initial count the semaphore was created with, +16). */

int Gap__Core__igPsx2Semaphore__vfunc_27(igPsx2Semaphore *self) {
    return self->_initCount;
}

void Gap__Core__igPsx2Semaphore__vfunc_28(int *arg0, struct S_32ed50 *arg1, int arg2) {
    if (arg1->f12 == -1) {
        arg1->f20 = arg2;
        *arg0 = g_statusSucceeded.v;
    } else {
        *arg0 = g_allocatorFailureStatus.v;
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

void Gap__Core__igPsx2Semaphore__vfunc_23(int *arg0, struct S_arg1 *arg1) {
    union U_32ede0 u;
    char *var_v1_2;
    unsigned int var_v0;
    if (arg1->f12 != -1) {
        *arg0 = g_allocatorFailureStatus.v;
    } else {
        var_v1_2 = u.b;
        var_v0 = 0x18;
        if (var_v1_2 != 0) {
            do {
                *var_v1_2 = 0;
                var_v0 -= 1;
                var_v1_2 += 1;
            } while (var_v0 != 0);
        }
        u.w[1] = arg1->f20;
        u.w[2] = arg1->f16;
        arg1->f12 = CreateSema(&u);
        if (arg1->f12 < 0) {
            arg1->f12 = -1;
            *arg0 = g_allocatorFailureStatus.v;
        } else {
            *arg0 = g_statusSucceeded.v;
        }
    }
}

void Gap__Core__igPsx2Semaphore__vfunc_24(int *arg0, int *arg1) {
    int id = arg1[3];
    int *p;
    if (id == -1) {
        *arg0 = g_allocatorFailureStatus.v;
        return;
    }
    id = DeleteSema(id);
    arg1[3] = -1;
    p = id >= 0 ? &g_statusSucceeded.v : &g_allocatorFailureStatus.v;
    *arg0 = *p;
}

void Gap__Core__igPsx2Semaphore__vfunc_32(int *arg0, void *arg1) {
    int *p;
    int temp_a0;

    temp_a0 = *(int *)((char *)(arg1) + 12);
    if (temp_a0 == -1) {
        *arg0 = g_allocatorFailureStatus.v;
    } else {
        if (iSignalSema(temp_a0) >= 0) {
            p = &g_statusSucceeded.v;
        } else {
            p = &g_allocatorFailureStatus.v;
        }
        *arg0 = *p;
    }
}

void Gap__Core__igPsx2Semaphore__vfunc_35(int *arg0, void *arg1) {
    int *p;
    int h = *(int *)((char *)(arg1) + 12);
    if (h == -1) {
        *arg0 = g_allocatorFailureStatus.v;
    } else {
        if (WaitSema(h) >= 0) {
            p = &g_statusSucceeded.v;
        } else {
            p = &g_allocatorFailureStatus.v;
        }
        *arg0 = *p;
    }
}

void Gap__Core__igPsx2Semaphore__vfunc_34(int *arg0, struct T_32f1f0 *arg1) {
    int *p;
    if (arg1->t == -1) { *arg0 = g_allocatorFailureStatus.v; return; } p = (iPollSema(arg1->t) >= 0) ? &g_statusSucceeded.v : &g_allocatorFailureStatus.v; *arg0 = *p;
}

int **FUN_0032f260(int **arg0) {
    FUN_00328de0((int **)arg0);
    *arg0 = &DAT_0052d8b0[0];
    return arg0;
}

int **FUN_0032f2a0(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0052d8b0[0];
        FUN_00328e00((igObject *)arg0, 0);
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0032f300(void) {
    if (((int * *)DAT_00587218)[0] == 0) {
        ((int * *)DAT_00587218)[0] = &DAT_00587380[0];
    }
}

void FUN_0032f330(void) {
    if (((void ** *)DAT_00587218)[0] != 0) {
        ((DW4VC_12_0 *)(((void ** *)DAT_00587218)[0]))->vX();
    }
}

int FUN_0032f370(void) {
    return 6;
}

void FUN_0032f380(ThreadStackOwner *self, ThreadMemoryMap *map) {
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

