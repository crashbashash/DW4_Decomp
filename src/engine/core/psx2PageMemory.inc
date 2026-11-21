/* Deleting destructor. Sets the vtable to its own image, then calls operator delete when the
 * signed low 16 bits of the delete flag are positive. operator delete never returns (it ends in an
 * endless loop). */
igObject *SystemAllocatorBase_Destruct(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_vtable[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            operator delete(self);
        }
    }
    return self;
}

int g_systemPageTables[64];

void SystemAllocatorBase_ReleasePageTables(SystemAllocator *self) {
    for (unsigned int i = 0; i < 64; i++) {
        int *slot = &g_systemPageTables[i];
        int table = *slot;
        if (table != 0) {
            self->FreeTable((void *)table);
            *slot = 0;
        }
    }
}

int igSystemMallocTriggerAddress;

int SystemAllocatorBase_Allocate(void *self, int size) {
    int block;

    block = (int)malloc(size);
    if (block == igSystemMallocTriggerAddress) {
        igReport_Printf("igSystemMallocTriggerAddress 0x%08x hit.\n", igSystemMallocTriggerAddress);
        igReport_Flush();
    }
    return block;
}

int SystemAllocatorBase_Memalign(int self, int size) {
    int block;

    block = (int)malloc(size);
    if (block == igSystemMallocTriggerAddress) {
        igReport_Printf("igSystemMallocTriggerAddress 0x%08x hit.\n", igSystemMallocTriggerAddress);
        igReport_Flush();
    }
    return block;
}

void SystemAllocatorBase_Callocate(int unused, int a, int b) {
    calloc(a, b);
}

void SystemAllocatorBase_Reallocate(int self, int block, int size) {
    realloc((void *)block, size);
}

int SystemAllocatorBase_DuplicateString(SystemAllocator *self, int *string) {
    int *text;
    int copy;

    text = (int *)(string);
    if (text == 0) {
        text = (int *)("");
    }
    copy = (int)self->Allocate(strlen((const char *)text) + 1);
    if (copy != 0) {
        strcpy((char *)copy, (const char *)text);
    }
    return copy;
}

void SystemAllocatorBase_Free(int a0, int a1) {
    free((void *)a1);
}

void SystemAllocatorBase_AllocateSized(SystemAllocator *self, unsigned int size)
{
    self->AllocateRange(0, size);
}

void SystemAllocatorBase_FreeSized(SystemAllocator *self, int block, int size) {
    igResult result;

    result = self->FreeRange(block, size);
}

int SystemAllocatorBase_ReallocateSized(SystemAllocator *self, int block, unsigned int size, unsigned int oldSize) {
    igResult freeResult;
    igResult releaseResult;
    int moved;

    if (size < oldSize) {
        freeResult = self->FreeRange(block + size, oldSize - size);
        return block;
    }
    if (self->AllocateRange(block + oldSize, size - oldSize) != -1) {
        return block;
    }
    moved = self->AllocateRange(0, size);
    if (moved == -1) {
        return 0;
    }
    memcpy((void *)moved, (void *)block, oldSize);
    releaseResult = self->FreeRange(block, oldSize);
    return moved;
}

void SystemAllocatorBase_AllocateAligned(SystemAllocator *self, unsigned int size)
{
    self->AllocateSized(size);
}

void SystemAllocatorBase_FreeAligned(SystemAllocator *self, void *block, int size)
{
    self->FreeSized(block, size);
}

void SystemAllocatorBase_ReallocateAligned(SystemAllocator *self, void *block, unsigned int size, unsigned int old)
{
    self->ReallocateSized(block, size, old);
}

void SystemAllocatorBase_AdjustHeap(SystemAllocator *self, int n) {
    if (n > 0) {
        if (self->AllocateRange(self->GetStackSize(), n) == -1) {
            self->AllocateRange(0, n);
        }
    } else if (n < 0) {
        int pos = self->GetStackSize();
        self->FreeRange(pos + n, -n);
        self->GetStackSize();
    } else {
        self->GetStackSize();
    }
}

