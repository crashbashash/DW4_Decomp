/* Deleting destructor. Sets the vtable to its own image, then calls __dl__FPv when the signed
 * low 16 bits of the delete flag are positive. __dl__FPv never returns (it ends in an endless
 * loop). */
igObject *FUN_00328e00(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_vtable[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            __dl__FPv();
        }
    }
    return self;
}

void FUN_00328e50(SystemAllocator *self) {
    for (unsigned int i = 0; i < 64; i++) {
        int *slot = &DAT_00587220[i];
        int table = *slot;
        if (table != 0) {
            self->vfunc_45((void *)table);
            *slot = 0;
        }
    }
}

int FUN_00328ed0(void *arg0, int arg1) {
    int temp_v0;

    temp_v0 = malloc(arg1);
    if (temp_v0 == DAT_00587328[0]) {
        FUN_00304430(DAT_004ff590, DAT_00587328[0]);
        FUN_00304680();
    }
    return temp_v0;
}

int FUN_00328f20(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = malloc(arg1);
    if (temp_v0 == DAT_00587328[0]) {
        FUN_00304430(DAT_004ff590, DAT_00587328[0]);
        FUN_00304680();
    }
    return temp_v0;
}

void FUN_00328f70(int unused, int a, int b) {
    calloc(a, b);
}

void FUN_00328f80(int arg0, int arg1, int arg2) {
    realloc(arg1, arg2);
}

int FUN_00328f90(SystemAllocator *self, int *arg1) {
    int *var_s1;
    int temp_v0;

    var_s1 = (int *)(arg1);
    if (var_s1 == 0) {
        var_s1 = (int *)(&DAT_004f7910[0]);
    }
    temp_v0 = (int)self->Allocate(strlen(var_s1) + 1);
    if (temp_v0 != 0) {
        strcpy(temp_v0, var_s1);
    }
    return temp_v0;
}

void FUN_00329000(int a0, int a1) {
    free(a1, a1);
}

void FUN_00329010(SystemAllocator *self, unsigned int size)
{
    self->vfunc_17(0, size);
}

void FUN_00329030(SystemAllocator *self, int arg1, int arg2) {
    igResult sp1C;

    sp1C = self->vfunc_18(arg1, arg2);
}

int FUN_00329070(SystemAllocator *self, int arg1, unsigned int arg2, unsigned int arg3) {
    igResult sp5C;
    igResult sp58;
    int temp_v0;

    if (arg2 < arg3) {
        sp5C = self->vfunc_18(arg1 + arg2, arg3 - arg2);
        return arg1;
    }
    if (self->vfunc_17(arg1 + arg3, arg2 - arg3) != -1) {
        return arg1;
    }
    temp_v0 = self->vfunc_17(0, arg2);
    if (temp_v0 == -1) {
        return 0;
    }
    memcpy(temp_v0, arg1, arg3);
    sp58 = self->vfunc_18(arg1, arg3);
    return temp_v0;
}

void FUN_00329170(SystemAllocator *self, unsigned int size)
{
    self->AllocateSized(size);
}

void FUN_00329180(SystemAllocator *self, void *block, int size)
{
    self->FreeSized(block, size);
}

void FUN_00329190(SystemAllocator *self, void *block, unsigned int size, unsigned int old)
{
    self->ReallocateSized(block, size, old);
}

void FUN_003291a0(SystemAllocator *self, int n) {
    if (n > 0) {
        if (self->vfunc_17(self->GetStackSize(), n) == -1) {
            self->vfunc_17(0, n);
        }
    } else if (n < 0) {
        int pos = self->GetStackSize();
        self->vfunc_18(pos + n, -n);
        self->GetStackSize();
    } else {
        self->GetStackSize();
    }
}

