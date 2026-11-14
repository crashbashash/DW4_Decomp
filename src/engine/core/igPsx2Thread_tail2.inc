static inline int threadID(const igPsx2ThreadView *self) { return self->_threadID; }

int igPsx2Thread_IsEqual(void *arg0, void *arg1) {
    return *(int *)((char *)(arg0) + 60) == *(int *)((char *)(arg1) + 60);
}

void igPsx2Thread_InitDefaults(igPsx2ThreadView *self) {
    igResult result;
    igSemaphoreView *done;

    self->_stack = igObject_MallocAligned((int)self, self->_stackSize, self->getStackAlignment() & 0xFFFF);
    done = self->_threadDoneSema;
    result = done->setInitialCount(0);
}

void igPsx2Thread_AdoptCurrentThread(igPsx2Thread *self) {
    self->_threadID = GetThreadId();
    igObject_FreeMemory((int)self, self->_stack);
    self->_stack = 0;
}

void igPsx2Thread_Join(int *arg0, void *arg1, igPsx2ThreadView *thread) {
    igResult waited;
    igResult signalled;
    waited = thread->_threadDoneSema->wait(1);
    signalled = thread->_threadDoneSema->signal();
    if (thread->_threadID != -1) {
        while (ReferThreadStatus(thread->_threadID, 0) != 0x10) {
            p2SleepMilliseconds(1);
        }
    }
    *arg0 = g_resultSuccess.v;
}

