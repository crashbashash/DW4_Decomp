static inline int threadID(const igPsx2Thread *self) { return self->_threadID; }

int Gap__Core__igPsx2Thread__vfunc_23(void *arg0, void *arg1) {
    return *(int *)((char *)(arg0) + 60) == *(int *)((char *)(arg1) + 60);
}

void Gap__Core__igPsx2Thread__vfunc_11(void *arg0) {
    DW4SR4 sp2C;
    void **temp_a1;

    *(int *)((char *)(arg0) + 32) = FUN_00300db0((int)arg0, *(int *)((char *)(arg0) + 36), ((DW4VC_168_0 *)(((char *)(arg0) + 0)))->vX() & 0xFFFF);
    temp_a1 = (void **)(*(int *)((char *)(arg0) + 48));
    sp2C = ((DW4VCSR_104_1 *)(temp_a1))->vX((int)(0));
}

void Gap__Core__igPsx2Thread__vfunc_55(igPsx2Thread *self) {
    self->_threadID = GetThreadId();
    FUN_00300f50((int)self, self->_stack);
    self->_stack = 0;
}

void Gap__Core__igPsx2Thread__vfunc_24(int *arg0, void *arg1, T24_32f840 *arg2) {
    SR24 sp3C;
    SR24 sp38;
    sp3C = ((VC1_24 *)arg2->f48)->vX(1);
    sp38 = ((VC2_24 *)arg2->f48)->vX();
    if (arg2->f60 != -1) {
        while (ReferThreadStatus(arg2->f60, 0) != 0x10) {
            p2SleepMilliseconds(1);
        }
    }
    *arg0 = g_statusSucceeded.v;
}

void Gap__Core__igPsx2Thread__vfunc_25(int *arg0, int arg1, int arg2) {
    if (GPR_00554ddc != 0) {
        p2SleepMilliseconds((int)__udivdi3(arg2, 0xF4240));
        *arg0 = g_statusSucceeded.v;
    } else {
        *arg0 = g_allocatorFailureStatus.v;
    }
}

void Gap__Core__igPsx2Thread__vfunc_26(void *arg0, int arg1) {
    if (*(unsigned char *)((char *)(arg0) + 44) == 0) {
        FUN_00330440((igPsx2Thread *)arg0, arg1);
    }
}

void Gap__Core__igPsx2Thread__vfunc_29(int *arg0) {
    SleepThread();
    *arg0 = *(int *)0x4FB410;
}