unsigned FUN_00329280(SystemAllocator *self, unsigned a, int n) {
    unsigned r = -1;
    if (a == 0) {
        unsigned t = self->vfunc_29(n);
        r = t;
        if (t == (unsigned)-1) r = self->vfunc_42(n);
    } else if (self->vfunc_28(a, n) != 0) {
        r = a;
    } else {
        unsigned c = self->GetStackSize();
        if (c == a) {
            r = self->vfunc_42(n);
            if (r != a) {
                if (r != (unsigned)-1) {
                    self->vfunc_42(-n);
                    r = -1;
                }
            }
        } else {
            unsigned e = a + n;
            if (a <= c && c < e && self->vfunc_28(a, c - a) != 0) {
                int m = e - c;
                r = self->vfunc_42(m);
                if (r != a && r != (unsigned)-1) {
                    self->vfunc_42(-m);
                    r = -1;
                }
            }
        }
    }
    if (r != (unsigned)-1) {
        igResult x = self->vfunc_46(r, n, 1);
        igResult y = self->vfunc_27(3, r, n);
    }
    return r;
}

igResult FUN_00329460(SystemAllocator *self, int arg2, int arg3) {
    int r17 = self->GetStackSize();
    if (r17 == arg2 + arg3) {
        int t = self->vfunc_42(-arg3);
        if (t != -1) {
            self->vfunc_27(0, t, arg3);
            return igResult(g_resultSuccess.v);
        }
    } else {
        return self->vfunc_43(arg2, arg3);
    }
    return igResult(g_resultFailure.v);
}

/* Result of the virtual call at vtable byte offset 168 (queried with 0), with a zero result mapped
 * to -1 (an index-style lookup that reports "not found" as -1). */
int FUN_00329540(SystemAllocator *self) {
    int result;

    result = self->vfunc_42(0);
    if (result == 0) {
        result = -1;
    }
    return result;
}

/* Lower bound of the address range the tracer pages over, or 0 while it still holds the all-ones
 * "unset" value. */
int FUN_00329570(void) {
    int start;

    start = g_rangeStart[0];
    if (start == -1) {
        start = 0;
    }
    return start;
}

int FUN_00329590(igPsx2CallStackTracer *self) {
    return TRACER_PAGE_SIZE;
}

int FUN_003295a0(igPsx2CallStackTracer *self) {
    return TRACER_BLOCK_SIZE;
}

int FUN_003295b0(void) {
    return g_rangeStart[0];
}

int FUN_003295c0(void) {
    return g_rangeEnd[0];
}

void FUN_003295d0(SystemAllocator *self, int *out) {
    PageStateCounts s;
    unsigned int i;
    int v = self->GetStackSize();
    if (v == -1) {
        v = g_rangeEnd[0];
    }
    memset(&s, 0, 16);
    i = 0;
    do {
        int t = DAT_00587220[i];
        if (t != 0) {
            FUN_0032ae00(t, &s);
        }
        i += 1;
    } while (i < 64);
    memset(out, 255, 84);
    out[0] = -1;
    out[1] = v - g_rangeStart[0];
    out[2] = g_rangeEnd[0] - g_rangeStart[0];
    out[3] = s.allocated << 12;
    out[4] = s.available << 12;
    out[5] = -1;
}

int FUN_003296d0(igPsx2CallStackTracer *self) {
    return 0;
}

igResult FUN_003296e0(SystemAllocator *self, int state, unsigned int addr, int len) {
    unsigned int end = addr + len;
    unsigned int startPage = addr >> 26;
    unsigned int endPage = end >> 26;
    unsigned int lo0 = (addr & 0x3FFFFFF) >> 12;
    unsigned int hi0 = (end & 0x3FFFFFF) >> 12;
    for (unsigned int page = startPage; page <= endPage; page++) {
        int *slot = &DAT_00587220[page];
        int table = *slot;
        unsigned int lo, hi;
        if (table == 0) {
            table = (int)self->vfunc_44(0x1000);
            memset(table, 0, 0x1000);
            *slot = table;
        }
        if (startPage < page) lo = 0; else lo = lo0;
        if (page < endPage) hi = 0x4000; else hi = hi0;
        FUN_0032ace0(table, lo, hi - lo, state);
    }
    if (addr < g_rangeStart[0]) g_rangeStart[0] = addr;
    if (g_rangeEnd[0] < end) g_rangeEnd[0] = end;
    return igResult(g_resultSuccess.v);
}

int FUN_00329860(void *self, unsigned int addr, unsigned int len) {
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
            p = DAT_00587220[i];
            if (p != 0) {
                lo = loB;
                if (i > s5) lo = 0;
                hi = hiB;
                if (i < s4) hi = 0x4000;
                r = FUN_0032ac70(p, lo);
                if (r != 1) break;
                t = FUN_0032ad50(p, lo, len, hi - lo, r);
                if (t >= len) return 1;
                len -= t;
            }
            i++;
        }
    }
    return 0;
}