unsigned SystemAllocatorBase_AllocateRange(SystemAllocator *self, unsigned a, int n) {
    unsigned r = -1;
    if (a == 0) {
        unsigned t = self->FindFreeRange(n);
        r = t;
        if (t == (unsigned)-1) r = self->Sbrk(n);
    } else if (self->IsRangeFree(a, n) != 0) {
        r = a;
    } else {
        unsigned c = self->GetStackSize();
        if (c == a) {
            r = self->Sbrk(n);
            if (r != a) {
                if (r != (unsigned)-1) {
                    self->Sbrk(-n);
                    r = -1;
                }
            }
        } else {
            unsigned e = a + n;
            if (a <= c && c < e && self->IsRangeFree(a, c - a) != 0) {
                int m = e - c;
                r = self->Sbrk(m);
                if (r != a && r != (unsigned)-1) {
                    self->Sbrk(-m);
                    r = -1;
                }
            }
        }
    }
    if (r != (unsigned)-1) {
        igResult x = self->MarkRange(r, n, 1);
        igResult y = self->SetPageState(3, r, n);
    }
    return r;
}

igResult SystemAllocatorBase_FreeRange(SystemAllocator *self, int address, int size) {
    int top = self->GetStackSize();
    if (top == address + size) {
        int start = self->Sbrk(-size);
        if (start != -1) {
            self->SetPageState(0, start, size);
            return igResult(g_resultSuccess.v);
        }
    } else {
        return self->ReserveRange(address, size);
    }
    return igResult(g_resultFailure.v);
}

/* Result of the virtual call at vtable byte offset 168 (queried with 0), with a zero result mapped
 * to -1 (an index-style lookup that reports "not found" as -1). */
int SystemAllocatorBase_GetStackSize(SystemAllocator *self) {
    int result;

    result = self->Sbrk(0);
    if (result == 0) {
        result = -1;
    }
    return result;
}

unsigned int g_rangeStart = 0xffffffff;

/* Lower bound of the address range the tracer pages over, or 0 while it still holds the all-ones
 * "unset" value. */
int SystemAllocatorBase_GetRangeStart(void) {
    int start;

    start = g_rangeStart;
    if (start == -1) {
        start = 0;
    }
    return start;
}

int SystemAllocatorBase_GetPageSize(igPsx2CallStackTracer *self) {
    return TRACER_PAGE_SIZE;
}

int SystemAllocatorBase_GetBlockSize(igPsx2CallStackTracer *self) {
    return TRACER_BLOCK_SIZE;
}

int SystemAllocatorBase_GetRawRangeStart(void) {
    return g_rangeStart;
}

unsigned int g_rangeEnd;

int SystemAllocatorBase_GetRangeEnd(void) {
    return g_rangeEnd;
}

void SystemAllocatorBase_GetStatistics(SystemAllocator *self, int *out) {
    PageStateCounts s;
    unsigned int i;
    int v = self->GetStackSize();
    if (v == -1) {
        v = g_rangeEnd;
    }
    memset(&s, 0, 16);
    i = 0;
    do {
        int t = g_systemPageTables[i];
        if (t != 0) {
            PageTable_CountStates(t, &s);
        }
        i += 1;
    } while (i < 64);
    memset(out, 255, 84);
    out[0] = -1;
    out[1] = v - g_rangeStart;
    out[2] = g_rangeEnd - g_rangeStart;
    out[3] = s.allocated << 12;
    out[4] = s.available << 12;
    out[5] = -1;
}

int FUN_003296d0(igPsx2CallStackTracer *self) {
    return 0;
}