void Gap__Core__igPsx2Thread__vfunc_44(int *arg0, igPsx2Thread *arg1) {
    int s0, s1, s0b;
    RS44 sp5C;
    if (arg1->_isMaster != 0) {
        *arg0 = g_allocatorFailureStatus.v;
        return;
    }
    if (arg1->_isDeferred != 0 && arg1->_atStoppingPoint == 0) {
        arg1->_stopRequested = 1;
        *arg0 = g_statusSucceeded.v;
        return;
    }
    s0 = arg1->_threadID;
    if (s0 == GetThreadId()) {
        FUN_00330440(arg1, 0);
    }
    g_threadManager[0]->v23(arg1);
    s1 = arg1->_threadID;
    s0b = TerminateThread(threadID(arg1));
    arg1->_threadID = -1;
    sp5C = ((Sub44 *)arg1->_threadDoneSema)->get();
    arg1->_refCount--;
    if (((unsigned long long)(long long)arg1->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy((igObject *)arg1);
    }
    DeleteThread(s1);
    int *p = (s0b < 0) ? &g_allocatorFailureStatus.v : &g_statusSucceeded.v;
    *arg0 = *p;
}

void Gap__Core__igPsx2Thread__vfunc_27(int *arg0, void *arg1) {
    int *var_v1;

    if (WakeupThread(*(int *)((char *)arg1 + 60)) < 0) {
        var_v1 = &g_allocatorFailureStatus.v;
    } else {
        var_v1 = &g_statusSucceeded.v;
    }
    *arg0 = *var_v1;
}

void Gap__Core__igPsx2Thread__vfunc_46(int *status, igPsx2Thread *self) {
    int *word;

    if (SuspendThread(self->_threadID) < 0) {
        word = &g_allocatorFailureStatus.v;
    } else {
        word = &g_statusSucceeded.v;
    }
    *status = *word;
}

void Gap__Core__igPsx2Thread__vfunc_48(int *status, igPsx2Thread *self) {
    int *word;

    if (ResumeThread(self->_threadID) < 0) {
        word = &g_allocatorFailureStatus.v;
    } else {
        word = &g_statusSucceeded.v;
    }
    *status = *word;
}

void Gap__Core__igPsx2Thread__vfunc_45(int *arg0, O45 *arg1) {
    /* matching construct: variant search — decl order [4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    const O45 *view = arg1;
    H4 sp5C;
    int temp_s1;
    int temp_s0_2;
    int temp_s0;
    int *var_v1_2;

    if (arg1->f44 != 0) {
        *arg0 = g_allocatorFailureStatus.v;
        return;
    }
    if ((arg1->f56 != 0) && (arg1->f58 == 0)) {
        arg1->f57 = 1;
        *arg0 = g_statusSucceeded.v;
        return;
    }
    temp_s0 = arg1->f60;
    if (temp_s0 == GetThreadId()) {
        FUN_00330440((igPsx2Thread *)arg1, 0);
    }
    g_threadManager[0]->v23(arg1);
    temp_s1 = view->f60;
    temp_s0_2 = TerminateThread(arg1->f60);
    arg1->f60 = -1;
    sp5C = arg1->f48->vX();
    arg1->rc4 = arg1->rc4 - 1;
    if ((arg1->rc4 & 0x7FFFFF) == 0) {
        igObject_Destroy(arg1);
    }
    DeleteThread(temp_s1);
    if (temp_s0_2 < 0) {
        var_v1_2 = (int *)(&g_allocatorFailureStatus.v);
    } else {
        var_v1_2 = (int *)(&g_statusSucceeded.v);
    }
    *arg0 = *var_v1_2;
}

void Gap__Core__igPsx2Thread__vfunc_28(int *arg0, void *arg1) {
    int *var_v1;

    if (iWakeupThread(*(int *)((char *)arg1 + 60)) < 0) {
        var_v1 = &g_allocatorFailureStatus.v;
    } else {
        var_v1 = &g_statusSucceeded.v;
    }
    *arg0 = *var_v1;
}

void Gap__Core__igPsx2Thread__vfunc_47(int *status, igPsx2Thread *thread) {
    int *word;

    if (iSuspendThread(thread->_threadID) < 0) {
        word = &g_allocatorFailureStatus.v;
    } else {
        word = &g_statusSucceeded.v;
    }
    *status = *word;
}

void Gap__Core__igPsx2Thread__vfunc_49(int *status, igPsx2Thread *self) {
    int *word;

    if (iResumeThread(self->_threadID) < 0) {
        word = &g_allocatorFailureStatus.v;
    } else {
        word = &g_statusSucceeded.v;
    }
    *status = *word;
}

void Gap__Core__igPsx2Thread__vfunc_30(int *out, Obj30 *o) {
    TP30 tp;
    R30_32f840 t1, t2, t3;
    if (o->w40 == 0) {
        { *out = g_allocatorFailureStatus.v; return; }
    }
    if (o->v30() != 0) {
        { *out = g_allocatorFailureStatus.v; return; }
    }
    o->f56 = 1;
    o->f57 = 0;
    memset(&tp, 0, 0x30);
    tp.w[1] = (int)&FUN_0032f7f0;
    tp.w[2] = o->w32;
    tp.w[3] = o->w36;
    tp.w[5] = o->w24 / 2;
    tp.w[4] = (int)&_gp[0];
    g_threadManager[0]->v22(o);
    o->th = CreateThread(&tp);
    if (o->th < 0) {
        o->th = -1;
        { *out = g_allocatorFailureStatus.v; return; }
    }
    if (o->sub->v23() != 0) {
        t1 = o->sub->v22();
    }
    t2 = o->sub->v21();
    o->th = _StartThread(o->th, o);
    if (o->th == -1) {
        g_threadManager[0]->v23(o);
        t3 = o->sub->v22();
        { *out = g_allocatorFailureStatus.v; return; }
    }
    { *out = g_statusSucceeded.v; return; }
}

unsigned char Gap__Core__igPsx2Thread__vfunc_32(S32 *arg0) {
    int a; unsigned char r;
    a = arg0->f60; r = 0; if (a != -1) { int s = ReferThreadStatus(a, 0); if (s & 0xF) r = 1; }
    return r;
}

R31 Gap__Core__igPsx2Thread__vfunc_31(C31_32f840 *arg1) {
    if (arg1->f44 == 0 && arg1->vA() != 0) {
        return arg1->vB();
    }
    return R31(g_allocatorFailureStatus.v);
}

R41 Gap__Core__igPsx2Thread__vfunc_41(O41 *arg1, int arg2, int *arg3) {
    if (arg1->c->v100() == 0) {
        return R41(g_allocatorFailureStatus.v);
    }
    R41 t = arg1->c->v132(arg2);
    if (t.v != g_allocatorFailureStatus.v) {
        arg1->c->v124();
        *arg3 = arg1->f52;
    }
    return t;
}

void Gap__Core__igPsx2Thread__vfunc_56(int *arg0, T56 *arg1, int arg2) {
    if (arg1->f44 == 0) {
        arg1->f56 = (arg2 == 1);
        *arg0 = g_statusSucceeded.v;
    } else {
        *arg0 = g_allocatorFailureStatus.v;
    }
}

void Gap__Core__igPsx2Thread__vfunc_57(igPsx2Thread *self) {
    if (self->_stopRequested != 0) {
        FUN_00330440(self, 0);
    }
}

void FUN_003303f0(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 57) != 0) {
        FUN_00330440((igPsx2Thread *)arg0, 0);
    }
    *(char *)((char *)(arg0) + 58) = 1;
}

void FUN_00330430(void *arg0) {
    *(char *)((char *)arg0 + 58) = 0;
}

void FUN_00330440(igPsx2Thread *arg0, int arg1) {
    arg0->_result = arg1;
    FUN_003304e0((void **)g_threadManager[0], arg0);
}