unsigned int FUN_00329980(void *self, int size) {
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
    s5 = g_rangeStart[0];
    s6 = s5 >> 26;
    s3 = s6;
    s7 = g_rangeEnd[0] >> 26;
    while (s3 <= s7) {
        s2 = 0;
        if (s3 == s6) {
            s2 = (g_rangeStart[0] & 0x3FFFFFF) >> 12;
        }
        base = s3 << 26;
        if (s3 == s7) {
            s8 = (g_rangeEnd[0] & 0x3FFFFFF) >> 12;
        } else {
            s8 = 0x4000;
        }
        p = DAT_00587220[s3];
        if (p != 0) {
            while (s2 < s8) {
                r = FUN_0032ac70(p, s2);
                if (r == 1) {
                    v = FUN_0032ad50(p, s2, s4, r, 3);
                    if (s1 == 0) {
                        s5 = base + (s2 << 12);
                    }
                    s1 += v;
                    if (s1 >= s4) {
                        return s5;
                    }
                } else {
                    v = FUN_0032ad50(p, s2, 0x4000, r, 3);
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

void FUN_00329b20(void *arg0, int *arg1, int *arg2, int *arg3) {
    *arg1 = -1;
    *arg2 = -1;
    *arg3 = -1;
}

int FUN_00329b40(void *arg0, void *arg1, int *arg2, int *arg3) {
    *arg2 = -1;
    *arg3 = -1;
    return 1;
}

void FUN_00329b60(SystemAllocator *self) {
    char line[256];
    unsigned int page;
    unsigned int index;
    int pos;
    int table;
    int column;

    page = 0;
    do {
        table = DAT_00587220[page];
        if (table != 0) {
            pos = 0;
            index = 0;
            do {
                column = index & 0x3F;
                if (column == 0) {
                    sprintf(line, &DAT_004ff5c0[0], (page << 0x1A) + (index << 0xC));
                    pos = 0xB;
                }
                line[pos] = (char) (FUN_0032ac70(table, index) + 0x30);
                pos += 1;
                if (column == 0x3F) {
                    strcpy(line + pos, &DAT_004f95c8[0]);
                    FUN_00304430(line);
                    FUN_00304680();
                    pos = 0;
                }
                index += 1;
            } while (index < 0x4000U);
        } else {
            FUN_00304430(&DAT_004ff5c8[0], page << 0x1A);
            FUN_00304680();
        }
        page += 1;
    } while (page < 0x40U);
    self->vfunc_36();
}

void FUN_00329ca0(int unused, unsigned int addr, int len) {
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
        int table = DAT_00587220[page];
        if (table != 0) {
            unsigned int lo, hi;
            if (startPage < page) lo = 0; else lo = lo0;
            if (page < endPage) hi = 0x4000; else hi = hi0;
            for (j = lo; j < hi; ) {
                FUN_0032ac70(table, j);
                if ((counter & 0x3F) == 0) {
                    sprintf(buf, &DAT_004ff5c0[0], addr);
                    pos = 11;
                }
                buf[pos] = FUN_0032ac70(table, counter) + 0x30;
                pos++;
                if ((counter & 0x3F) == 0x3F) {
                    strcpy(buf + pos, &DAT_004f95c8[0]);
                    FUN_00304430(buf);
                    FUN_00304680();
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
        strcpy(buf + pos, &DAT_004f95c8[0]);
        FUN_00304430(buf);
        FUN_00304680();
    }
}

void FUN_00329e70(SystemAllocator *self) {
    SystemMemoryStatistics stats;
    self->GetStatistics(&stats);
    FUN_00304430(DAT_004ff5e0);
    FUN_00304680();
    FUN_00304430(DAT_004ff600, stats.totalSystemMemorySize, stats.totalSystemMemorySize);
    FUN_00304680();
    FUN_00304430(DAT_004ff630, stats.allocationSpan, stats.allocationSpan);
    FUN_00304680();
    FUN_00304430(DAT_004ff660, stats.maximumSpan, stats.maximumSpan);
    FUN_00304680();
    FUN_00304430(DAT_004ff690, stats.allocatedAndInUse, stats.allocatedAndInUse);
    FUN_00304680();
    FUN_00304430(DAT_004ff6c0, stats.allocatedAndAvailable, stats.allocatedAndAvailable);
    FUN_00304680();
    FUN_00304430(DAT_004ff6f0, stats.freeFromTop, stats.freeFromTop);
    FUN_00304680();
    FUN_00304430(DAT_004ff720, stats.codeStart, stats.codeStart);
    FUN_00304680();
    FUN_00304430(DAT_004ff750, stats.codeSize, stats.codeSize);
    FUN_00304680();
    FUN_00304430(DAT_004ff780, stats.dataStart, stats.dataStart);
    FUN_00304680();
    FUN_00304430(DAT_004ff7b0, stats.dataSize, stats.dataSize);
    FUN_00304680();
    FUN_00304430(DAT_004ff7e0, stats.initializedStart, stats.initializedStart);
    FUN_00304680();
    FUN_00304430(DAT_004ff810, stats.initializedSize, stats.initializedSize);
    FUN_00304680();
    FUN_00304430(DAT_004ff840, stats.uninitializedStart, stats.uninitializedStart);
    FUN_00304680();
    FUN_00304430(DAT_004ff870, stats.uninitializedSize, stats.uninitializedSize);
    FUN_00304680();
    FUN_00304430(DAT_004ff8a0, stats.stackStart, stats.stackStart);
    FUN_00304680();
    FUN_00304430(DAT_004ff8d0, stats.stackSize, stats.stackSize);
    FUN_00304680();
    FUN_00304430(DAT_004ff900, stats.fastStart, stats.fastStart);
    FUN_00304680();
    FUN_00304430(DAT_004ff930, stats.fastSize, stats.fastSize);
    FUN_00304680();
    FUN_00304430(DAT_004ff960, stats.virtualStart, stats.virtualStart);
    FUN_00304680();
    FUN_00304430(DAT_004ff990, stats.virtualSize, stats.virtualSize);
    FUN_00304680();
    FUN_00304430(DAT_004ff9c0, stats.heapTop, stats.heapTop);
    FUN_00304680();
}

DumpRegion *FUN_0032a100(DumpRegion *row) {
    memset(row, 0, sizeof(DumpRegion));
    return row;
}

DumpRegion *FUN_0032a130(DumpRegion *row, short flags) {
    if (row != 0) {
        if (flags > 0) {
            FUN_0032a220(row);
        }
    }
    return row;
}

void FUN_0032a180(DumpRegion *row, const char *annotation) {
    strncpy(row->annotation, annotation, sizeof(row->annotation) - 1);
    row->annotation[sizeof(row->annotation) - 1] = 0;
}

void FUN_0032a1b0(DumpRegion *row, const char *poolName) {
    strncpy(row->poolName, poolName, sizeof(row->poolName) - 1);
    row->poolName[sizeof(row->poolName) - 1] = 0;
}

DumpRegion *FUN_0032a1e0(int size) {
    return (DumpRegion *)((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked))->Allocate(size);
}

void FUN_0032a220(void *block) {
    ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked))->Free(block);
}

int FUN_0032a260(DumpRegion **a, DumpRegion **b) {
    return (*a)->start - (*b)->start;
}

void FUN_0032a280(SystemAllocator *self, char *title, char *path, int a, int b, int c, int d) {
    SystemMemoryStatistics stats;
    char region[160];
    int i;
    int count;
    FUN_00304430(DAT_004ffa00, title == 0 ? text_Memory_Map : title);
    FUN_00304680();
    self->GetStatistics(&stats);
    igSmartPointer<igPointerList> list((igPointerList *)FUN_002c9130((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked)));
    if (list->_count <= 1024) {
        FUN_002d6680(list, 1024, 4);
    }
    if (a != 0) {
        self->vfunc_38(list);
    }
    if (b != 0) {
        self->CollectProgramRegions(list);
    }
    if (c != 0) {
        self->CollectHeapRegions(list);
    }
    if (d != 0) {
        self->vfunc_41(list);
    }
    count = list->_count;
    if (path != 0 && count != 0) {
        igSmartPointer<igEventTrackerView> tracker((igEventTrackerView *)FUN_002c5780((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked)));
        FUN_002dcc40((int)tracker.p, list->_count);
        tracker->_flags |= 0x10;
        tracker->_memoryFieldFilterFlags = ~0x20;
        tracker->vfunc_23();
        for (i = 0; i < count; i++) {
            DumpRegion *e = ((DumpRegion **)list->_data)[i];
            FUN_002e2190(region, 1, (void *)e->start, e->size, 0, 0, 0, 0, (int)e->annotation, 0, 0, (int)e->poolName);
            tracker->vfunc_26((EventRecordInfo *)region, 0);
            FUN_002e2300(region, -1);
        }
        tracker->vfunc_44(path);
        tracker->vfunc_24();
    }
    FUN_00304430(DAT_004ffa10, text_Start, text_End, text_Size, text_Pool_Name, text_Annotation);
    FUN_00304680();
    for (i = 0; i < count; i++) {
        DumpRegion *e = ((DumpRegion **)list->_data)[i];
        FUN_00304430(DAT_004ffa60, e->start, e->start + e->size, e->size, e->poolName, e->annotation);
        FUN_00304680();
        FUN_0032a130(e, 1);
    }
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
}

void FUN_0032a5f0(int extra0)
{
}

void FUN_0032a600(SystemAllocator *self, int arg1) {
    DumpRegion *row;
    SystemMemoryStatistics out;
    int *s1;
    self->GetStatistics(&out);
    s1 = &out.codeStart;
    if (*s1 != -1) {
        DumpRegion *e = FUN_0032a1e0(sizeof(DumpRegion));
        if (e != 0) e = FUN_0032a100(e);
        row = e;
        e->start = *s1;
        row->size = out.codeSize;
        FUN_0032a180(row, text_Section_Code);
        FUN_0032a1b0(row, text_Program);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((igDataList *)arg1, &row, (Cmp)FUN_0032a260), 1, &row);
    }
    s1 = &out.dataStart;
    if (*s1 != -1) {
        DumpRegion *e = FUN_0032a1e0(sizeof(DumpRegion));
        if (e != 0) e = FUN_0032a100(e);
        row = e;
        e->start = *s1;
        row->size = out.dataSize;
        FUN_0032a180(row, text_Section_Data);
        FUN_0032a1b0(row, text_Program);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((igDataList *)arg1, &row, (Cmp)FUN_0032a260), 1, &row);
    }
    s1 = &out.initializedStart;
    if (*s1 != -1) {
        DumpRegion *e = FUN_0032a1e0(sizeof(DumpRegion));
        if (e != 0) e = FUN_0032a100(e);
        row = e;
        e->start = *s1;
        row->size = out.initializedSize;
        FUN_0032a180(row, text_Section_Initialized_Data);
        FUN_0032a1b0(row, text_Program);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((igDataList *)arg1, &row, (Cmp)FUN_0032a260), 1, &row);
    }
    s1 = &out.uninitializedStart;
    if (*s1 != -1) {
        DumpRegion *e = FUN_0032a1e0(sizeof(DumpRegion));
        if (e != 0) e = FUN_0032a100(e);
        row = e;
        e->start = *s1;
        row->size = out.uninitializedSize;
        FUN_0032a180(row, text_Section_Uninitialized_Data);
        FUN_0032a1b0(row, text_Program);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((igDataList *)arg1, &row, (Cmp)FUN_0032a260), 1, &row);
    }
    s1 = &out.stackStart;
    if (*s1 != -1) {
        DumpRegion *e = FUN_0032a1e0(sizeof(DumpRegion));
        if (e != 0) e = FUN_0032a100(e);
        row = e;
        e->start = *s1;
        row->size = out.stackSize;
        FUN_0032a180(row, text_Section_Stack_Data);
        FUN_0032a1b0(row, text_Program);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((igDataList *)arg1, &row, (Cmp)FUN_0032a260), 1, &row);
    }
}