igResult SystemAllocatorBase_SetPageState(SystemAllocator *self, int state, unsigned int addr, int len) {
    unsigned int end = addr + len;
    unsigned int startPage = addr >> 26;
    unsigned int endPage = end >> 26;
    unsigned int lo0 = (addr & 0x3FFFFFF) >> 12;
    unsigned int hi0 = (end & 0x3FFFFFF) >> 12;
    for (unsigned int page = startPage; page <= endPage; page++) {
        int *slot = &g_systemPageTables[page];
        int table = *slot;
        unsigned int lo, hi;
        if (table == 0) {
            table = (int)self->AllocateTable(0x1000);
            memset((void *)table, 0, 0x1000);
            *slot = table;
        }
        if (startPage < page) lo = 0; else lo = lo0;
        if (page < endPage) hi = 0x4000; else hi = hi0;
        PageTable_SetStateRange(table, lo, hi - lo, state);
    }
    if (addr < g_rangeStart) g_rangeStart = addr;
    if (g_rangeEnd < end) g_rangeEnd = end;
    return igResult(g_resultSuccess.v);
}

int SystemAllocatorBase_IsRangeFree(void *self, unsigned int addr, unsigned int len) {
    unsigned int end, s5, s4, i, lo, hi, t, loB, hiB;
    int p, r;
    end = addr + len;
    s5 = addr >> 26;
    s4 = end >> 26;
    loB = (addr & 0x3FFFFFF) >> 12;
    hiB = (end & 0x3FFFFFF) >> 12;
    i = s5;
    if (len == 0) return 0;
    {
        while (i <= s4) {
            p = g_systemPageTables[i];
            if (p != 0) {
                lo = loB;
                if (i > s5) lo = 0;
                hi = hiB;
                if (i < s4) hi = 0x4000;
                r = PageTable_GetState(p, lo);
                if (r != 1) break;
                t = PageTable_CountRun(p, lo, len, hi - lo, r);
                if (t >= len) return 1;
                len -= t;
            }
            i++;
        }
    }
    return 0;
}

unsigned int SystemAllocatorBase_FindFreeRange(void *self, int size) {
    unsigned int base;
    unsigned int s5;
    unsigned int s4;
    unsigned int s3;
    unsigned int s2;
    unsigned int s1;
    int p;
    unsigned int v;
    unsigned int s6;
    unsigned int s7;
    int r;
    unsigned int s8;
    s4 = (unsigned int)(size + 0xFFF) >> 12;
    s1 = 0;
    s5 = g_rangeStart;
    s6 = s5 >> 26;
    s3 = s6;
    s7 = g_rangeEnd >> 26;
    while (s3 <= s7) {
        s2 = 0;
        if (s3 == s6) {
            s2 = (g_rangeStart & 0x3FFFFFF) >> 12;
        }
        base = s3 << 26;
        if (s3 == s7) {
            s8 = (g_rangeEnd & 0x3FFFFFF) >> 12;
        } else {
            s8 = 0x4000;
        }
        p = g_systemPageTables[s3];
        if (p != 0) {
            while (s2 < s8) {
                r = PageTable_GetState(p, s2);
                if (r == 1) {
                    v = PageTable_CountRun(p, s2, s4, r, 3);
                    if (s1 == 0) {
                        s5 = base + (s2 << 12);
                    }
                    s1 += v;
                    if (s1 >= s4) {
                        return s5;
                    }
                } else {
                    v = PageTable_CountRun(p, s2, 0x4000, r, 3);
                    s1 = 0;
                }
                s2 += v;
            }
        }
        s3++;
    }
    return -1;
}

int FUN_00329b00(void) {
    return -1;
}

int FUN_00329b10(void) {
    return -1;
}

void FUN_00329b20(void *self, int *first, int *second, int *third) {
    *first = -1;
    *second = -1;
    *third = -1;
}

int FUN_00329b40(void *self, void *region, int *first, int *second) {
    *first = -1;
    *second = -1;
    return 1;
}

