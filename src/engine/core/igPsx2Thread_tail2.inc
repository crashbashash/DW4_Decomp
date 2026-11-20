static inline int threadID(const igPsx2ThreadView *self) { return self->_threadID; }

int igPsx2Thread_IsEqual(void *self, void *other) {
    return ((igPsx2ThreadView *)self)->_threadID == ((igPsx2ThreadView *)other)->_threadID;
}

void igPsx2Thread_InitDefaults(igPsx2ThreadView *self) {
    igResult result;
    igSemaphoreView *done;

    self->_stack = (int)((Gap::Core::igObject *)self)->mallocAligned(self->_stackSize, self->GetStackAlignment());
    done = self->_threadDoneSema;
    result = done->SetInitialCount(0);
}

void igPsx2Thread_AdoptCurrentThread(igPsx2Thread *self) {
    self->_threadID = GetThreadId();
    ((Gap::Core::igObject *)self)->free((void *)self->_stack);
    self->_stack = 0;
}

void igPsx2Thread_Join(int *result, void *self, igPsx2ThreadView *thread) {
    igResult waited;
    igResult signalled;
    waited = thread->_threadDoneSema->Wait(1);
    signalled = thread->_threadDoneSema->Signal();
    if (thread->_threadID != -1) {
        while (ReferThreadStatus(thread->_threadID, 0) != 0x10) {
            p2SleepMilliseconds(1);
        }
    }
    *result = g_resultSuccess.v;
}

void igPsx2Thread_Sleep(int *result, int self, unsigned long long nanoseconds) {
    if (g_igPsx2LongTimer_initialized != 0) {
        p2SleepMilliseconds((int)__udivdi3(nanoseconds, 0xF4240));
        *result = g_resultSuccess.v;
    } else {
        *result = g_resultFailure.v;
    }
}

void igPsx2Thread_Exit(void *self, int result) {
    if (((igPsx2ThreadView *)self)->_isMaster == 0) {
        igPsx2Thread_Finish((igPsx2ThreadView *)self, result);
    }
}

void igPsx2Thread_WaitForWakeup(int *result) {
    SleepThread();
    *result = *(int *)0x4FB410;
}

void igPsx2Thread_Terminate(int *result, igPsx2ThreadView *self) {
    int s0, s1, s0b;
    igResult signalled;
    if (self->_isMaster != 0) {
        *result = g_resultFailure.v;
        return;
    }
    if (self->_isDeferred != 0 && self->_atStoppingPoint == 0) {
        self->_stopRequested = 1;
        *result = g_resultSuccess.v;
        return;
    }
    s0 = self->_threadID;
    if (s0 == GetThreadId()) {
        igPsx2Thread_Finish(self, 0);
    }
    g_threadManager->RemoveThread(self);
    s1 = self->_threadID;
    s0b = TerminateThread(threadID(self));
    self->_threadID = -1;
    signalled = self->_threadDoneSema->Signal();
    self->_refCount--;
    if (((unsigned long long)(long long)self->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy((igObject *)self);
    }
    DeleteThread(s1);
    const int *p = (s0b < 0) ? &g_resultFailure.v : &g_resultSuccess.v;
    *result = *p;
}

void igPsx2Thread_Wakeup(int *result, void *thread) {
    const int *word;

    if (WakeupThread(((igPsx2ThreadView *)thread)->_threadID) < 0) {
        word = &g_resultFailure.v;
    } else {
        word = &g_resultSuccess.v;
    }
    *result = *word;
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
    g_threadManager->RemoveThread(self);
    int id = self->_threadID;
    int status = TerminateThread(igPsx2Thread_getThreadID(self));
    self->_threadID = -1;
    igResult signalled = self->_threadDoneSema->Signal();
    --self->_refCount;
    if ((self->_refCount & 0x7fffff) == 0) {
        igObject_Destroy(self);
    }
    DeleteThread(id);
    return status < 0 ? g_resultFailure : g_resultSuccess;
}

void igPsx2Thread_IWakeup(int *result, void *thread) {
    const int *word;

    if (iWakeupThread(((igPsx2ThreadView *)thread)->_threadID) < 0) {
        word = &g_resultFailure.v;
    } else {
        word = &g_resultSuccess.v;
    }
    *result = *word;
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
    if (thread->IsRunning() != 0) {
        { *out = g_resultFailure.v; return; }
    }
    thread->_isDeferred = 1;
    thread->_stopRequested = 0;
    memset(&param, 0, 0x30);
    param.entry = igPsx2Thread_ThreadEntry;
    param.stack = (void *)thread->_stack;
    param.stackSize = thread->_stackSize;
    param.initPriority = thread->_priority / 2;
    param.gpReg = _gp;
    g_threadManager->AddThread(thread);
    thread->_threadID = CreateThread(&param);
    if (thread->_threadID < 0) {
        thread->_threadID = -1;
        { *out = g_resultFailure.v; return; }
    }
    if (thread->_threadDoneSema->IsCreated() != 0) {
        t1 = thread->_threadDoneSema->Destroy();
    }
    t2 = thread->_threadDoneSema->Create();
    thread->_threadID = _StartThread(thread->_threadID, thread);
    if (thread->_threadID == -1) {
        g_threadManager->RemoveThread(thread);
        t3 = thread->_threadDoneSema->Destroy();
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
    if (self->_isMaster == 0 && self->IsRunning() != 0) {
        return self->Terminate();
    }
    return igResult(g_resultFailure.v);
}

igResult igPsx2Thread_GetResult(igPsx2ThreadView *self, int block, int *result) {
    if (self->_threadDoneSema->IsCreated() == 0) {
        return igResult(g_resultFailure.v);
    }
    igResult t = self->_threadDoneSema->Wait(block);
    if (t.v != g_resultFailure.v) {
        self->_threadDoneSema->Signal();
        *result = self->_result;
    }
    return t;
}

void igPsx2Thread_SetDeferred(int *result, igPsx2Thread *self, int deferred) {
    if (self->_isMaster == 0) {
        self->_isDeferred = (deferred == 1);
        *result = g_resultSuccess.v;
    } else {
        *result = g_resultFailure.v;
    }
}

void igPsx2Thread_TestStop(igPsx2ThreadView *self) {
    if (self->_stopRequested != 0) {
        igPsx2Thread_Finish(self, 0);
    }
}

void igPsx2Thread_EnterStoppingPoint(void *self) {
    if (((igPsx2ThreadView *)self)->_stopRequested != 0) {
        igPsx2Thread_Finish((igPsx2ThreadView *)self, 0);
    }
    ((igPsx2ThreadView *)self)->_atStoppingPoint = 1;
}

void igPsx2Thread_LeaveStoppingPoint(void *self) {
    ((igPsx2ThreadView *)self)->_atStoppingPoint = 0;
}

void igPsx2Thread_Finish(igPsx2ThreadView *thread, int result) {
    thread->_result = result;
    igPsx2ThreadManager_FinishThread(g_threadManager, thread);
}

