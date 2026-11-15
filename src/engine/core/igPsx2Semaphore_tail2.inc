void igPsx2Semaphore_SetInitialCount(int *result, void *semaphore, int count) {
    if (((igPsx2Semaphore *)semaphore)->_semaID == -1) {
        ((igPsx2Semaphore *)semaphore)->_initCount = count;
        *result = g_resultSuccess.v;
    } else {
        *result = g_resultFailure.v;
    }
}

/* IgPsx2Semaphore vtable slot 27, a plain getter that returns the reflected field _initCount (the
 * initial count the semaphore was created with, +16). */

int igPsx2Semaphore_GetInitialCount(igPsx2Semaphore *self) {
    return self->_initCount;
}

void igPsx2Semaphore_SetMaximumCount(int *result, igPsx2Semaphore *self, int count) {
    if (self->_semaID == -1) {
        self->_maxCount = count;
        *result = g_resultSuccess.v;
    } else {
        *result = g_resultFailure.v;
    }
}

/* IgPsx2Semaphore vtable slot 29, a plain getter that returns the reflected field _maxCount (the
 * maximum count the semaphore was created with, +20). */

int igPsx2Semaphore_GetMaximumCount(igPsx2Semaphore *self) {
    return self->_maxCount;
}

int igPsx2Semaphore_GetCount(igPsx2Semaphore *self) {
    int status[8];
    int semaId;
    semaId = self->_semaID;
    if (semaId < 0) {
        return self->_initCount;
    }
    ReferSemaStatus(semaId, status);
    return status[0];
}

void igPsx2Semaphore_Create(int *result, igPsx2Semaphore *self) {
    SemaParam param;
    char *cursor;
    unsigned int remaining;
    if (self->_semaID != -1) {
        *result = g_resultFailure.v;
    } else {
        cursor = (char *)&param;
        remaining = 0x18;
        if (cursor != 0) {
            do {
                *cursor = 0;
                remaining -= 1;
                cursor += 1;
            } while (remaining != 0);
        }
        param.maxCount = self->_maxCount;
        param.initCount = self->_initCount;
        self->_semaID = CreateSema(&param);
        if (self->_semaID < 0) {
            self->_semaID = -1;
            *result = g_resultFailure.v;
        } else {
            *result = g_resultSuccess.v;
        }
    }
}

void igPsx2Semaphore_Destroy(int *result, int *semaphore) {
    int id = semaphore[3];  /* matching construct: the _semaID word read as semaphore[3]; the member spelling hoists &_semaID */
    const int *p;
    if (id == -1) {
        *result = g_resultFailure.v;
        return;
    }
    id = DeleteSema(id);
    semaphore[3] = -1;
    p = id >= 0 ? &g_resultSuccess.v : &g_resultFailure.v;
    *result = *p;
}

/* The EE's interrupt-enable state: Status.IE (bit 0) masked by Status.EIE (bit 16, shifted down onto it).
 * Bit 0 of the result is set while interrupts are enabled, that is, outside an interrupt handler.
 *
 * The statement is `volatile`, as Sony's Status reads are, and names its registers. The compiler skips its
 * peephole pass for the block that holds a `volatile` asm statement, so in both callers the conversion to
 * `bool` keeps both of its `xori 1` and its `andi 0xff`, and the receiver is read through its saved copy
 * (docs/engine/understanding-shapes.md has the compiler's side). */
static inline int interruptEnableStatus(void) {
    int status;
    __asm__ volatile("mfc0 $5, $12\n\tsrl $6, $5, 16\n\tand $5, $5, $6\n\tmove %0, $5" : "=r"(status));
    return status;
}

/* igPsx2Semaphore::signal. A thread signals through the kernel call; an interrupt handler uses the
 * interrupt-safe call, and only while the count is below the maximum. */
void igPsx2Semaphore_Signal(int *result, igPsx2Semaphore *self) {
    const igPsx2Semaphore *semaphore = self;  /* matching construct: the later reads go through a const view, which keeps its own register */
    int status = self->_semaID;
    bool interruptsEnabled = interruptEnableStatus() & 1;
    const int *p;
    if (semaphore->_semaID == -1) {
        *result = g_resultFailure.v;
        return;
    }
    if (interruptsEnabled) {
        status = SignalSema(semaphore->_semaID);
    } else {
        SemaParam counts;
        iReferSemaStatus(semaphore->_semaID, &counts);
        if (counts.currentCount != counts.maxCount) {
            status = iSignalSema(semaphore->_semaID);
        }
    }
    p = status >= 0 ? &g_resultSuccess.v : &g_resultFailure.v;
    *result = *p;
}

void igPsx2Semaphore_ISignal(int *result, void *semaphore) {
    const int *p;
    int semaId;

    semaId = ((igPsx2Semaphore *)semaphore)->_semaID;
    if (semaId == -1) {
        *result = g_resultFailure.v;
    } else {
        if (iSignalSema(semaId) >= 0) {
            p = &g_resultSuccess.v;
        } else {
            p = &g_resultFailure.v;
        }
        *result = *p;
    }
}

/* igPsx2Semaphore::wait. A thread waits (inside a stopping point, so the thread manager can suspend it)
 * or polls; an interrupt handler polls with the interrupt-safe call, whose result is not kept. */