void SystemAllocatorBase_DumpPageTables(SystemAllocator *self) {
    char line[256];
    unsigned int page;
    unsigned int index;
    int pos;
    int table;
    int column;

    page = 0;
    do {
        table = g_systemPageTables[page];
        if (table != 0) {
            pos = 0;
            index = 0;
            do {
                column = index & 0x3F;
                if (column == 0) {
                    sprintf(line, "%08x:  ", (page << 0x1A) + (index << 0xC));
                    pos = 0xB;
                }
                line[pos] = (char) (PageTable_GetState(table, index) + 0x30);
                pos += 1;
                if (column == 0x3F) {
                    strcpy(line + pos, &newline_2[0]);
                    igReport_Printf(line);
                    igReport_Flush();
                    pos = 0;
                }
                index += 1;
            } while (index < 0x4000U);
        } else {
            igReport_Printf("%08x:  (null)\n", page << 0x1A);
            igReport_Flush();
        }
        page += 1;
    } while (page < 0x40U);
    self->PrintStatistics();
}

void SystemAllocatorBase_DumpPageRange(int unused, unsigned int addr, int len) {
    char buf[256];
    unsigned int lo0, hi0;
    unsigned int startPage = addr >> 26;
    unsigned int end = addr + len;
    unsigned int endPage = end >> 26;
    unsigned int page = startPage;
    unsigned int j = 0;
    unsigned int counter = 0;
    int pos = 0;
    lo0 = (addr & 0x3FFFFFF) >> 12;
    hi0 = (end & 0x3FFFFFF) >> 12;
    if (len == 0) return;
    while (page <= endPage) {
        int table = g_systemPageTables[page];
        if (table != 0) {
            unsigned int lo, hi;
            if (startPage < page) lo = 0; else lo = lo0;
            if (page < endPage) hi = 0x4000; else hi = hi0;
            for (j = lo; j < hi; ) {
                PageTable_GetState(table, j);
                if ((counter & 0x3F) == 0) {
                    sprintf(buf, "%08x:  ", addr);
                    pos = 11;
                }
                buf[pos] = PageTable_GetState(table, counter) + 0x30;
                pos++;
                if ((counter & 0x3F) == 0x3F) {
                    strcpy(buf + pos, &newline_2[0]);
                    igReport_Printf(buf);
                    igReport_Flush();
                    pos = 0;
                }
                j++;
                counter++;
                addr += 0x1000;
            }
        }
        page++;
    }
    if (!(counter & 0x3F)) {
        strcpy(buf + pos, &newline_2[0]);
        igReport_Printf(buf);
        igReport_Flush();
    }
}

void SystemAllocatorBase_PrintStatistics(SystemAllocator *self) {
    SystemMemoryStatistics stats;
    self->GetStatistics(&stats);
    igReport_Printf("System memory statistics:\n");
    igReport_Flush();
    igReport_Printf("    totalSystemMemorySize     %d (0x%x)\n", stats.totalSystemMemorySize, stats.totalSystemMemorySize);
    igReport_Flush();
    igReport_Printf("    allocationSpan            %d (0x%x)\n", stats.allocationSpan, stats.allocationSpan);
    igReport_Flush();
    igReport_Printf("    maximumSpan               %d (0x%x)\n", stats.maximumSpan, stats.maximumSpan);
    igReport_Flush();
    igReport_Printf("    allocatedAndInUse         %d (0x%x)\n", stats.allocatedAndInUse, stats.allocatedAndInUse);
    igReport_Flush();
    igReport_Printf("    allocatedAndAvailable     %d (0x%x)\n", stats.allocatedAndAvailable, stats.allocatedAndAvailable);
    igReport_Flush();
    igReport_Printf("    freeFromTop               %d (0x%x)\n", stats.freeFromTop, stats.freeFromTop);
    igReport_Flush();
    igReport_Printf("    codeStart                 %d (0x%x)\n", stats.codeStart, stats.codeStart);
    igReport_Flush();
    igReport_Printf("    codeSize                  %d (0x%x)\n", stats.codeSize, stats.codeSize);
    igReport_Flush();
    igReport_Printf("    dataStart                 %d (0x%x)\n", stats.dataStart, stats.dataStart);
    igReport_Flush();
    igReport_Printf("    dataSize                  %d (0x%x)\n", stats.dataSize, stats.dataSize);
    igReport_Flush();
    igReport_Printf("    initializedStart          %d (0x%x)\n", stats.initializedStart, stats.initializedStart);
    igReport_Flush();
    igReport_Printf("    initializedSize           %d (0x%x)\n", stats.initializedSize, stats.initializedSize);
    igReport_Flush();
    igReport_Printf("    uninitializedStart        %d (0x%x)\n", stats.uninitializedStart, stats.uninitializedStart);
    igReport_Flush();
    igReport_Printf("    uninitializedSize         %d (0x%x)\n", stats.uninitializedSize, stats.uninitializedSize);
    igReport_Flush();
    igReport_Printf("    stackStart                %d (0x%x)\n", stats.stackStart, stats.stackStart);
    igReport_Flush();
    igReport_Printf("    stackSize                 %d (0x%x)\n", stats.stackSize, stats.stackSize);
    igReport_Flush();
    igReport_Printf("    fastStart                 %d (0x%x)\n", stats.fastStart, stats.fastStart);
    igReport_Flush();
    igReport_Printf("    fastSize                  %d (0x%x)\n", stats.fastSize, stats.fastSize);
    igReport_Flush();
    igReport_Printf("    virtualStart              %d (0x%x)\n", stats.virtualStart, stats.virtualStart);
    igReport_Flush();
    igReport_Printf("    virtualSize               %d (0x%x)\n", stats.virtualSize, stats.virtualSize);
    igReport_Flush();
    igReport_Printf("    heapTop                   %d (0x%x)\n", stats.heapTop, stats.heapTop);
    igReport_Flush();
}