void FUN_0032a900(SystemAllocator *self, int arg1) {
    DumpRegion *row;
    SystemMemoryStatistics out;
    unsigned i;
    unsigned j;
    int s2; int s1; int s0;
    self->GetStatistics(&out);
    for (i = 0; i < 0x40U; i++) {
        s0 = DAT_00587220[i];
        if (s0 != 0) for (j = 0; j < 0x4000U; j += s1) {
            s2 = FUN_0032ac70(s0, j);
            s1 = FUN_0032ad50(s0, j, 0x4000 - j, s2, 3);
            DumpRegion *e = FUN_0032a1e0(sizeof(DumpRegion));
            if (e != 0) e = FUN_0032a100(e);
            row = e;
            e->start = (i << 26) + (j << 12);
            row->size = s1 << 12;
            switch (s2) {
            case 0: FUN_0032a180(row, text_Heap_Unknown); FUN_0032a1b0(row, text_SystemHeap); break;
            case 1: FUN_0032a180(row, text_Heap_Free); FUN_0032a1b0(row, text_SystemHeap); break;
            case 2: FUN_0032a180(row, text_Heap_Blocked); FUN_0032a1b0(row, text_SystemHeap); break;
            case 3: FUN_0032a180(row, text_Heap_Allocated); FUN_0032a1b0(row, text_SystemHeap); break;
            }
            List_InsertWords((igDataList *)arg1, FUN_002d6e60((igDataList *)arg1, &row, (Cmp)FUN_0032a260), 1, &row);
        }
    }
    if (out.heapTop != -1 && out.freeFromTop != -1) {
        DumpRegion *e = FUN_0032a1e0(sizeof(DumpRegion));
        if (e != 0) e = FUN_0032a100(e);
        row = e;
        e->start = out.heapTop;
        row->size = out.freeFromTop;
        FUN_0032a180(row, text_Heap_Free_from_top);
        FUN_0032a1b0(row, text_SystemHeap);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((igDataList *)arg1, &row, (Cmp)FUN_0032a260), 1, &row);
    }
}