void igPsx2Semaphore_Wait(int *result, igPsx2Semaphore *self, int block) {
    const igPsx2Semaphore *semaphore = self;  /* matching construct: the const view, as in signal */
    int status = self->_semaID;
    bool interruptsEnabled = interruptEnableStatus() & 1;
    const int *p;
    if (semaphore->_semaID == -1) {
        *result = g_resultFailure.v;
        return;
    }
    if (interruptsEnabled) {
        if (block) {
            igPsx2ThreadView *thread = g_threadManager->GetCurrentThread();
            igPsx2Thread_EnterStoppingPoint(thread);
            status = WaitSema(semaphore->_semaID);
            igPsx2Thread_LeaveStoppingPoint(thread);
        } else {
            status = PollSema(semaphore->_semaID);
        }
    } else {
        SemaParam counts;
        iReferSemaStatus(semaphore->_semaID, &counts);
        if (counts.currentCount != counts.maxCount) {
            iPollSema(semaphore->_semaID);
        }
    }
    p = status >= 0 ? &g_resultSuccess.v : &g_resultFailure.v;
    *result = *p;
}

void igPsx2Semaphore_WaitBlocking(int *result, void *semaphore) {
    const int *p;
    int h = ((igPsx2Semaphore *)semaphore)->_semaID;
    if (h == -1) {
        *result = g_resultFailure.v;
    } else {
        if (WaitSema(h) >= 0) {
            p = &g_resultSuccess.v;
        } else {
            p = &g_resultFailure.v;
        }
        *result = *p;
    }
}

void igPsx2Semaphore_IPoll(int *result, igPsx2Semaphore *self) {
    const int *p;
    if (self->_semaID == -1) { *result = g_resultFailure.v; return; } p = (iPollSema(self->_semaID) >= 0) ? &g_resultSuccess.v : &g_resultFailure.v; *result = *p;
}

SystemAllocator::SystemAllocator() {}

void SystemAllocator_Activate(void) {
    if (g_activeSystemAllocator == 0) {
        g_activeSystemAllocator = &g_systemAllocator;
    }
}

void SystemAllocator_Deactivate(void) {
    if (g_activeSystemAllocator != 0) {
        g_activeSystemAllocator->ReleasePageTables();
    }
}

int FUN_0032f370(void) {
    return 6;
}

void SystemAllocator_GetStatistics(SystemAllocator *self, SystemMemoryStatistics *stats) {
    unsigned top;
    unsigned marker;
    unsigned bottom;
    int heapTop;
    unsigned stackSize;
    unsigned end;
    end = (unsigned)_end;
    marker = end;
    stackSize = (unsigned)_stack_size;
    top = (unsigned)&marker;
    top -= top % stackSize;
    bottom = top - stackSize;
    heapTop = self->GetStackSize();
    if (heapTop == -1) {
        heapTop = g_rangeEnd;
    }
    SystemAllocatorBase_GetStatistics(self, (int *)stats);
    stats->totalSystemMemorySize = top;
    stats->freeFromTop = bottom - heapTop;
    stats->heapTop = heapTop;
    stats->codeStart = (int)__code_start__;
    stats->codeSize = (int)(Gap__Bec__beFont__vfunc_32 + 0x90);
    stats->dataStart = (int)__data_start__;
    stats->dataSize = end - (unsigned)__data_start__;
    stats->initializedStart = (int)__data_start__;
    stats->initializedSize = (int)__initialized_data_size__;
    stats->uninitializedStart = (int)__uninitialized_data_start__;
    stats->uninitializedSize = (int)__uninitialized_data_size__;
    stats->stackStart = top;
    stats->stackSize = stackSize;
    stats->fastStart = (int)__fast_memory_start__;
    stats->fastSize = (int)__fast_memory_size__;
    stats->virtualSize = 0;
}

/* Allocates a zeroed DumpRegion row for [start, start + size) into `row`. */
static inline void newRegion(DumpRegion *&row, unsigned start, unsigned size) {
    DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
    if (e != 0) e = DumpRegion_Init(e);
    row = e;
    e->start = start;
    row->size = size;
}

/* Labels `row` and inserts it into `regions`, kept sorted by start address. */
static inline void insertRegion(igDataList *regions, DumpRegion *&row, const char *annotation, const char *poolName) {
    DumpRegion_SetAnnotation(row, annotation);
    DumpRegion_SetPoolName(row, poolName);
    List_InsertWords(regions, List_LowerBound(regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
}

/* The PS2's fixed memories: the 32 MB of main RAM and the 16 KB scratchpad at 0x70000000. */
void SystemAllocator_CollectHardwareRegions(SystemAllocator *self, igDataList *regions) {
    DumpRegion *row;
    SystemAllocatorBase_CollectHardwareRegions((int)self);
    newRegion(row, 0, 0x02000000);
    insertRegion(regions, row, text_Memory_Main, text_Platform);
    newRegion(row, (unsigned)__fast_memory_start__, (unsigned)__fast_memory_size__);
    insertRegion(regions, row, text_Memory_Fast, text_Platform);
}

/* The program sections the base class does not know: static constructors, vtables, small data. */
void SystemAllocator_CollectProgramRegions(SystemAllocator *self, igDataList *regions) {
    DumpRegion *row;
    char *vtables;
    SystemAllocatorBase_CollectProgramRegions(self, (int)regions);
    DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
    if (e != 0) e = DumpRegion_Init(e);
    row = e;
    e->start = (unsigned)__ctors_start__;
    vtables = __ctors_end__;
    row->size = vtables - __ctors_start__;
    insertRegion(regions, row, text_Section_Static_Cons,"Program");
    newRegion(row, (unsigned)vtables, __exception_table_start__ - vtables);
    insertRegion(regions, row, text_Section_VTables,"Program");
    newRegion(row, (unsigned)__small_data_start__, (unsigned)__small_data_size__);
    insertRegion(regions, row, text_Section_Small_Data,"Program");
}

int SystemAllocator_Sbrk(int self, int size) {
    int s1 = sbrk(size);
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