DumpRegion *DumpRegion_Init(DumpRegion *row) {
    memset(row, 0, sizeof(DumpRegion));
    return row;
}

DumpRegion *DumpRegion_Destruct(DumpRegion *row, short flags) {
    if (row != 0) {
        if (flags > 0) {
            DumpRegion_Free(row);
        }
    }
    return row;
}

void DumpRegion_SetAnnotation(DumpRegion *row, const char *annotation) {
    strncpy(row->annotation, annotation, sizeof(row->annotation) - 1);
    row->annotation[sizeof(row->annotation) - 1] = 0;
}

void DumpRegion_SetPoolName(DumpRegion *row, const char *poolName) {
    strncpy(row->poolName, poolName, sizeof(row->poolName) - 1);
    row->poolName[sizeof(row->poolName) - 1] = 0;
}

DumpRegion *DumpRegion_Allocate(int size) {
    return (DumpRegion *)((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked))->Allocate(size);
}

void DumpRegion_Free(void *block) {
    ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked))->Free(block);
}

int DumpRegion_CompareStart(DumpRegion **a, DumpRegion **b) {
    return (*a)->start - (*b)->start;
}

void SystemAllocatorBase_PrintMemoryMap(SystemAllocator *self, char *title, char *path, int a, int b, int c, int d) {
    SystemMemoryStatistics stats;
    char region[160];
    int i;
    int count;
    igReport_Printf("%s:\n\n", title == 0 ?"Memory Map" : title);
    igReport_Flush();
    self->GetStatistics(&stats);
    igSmartPointer<igPointerList> list((igPointerList *)igPointerList_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked)));
    if (list->_count <= 1024) {
        ((Gap::Core::igDataList *)list.p)->setCapacity(1024, 4);
    }
    if (a != 0) {
        self->CollectHardwareRegions(list);
    }
    if (b != 0) {
        self->CollectProgramRegions(list);
    }
    if (c != 0) {
        self->CollectHeapRegions(list);
    }
    if (d != 0) {
        self->CollectPoolRegions(list);
    }
    count = list->_count;
    if (path != 0 && count != 0) {
        igSmartPointer<igEventTrackerView> tracker((igEventTrackerView *)igEventTracker_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked)));
        igEventTracker_SetCapacity((int)tracker.p, list->_count);
        tracker->_flags |= 0x10;
        tracker->_memoryFieldFilterFlags = ~0x20;
        tracker->Initialize();
        for (i = 0; i < count; i++) {
            DumpRegion *e = ((DumpRegion **)list->_data)[i];
            igEventTracker_InitMemoryEvent(region, 1, (void *)e->start, e->size, 0, 0, 0, 0, (int)e->annotation, 0, 0, (int)e->poolName);
            tracker->AddEvent((EventRecord *)region, 0);
            igEventTracker_DestructEvent(region, -1);
        }
        tracker->WriteFile(path);
        tracker->Shutdown();
    }
    igReport_Printf("    %10s %10s %10s %-14s %s \n\n","Start","End", text_Size,"Pool Name","Annotation");
    igReport_Flush();
    for (i = 0; i < count; i++) {
        DumpRegion *e = ((DumpRegion **)list->_data)[i];
        igReport_Printf("    0x%08x 0x%08x 0x%08x %-14s %s\n", e->start, e->start + e->size, e->size, e->poolName, e->annotation);
        igReport_Flush();
        DumpRegion_Destruct(e, 1);
    }
    igReport_Printf(newline_2);
    igReport_Flush();
}