void FUN_0032ab90(int a0, int a1) {
    FUN_002f0760(a1, a1);
}

int FUN_0032aba0(void) {
    return -1;
}

void FUN_0032abb0(int *arg0, SystemAllocator *self, int arg2, int arg3) {igResult a = self->vfunc_27(1, arg2, arg3); igResult b = self->vfunc_46(arg2, arg3, 0);*arg0 = g_resultSuccess.v;}

void *FUN_0032ac40(SystemAllocator *self, unsigned int size)
{
    return self->Allocate(size);
}

void FUN_0032ac50(SystemAllocator *self, void *block)
{
    self->Free(block);
}

void FUN_0032ac60(int *arg0) {
    *arg0 = g_resultSuccess.v;
}

int FUN_0032ac70(int arg0, unsigned int arg1) {
    return (((unsigned int *)arg0)[arg1 >> 4] >> ((arg1 & 0xF) * 2)) & 3;
}

void FUN_0032aca0(int arg0, unsigned int arg1, int arg2) {
    int *temp_a2;
    int temp_a3;

    temp_a3 = (arg1 & 0xF) * 2;
    temp_a2 = (int *)(arg0 + ((arg1 >> 4) * 4));
    *temp_a2 = (~(3 << temp_a3) & *temp_a2) | (arg2 << temp_a3);
}

void FUN_0032ace0(int arg0, int arg1, int arg2, int arg3) {
    while (arg2-- != 0) {
        FUN_0032aca0(arg0, arg1, arg3);
        arg1++;
    }
}

int FUN_0032ad50(int arg0, unsigned int arg1, int arg2, int arg3, int arg4) {
    int n = 0;
    for (; arg1 < 0x4000U; arg1++) {
        if (arg2-- == 0) return n;
        if (arg3 != (arg4 & FUN_0032ac70(arg0, arg1))) return n;
        n++;
    }
    return n;
}

void FUN_0032ae00(int arg0, void *arg1) {
    int *temp_a1;
    int temp_v1;
    int var_s2;

    var_s2 = 0;
    do {
        temp_v1 = FUN_0032ac70(arg0, var_s2) * 4;
        var_s2 += 1;
        temp_a1 = (int *)((char *)arg1 + temp_v1);
        *temp_a1 += 1;
    } while (var_s2 < 0x4000);
}

void FUN_0032ae70(void) {
    if (g_activeSystemAllocator[0] == 0) {
        FUN_0032f300();
    }
}

void FUN_0032aea0(void) {
    if (g_activeSystemAllocator[0] != 0) {
        FUN_0032f330();
    }
}

