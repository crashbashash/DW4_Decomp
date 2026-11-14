void igPsx2Semaphore_SetInitialCount(int *arg0, void *arg1, int arg2) {
    if (*(int *)((char *)(arg1) + 12) == -1) {
        *(int *)((char *)(arg1) + 16) = arg2;
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

/* IgPsx2Semaphore vtable slot 27, a plain getter that returns the reflected field _initCount (the
 * initial count the semaphore was created with, +16). */

int igPsx2Semaphore_GetInitialCount(igPsx2Semaphore *self) {
    return self->_initCount;
}

void igPsx2Semaphore_SetMaximumCount(int *arg0, igPsx2Semaphore *self, int arg2) {
    if (self->_semaID == -1) {
        self->_maxCount = arg2;
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

/* IgPsx2Semaphore vtable slot 29, a plain getter that returns the reflected field _maxCount (the
 * maximum count the semaphore was created with, +20). */

int igPsx2Semaphore_GetMaximumCount(igPsx2Semaphore *self) {
    return self->_maxCount;
}

int igPsx2Semaphore_GetCount(igPsx2Semaphore *arg0) {
    int sp[8];
    int temp_v0;
    temp_v0 = arg0->_semaID;
    if (temp_v0 < 0) {
        return arg0->_initCount;
    }
    ReferSemaStatus(temp_v0, sp);
    return sp[0];
}

void igPsx2Semaphore_Create(int *arg0, igPsx2Semaphore *self) {
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

void igPsx2Semaphore_Destroy(int *arg0, int *arg1) {
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

void igPsx2Semaphore_ISignal(int *arg0, void *arg1) {
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

void igPsx2Semaphore_WaitBlocking(int *arg0, void *arg1) {
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

void igPsx2Semaphore_IPoll(int *arg0, igPsx2Semaphore *self) {
    const int *p;
    if (self->_semaID == -1) { *arg0 = g_resultFailure.v; return; } p = (iPollSema(self->_semaID) >= 0) ? &g_resultSuccess.v : &g_resultFailure.v; *arg0 = *p;
}

SystemAllocator::SystemAllocator() {}

void SystemAllocator_Activate(void) {
    if (g_activeSystemAllocator[0] == 0) {
        g_activeSystemAllocator[0] = &g_systemAllocator;
    }
}

void SystemAllocator_Deactivate(void) {
    if (g_activeSystemAllocator[0] != 0) {
        g_activeSystemAllocator[0]->vfunc_3();
    }
}

int FUN_0032f370(void) {
    return 6;
}

void SystemAllocator_GetStatistics(SystemAllocator *self, ThreadMemoryMap *map) {
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
    SystemAllocatorBase_GetStatistics(self, (int *)map);
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
    newRegion(row, (unsigned)DAT_70000000, (unsigned)DAT_00004000);
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
    vtables = DAT_00522480;
    row->size = vtables - __ctors_start__;
    insertRegion(regions, row, text_Section_Static_Cons, text_Program);
    newRegion(row, (unsigned)vtables, __exception_table_start__ - vtables);
    insertRegion(regions, row, text_Section_VTables, text_Program);
    newRegion(row, (unsigned)DAT_00554974, (unsigned)DAT_0000050d);
    insertRegion(regions, row, text_Section_Small_Data, text_Program);
}

int SystemAllocator_Sbrk(int arg0, int arg1) {
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