void SystemAllocatorBase_CollectHardwareRegions(int extra0)
{
}

void SystemAllocatorBase_CollectProgramRegions(SystemAllocator *self, int regions) {
    DumpRegion *row;
    SystemMemoryStatistics out;
    int *start;
    self->GetStatistics(&out);
    start = &out.codeStart;
    if (*start != -1) {
        DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
        if (e != 0) e = DumpRegion_Init(e);
        row = e;
        e->start = *start;
        row->size = out.codeSize;
        DumpRegion_SetAnnotation(row,"Section Code");
        DumpRegion_SetPoolName(row,"Program");
        List_InsertWords((igDataList *)regions, List_LowerBound((igDataList *)regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
    }
    start = &out.dataStart;
    if (*start != -1) {
        DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
        if (e != 0) e = DumpRegion_Init(e);
        row = e;
        e->start = *start;
        row->size = out.dataSize;
        DumpRegion_SetAnnotation(row,"Section Data");
        DumpRegion_SetPoolName(row,"Program");
        List_InsertWords((igDataList *)regions, List_LowerBound((igDataList *)regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
    }
    start = &out.initializedStart;
    if (*start != -1) {
        DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
        if (e != 0) e = DumpRegion_Init(e);
        row = e;
        e->start = *start;
        row->size = out.initializedSize;
        DumpRegion_SetAnnotation(row,"Section Initialized Data");
        DumpRegion_SetPoolName(row,"Program");
        List_InsertWords((igDataList *)regions, List_LowerBound((igDataList *)regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
    }
    start = &out.uninitializedStart;
    if (*start != -1) {
        DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
        if (e != 0) e = DumpRegion_Init(e);
        row = e;
        e->start = *start;
        row->size = out.uninitializedSize;
        DumpRegion_SetAnnotation(row,"Section Uninitialized Data");
        DumpRegion_SetPoolName(row,"Program");
        List_InsertWords((igDataList *)regions, List_LowerBound((igDataList *)regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
    }
    start = &out.stackStart;
    if (*start != -1) {
        DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
        if (e != 0) e = DumpRegion_Init(e);
        row = e;
        e->start = *start;
        row->size = out.stackSize;
        DumpRegion_SetAnnotation(row,"Section Stack Data");
        DumpRegion_SetPoolName(row,"Program");
        List_InsertWords((igDataList *)regions, List_LowerBound((igDataList *)regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
    }
}

void SystemAllocatorBase_CollectHeapRegions(SystemAllocator *self, int regions) {
    DumpRegion *row;
    SystemMemoryStatistics out;
    unsigned i;
    unsigned j;
    int state; int run; int table;
    self->GetStatistics(&out);
    for (i = 0; i < 0x40U; i++) {
        table = g_systemPageTables[i];
        if (table != 0) for (j = 0; j < 0x4000U; j += run) {
            state = PageTable_GetState(table, j);
            run = PageTable_CountRun(table, j, 0x4000 - j, state, 3);
            DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
            if (e != 0) e = DumpRegion_Init(e);
            row = e;
            e->start = (i << 26) + (j << 12);
            row->size = run << 12;
            switch (state) {
            case 0: DumpRegion_SetAnnotation(row,"Heap Unknown"); DumpRegion_SetPoolName(row,"SystemHeap"); break;
            case 1: DumpRegion_SetAnnotation(row,"Heap Free"); DumpRegion_SetPoolName(row,"SystemHeap"); break;
            case 2: DumpRegion_SetAnnotation(row,"Heap Blocked"); DumpRegion_SetPoolName(row,"SystemHeap"); break;
            case 3: DumpRegion_SetAnnotation(row,"Heap Allocated"); DumpRegion_SetPoolName(row,"SystemHeap"); break;
            }
            List_InsertWords((igDataList *)regions, List_LowerBound((igDataList *)regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
        }
    }
    if (out.heapTop != -1 && out.freeFromTop != -1) {
        DumpRegion *e = DumpRegion_Allocate(sizeof(DumpRegion));
        if (e != 0) e = DumpRegion_Init(e);
        row = e;
        e->start = out.heapTop;
        row->size = out.freeFromTop;
        DumpRegion_SetAnnotation(row,"Heap Free from top");
        DumpRegion_SetPoolName(row,"SystemHeap");
        List_InsertWords((igDataList *)regions, List_LowerBound((igDataList *)regions, &row, (Cmp)DumpRegion_CompareStart), 1, &row);
    }
}

void SystemAllocatorBase_CollectPoolRegions(int a0, int a1) {
    igMemoryPool_CollectAllMemoryRegions(a1, a1);
}

int SystemAllocatorBase_Sbrk(void) {
    return -1;
}

void SystemAllocatorBase_ReserveRange(int *status, SystemAllocator *self, int address, int size) {igResult stateResult = self->SetPageState(1, address, size); igResult markResult = self->MarkRange(address, size, 0);*status = g_resultSuccess.v;}

void *SystemAllocatorBase_AllocateTable(SystemAllocator *self, unsigned int size)
{
    return self->Allocate(size);
}

void SystemAllocatorBase_FreeTable(SystemAllocator *self, void *block)
{
    self->Free(block);
}

void SystemAllocatorBase_MarkRange(int *status) {
    *status = g_resultSuccess.v;
}

int PageTable_GetState(int table, unsigned int page) {
    return (((unsigned int *)table)[page >> 4] >> ((page & 0xF) * 2)) & 3;
}

void PageTable_SetState(int table, unsigned int page, int state) {
    int *word;
    int shift;

    shift = (page & 0xF) * 2;
    word = (int *)(table + ((page >> 4) * 4));
    *word = (~(3 << shift) & *word) | (state << shift);
}

void PageTable_SetStateRange(int table, int page, int count, int state) {
    while (count-- != 0) {
        PageTable_SetState(table, page, state);
        page++;
    }
}

int PageTable_CountRun(int table, unsigned int page, int limit, int state, int mask) {
    int count = 0;
    for (; page < 0x4000U; page++) {
        if (limit-- == 0) return count;
        if (state != (mask & PageTable_GetState(table, page))) return count;
        count++;
    }
    return count;
}

void PageTable_CountStates(int table, void *counts) {
    int *counter;
    int offset;
    int page;

    page = 0;
    do {
        offset = PageTable_GetState(table, page) * 4;
        page += 1;
        counter = (int *)((char *)counts + offset);
        *counter += 1;
    } while (page < 0x4000);
}

void SystemAllocator_EnsureCreated(void) {
    if (g_activeSystemAllocator == 0) {
        SystemAllocator_Activate();
    }
}

void SystemAllocator_EnsureDestroyed(void) {
    if (g_activeSystemAllocator != 0) {
        SystemAllocator_Deactivate();
    }
}