void igPsx2Thread_Sleep(int *arg0, int arg1, int arg2) {
    if (GPR_00554ddc != 0) {
        p2SleepMilliseconds((int)__udivdi3(arg2, 0xF4240));
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

void igPsx2Thread_Exit(void *arg0, int arg1) {
    if (*(unsigned char *)((char *)(arg0) + 44) == 0) {
        igPsx2Thread_Finish((igPsx2ThreadView *)arg0, arg1);
    }
}

void igPsx2Thread_WaitForWakeup(int *arg0) {
    SleepThread();
    *arg0 = *(int *)0x4FB410;
}

void igPsx2Thread_Terminate(int *arg0, igPsx2ThreadView *arg1) {
    int s0, s1, s0b;
    igResult signalled;
    if (arg1->_isMaster != 0) {
        *arg0 = g_resultFailure.v;
        return;
    }
    if (arg1->_isDeferred != 0 && arg1->_atStoppingPoint == 0) {
        arg1->_stopRequested = 1;
        *arg0 = g_resultSuccess.v;
        return;
    }
    s0 = arg1->_threadID;
    if (s0 == GetThreadId()) {
        igPsx2Thread_Finish(arg1, 0);
    }
    g_threadManager[0]->removeThread(arg1);
    s1 = arg1->_threadID;
    s0b = TerminateThread(threadID(arg1));
    arg1->_threadID = -1;
    signalled = arg1->_threadDoneSema->signal();
    arg1->_refCount--;
    if (((unsigned long long)(long long)arg1->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy((igObject *)arg1);
    }
    DeleteThread(s1);
    const int *p = (s0b < 0) ? &g_resultFailure.v : &g_resultSuccess.v;
    *arg0 = *p;
}

void igPsx2Thread_Wakeup(int *arg0, void *arg1) {
    const int *var_v1;

    if (WakeupThread(*(int *)((char *)arg1 + 60)) < 0) {
        var_v1 = &g_resultFailure.v;
    } else {
        var_v1 = &g_resultSuccess.v;
    }
    *arg0 = *var_v1;
}

void igPsx2Thread_Suspend(int *status, igPsx2Thread *self) {
    const int *word;

    if (SuspendThread(self->_threadID) < 0) {
        word = &g_resultFailure.v;
    } else {
        word = &g_resultSuccess.v;
    }
    *status = *word;
}

void igPsx2Thread_Resume(int *status, igPsx2Thread *self) {
    const int *word;

    if (ResumeThread(self->_threadID) < 0) {
        word = &g_resultFailure.v;
    } else {
        word = &g_resultSuccess.v;
    }
    *status = *word;
}

void igPsx2Thread_SetPriority(int *status, igPsx2Thread *self, int priority) {
    if (igThread_SetPriority(self, priority) != g_resultSuccess) {
        *status = g_resultFailure.v;
        return;
    }
    if (self->_threadID != -1) {
        const int *word = ChangeThreadPriority(self->_threadID, self->_priority / 2) < 0 ? &g_resultFailure.v : &g_resultSuccess.v;
        *status = *word;
        return;
    }
    *status = g_resultSuccess.v;
}

/* The thread's const id getter. A read through it is a `const int` read, which is not merged with
 * a plain read of the field: terminate() loads the id once for its saved copy and once for the call. */
static inline int igPsx2Thread_getThreadID(const igPsx2ThreadView *thread) { return thread->_threadID; }
igResult igPsx2Thread_ITerminate(igPsx2ThreadView *self) {
    if (self->_isMaster != 0) {
        return g_resultFailure;
    }
    if (self->_isDeferred != 0 && self->_atStoppingPoint == 0) {
        self->_stopRequested = 1;
        return g_resultSuccess;
    }
    if (self->_threadID == GetThreadId()) {
        igPsx2Thread_Finish(self, 0);
    }
    g_threadManager[0]->removeThread(self);
    int id = self->_threadID;
    int status = TerminateThread(igPsx2Thread_getThreadID(self));
    self->_threadID = -1;
    igResult signalled = self->_threadDoneSema->signal();
    --self->_refCount;
    if ((self->_refCount & 0x7fffff) == 0) {
        igObject_Destroy(self);
    }
    DeleteThread(id);
    return status < 0 ? g_resultFailure : g_resultSuccess;
}

void igPsx2Thread_IWakeup(int *arg0, void *arg1) {
    const int *var_v1;

    if (iWakeupThread(*(int *)((char *)arg1 + 60)) < 0) {
        var_v1 = &g_resultFailure.v;
    } else {
        var_v1 = &g_resultSuccess.v;
    }
    *arg0 = *var_v1;
}

void igPsx2Thread_ISuspend(int *status, igPsx2Thread *thread) {
    const int *word;

    if (iSuspendThread(thread->_threadID) < 0) {
        word = &g_resultFailure.v;
    } else {
        word = &g_resultSuccess.v;
    }
    *status = *word;
}

void igPsx2Thread_IResume(int *status, igPsx2Thread *self) {
    const int *word;

    if (iResumeThread(self->_threadID) < 0) {
        word = &g_resultFailure.v;
    } else {
        word = &g_resultSuccess.v;
    }
    *status = *word;
}

void igPsx2Thread_ISetPriority(int *status, igPsx2Thread *self, int priority) {
    if (igThread_SetPriority(self, priority) != g_resultSuccess) {
        *status = g_resultFailure.v;
        return;
    }
    if (self->_threadID != -1) {
        const int *word = iChangeThreadPriority(self->_threadID, self->_priority / 2) < 0 ? &g_resultFailure.v : &g_resultSuccess.v;
        *status = *word;
        return;
    }
    *status = g_resultSuccess.v;
}

void igPsx2Thread_Start(int *out, igPsx2ThreadView *thread) {
    ThreadParam param;
    igResult t1, t2, t3;
    if (thread->_function == 0) {
        { *out = g_resultFailure.v; return; }
    }
    if (thread->isRunning() != 0) {
        { *out = g_resultFailure.v; return; }
    }
    thread->_isDeferred = 1;
    thread->_stopRequested = 0;
    memset(&param, 0, 0x30);
    param.entry = (void (*)(void *))&FUN_0032f7f0;
    param.stack = (void *)thread->_stack;
    param.stackSize = thread->_stackSize;
    param.initPriority = thread->_priority / 2;
    param.gpReg = (void *)&_gp[0];
    g_threadManager[0]->addThread(thread);
    thread->_threadID = CreateThread(&param);
    if (thread->_threadID < 0) {
        thread->_threadID = -1;
        { *out = g_resultFailure.v; return; }
    }
    if (thread->_threadDoneSema->isCreated() != 0) {
        t1 = thread->_threadDoneSema->destroy();
    }
    t2 = thread->_threadDoneSema->create();
    thread->_threadID = _StartThread(thread->_threadID, thread);
    if (thread->_threadID == -1) {
        g_threadManager[0]->removeThread(thread);
        t3 = thread->_threadDoneSema->destroy();
        { *out = g_resultFailure.v; return; }
    }
    { *out = g_resultSuccess.v; return; }
}

unsigned char igPsx2Thread_IsRunning(igPsx2Thread *self) {
    int a; unsigned char r;
    a = self->_threadID; r = 0; if (a != -1) { int s = ReferThreadStatus(a, 0); if (s & 0xF) r = 1; }
    return r;
}

igResult igPsx2Thread_Stop(igPsx2ThreadView *self) {
    if (self->_isMaster == 0 && self->isRunning() != 0) {
        return self->terminate();
    }
    return igResult(g_resultFailure.v);
}

igResult igPsx2Thread_GetResult(igPsx2ThreadView *self, int block, int *result) {
    if (self->_threadDoneSema->isCreated() == 0) {
        return igResult(g_resultFailure.v);
    }
    igResult t = self->_threadDoneSema->wait(block);
    if (t.v != g_resultFailure.v) {
        self->_threadDoneSema->signal();
        *result = self->_result;
    }
    return t;
}

void igPsx2Thread_SetDeferred(int *arg0, igPsx2Thread *self, int arg2) {
    if (self->_isMaster == 0) {
        self->_isDeferred = (arg2 == 1);
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

void igPsx2Thread_TestStop(igPsx2ThreadView *self) {
    if (self->_stopRequested != 0) {
        igPsx2Thread_Finish(self, 0);
    }
}

void igPsx2Thread_EnterStoppingPoint(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 57) != 0) {
        igPsx2Thread_Finish((igPsx2ThreadView *)arg0, 0);
    }
    *(char *)((char *)(arg0) + 58) = 1;
}

void igPsx2Thread_LeaveStoppingPoint(void *arg0) {
    *(char *)((char *)arg0 + 58) = 0;
}

void igPsx2Thread_Finish(igPsx2ThreadView *thread, int result) {
    thread->_result = result;
    igPsx2ThreadManager_FinishThread(g_threadManager[0], thread);
}

