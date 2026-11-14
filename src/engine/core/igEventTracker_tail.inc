void FUN_002dca90(void)
{
}

static inline void setLock(igEventTrackerView *self, igSemaphoreView *pool) {
    igSemaphoreView *previous;
    if (pool != 0) {
        pool->_refCount = pool->_refCount + 1;
    }
    previous = self->_lock;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_lock = pool;
}

void FUN_002dcaa0(igEventTrackerView *self, int open) {
    if (open != 0) {
        if (self->_lock == 0) {
            igSmartPointer<igSemaphoreView> created(((igSemaphoreView *)FUN_002ba650(((int)igObject_GetAllocator((int)self)))));
            created.get()->create();
            setLock(self, created.get());
        }
    } else {
        if (self->_lock != 0) {
            igSmartPointer<igSemaphoreView> kept(self->_lock);
            kept.retain();
            setLock(self, 0);
            if (kept.get() != 0) {
                kept.get()->destroy();
            }
        }
    }
}

void FUN_002dcc40(int a0, int a1)
{
    *(int *)((char *)a0 + 36) = a1;
}

int FUN_002dcc50(int *p)
{
    return *(int *)((char *)p + 40);
}

void FUN_002dcc60(igEventTrackerView *tracker, int tag) {
    ScopedLock guard(tracker->_lock);
    if (tracker->isBusy() != false) {
        return;
    }
    tracker->_flags = tracker->_flags | 2;
    if (tag != 0) {
        strncpy(tracker->_eventTag, tag, 0xFF);
    } else {
        tracker->_eventTag[0] = 0;
    }
    if (tracker->_eventTag[0] != 0) {
        tracker->_eventTagOffset = FUN_0030d300(tracker->_groups, (int)tracker->_eventTag);
    } else {
        tracker->_eventTagOffset = -1;
    }
    tracker->_flags = tracker->_flags & ~2;
}

void FUN_002dcd70(igEventTrackerView *tracker, int className) {
    EventTrackerScopedLock guard(tracker->_lock);
    if (tracker->isBusy() != false) {
        return;
    }
    tracker->_flags = tracker->_flags | 2;
    if (className != 0) {
        strncpy(tracker->_eventClassName, className, 0xFF);
    } else {
        tracker->_eventClassName[0] = 0;
    }
    if (tracker->_eventClassName[0] != 0) {
        tracker->_eventClassNameOffset = FUN_0030d300(tracker->_classNames, (int)tracker->_eventClassName);
    } else {
        tracker->_eventClassNameOffset = -1;
    }
    tracker->_flags = tracker->_flags & ~2;
}

void Gap__Core__igEventTracker__vfunc_23(igEventTrackerView *arg0) {
    int n;
    FUN_0030cf20(arg0->_groups, 0x100);
    FUN_0030cf30(arg0->_groups, 0x20);
    FUN_0030cf40((void *)arg0->_groups);
    FUN_0030cf20(arg0->_classNames, 0x1000);
    FUN_0030cf30(arg0->_classNames, 0x100);
    FUN_0030cf40((void *)arg0->_classNames);
    FUN_0030cf20(arg0->_sourceFileNames, 0x200);
    FUN_0030cf30(arg0->_sourceFileNames, 0x20);
    FUN_0030cf40((void *)arg0->_sourceFileNames);
    FUN_0030cf20(arg0->_annotations, 0x10000);
    FUN_0030cf30(arg0->_annotations, 0x1000);
    FUN_0030cf40((void *)arg0->_annotations);
    FUN_0030cf20(arg0->_sourceFileNames, 0x2000);
    FUN_0030cf30(arg0->_sourceFileNames, 0x100);
    FUN_0030cf40((void *)arg0->_sourceFileNames);
    FUN_002d38d0(arg0->_callStacks, 0x10000);
    FUN_002d38e0((igCallStackTableView *)arg0->_callStacks, 0x1000);
    FUN_002d38f0((igCallStackTableView *)arg0->_callStacks);
    if (arg0->_callStackTracer->vfunc_25() != 0) {
        FUN_002eb090((int)arg0->_locations, 0x4000);
        FUN_002eb0a0((int)arg0->_locations, 0x4000);
        FUN_002eb0b0(arg0->_locations);
    }
    n = arg0->_capacity * 0x14;
    if (n >= arg0->_eventRecords->_count) {
        List_Reserve((igDataList *)arg0->_eventRecords, n, 1);
    }
    arg0->vfunc_50(arg0->_capacity * 2);
    FUN_002dca90();
    arg0->_codeReferenceAddress = (int)FUN_002dca90;
    FUN_002dcaa0(arg0, 1);
}

void Gap__Core__igEventTracker__vfunc_24(igEventTrackerView *arg0) {
    int busy = (arg0->getFlags() & 2) != 0;
    if (!busy) {
        arg0->_flags = arg0->_flags | 2;
        FUN_0030cfa0((igStringTableView *)arg0->_groups);
        FUN_0030cfa0((igStringTableView *)arg0->_classNames);
        FUN_0030cfa0((igStringTableView *)arg0->_sourceFileNames);
        FUN_0030cfa0((igStringTableView *)arg0->_annotations);
        FUN_0030cfa0((igStringTableView *)arg0->_sourceFileNames);
        FUN_002d3950((igCallStackTableView *)arg0->_callStacks);
        if (arg0->_callStackTracer->vfunc_25() != 0) {
            FUN_002eb150(arg0->_locations);
        }
        if (0 <= arg0->_eventRecords->_capacity) {
            arg0->_eventRecords->_count = 0;
        } else {
            List_Resize(arg0->_eventRecords, 0, 1);
        }
        if (!(0 < arg0->_eventRecords->_count)) {
            List_Reserve((igDataList *)arg0->_eventRecords, 0, 1);
        }
        FUN_002dcaa0(arg0, 0);
        arg0->_flags = arg0->_flags & ~2;
    }
}

void Gap__Core__igEventTracker__vfunc_25(igEventTrackerView *arg0) {
    EventTrackerScopedLock guard(arg0->_lock);
    arg0->_count = 0;
    FUN_0030d050(arg0->_groups);
    FUN_0030d050(arg0->_classNames);
    FUN_0030d050(arg0->_sourceFileNames);
    FUN_0030d050(arg0->_annotations);
    FUN_0030d050(arg0->_sourceFileNames);
    FUN_002d3a20((igCallStackTableView *)arg0->_callStacks);
    igTDataList<signed char> *l = arg0->_eventRecords;
    if (0 <= l->_capacity) {
        l->_count = 0;
    } else {
        List_Resize(l, 0, 1);
    }
    arg0->vfunc_50(arg0->_hashIndex->_capacity);
}

void Gap__Core__igEventTracker__vfunc_28(int *arg0, char *arg1, char *arg2, int *arg3) {
    int acc;
    int c;
    int sh;
    int t;
    sh = 0;
    acc = 0;
    arg2 = (char *)(*(int *)(*(char **)(arg1 + 80) + 16) + (int)arg2);
    do {
        c = *arg2;
        t = c & 0x7F;
        arg2++;
        t = t << sh;
        c = c & 0x80;
        acc |= t;
        if (c == 0) break;
        sh += 7;
    } while (1);
    *arg3 = acc;
    if (*arg3 >= 0x20) {
        *arg0 = g_resultFailure.v;
    } else {
        *arg0 = g_resultSuccess.v;
    }
}

void Gap__Core__igEventTracker__vfunc_29(int *arg0, char *arg1, char *arg2, int *arg3) {
    int acc2;
    int acc;
    int c;
    int sh;
    int sh2;
    int c2;
    int t;
    int t2;
    sh = 0;
    acc = 0;
    arg2 = (char *)(*(int *)(*(char **)(arg1 + 80) + 16) + (int)arg2);
    do {
        c = *arg2;
        t = c & 0x7F;
        arg2++;
        t = t << sh;
        c = c & 0x80;
        acc |= t;
        if (c == 0) break;
        sh += 7;
    } while (1);
    if (acc >= 0x20) {
        *arg0 = g_resultFailure.v;
        return;
    }
    {
    char *q = arg2 + 1;
    c = *arg2;
    if (c > DAT_004c1ea8[0]) {
        *arg0 = g_resultFailure.v;
        return;
    }
    acc2 = 0;
    sh2 = 0;
    do {
        c2 = *q;
        t2 = c2 & 0x7F;
        q++;
        t2 = t2 << sh2;
        c2 = c2 & 0x80;
        acc2 |= t2;
        if (c2 == 0) break;
        sh2 += 7;
    } while (1);
    if (acc2 & 1) {
        *arg3 = ((unsigned char)q[0]) | ((((unsigned char)q[1]) << 8) | ((((unsigned char)q[3]) << 24) | (((unsigned char)q[2]) << 16)));
    } else {
        *arg0 = g_resultFailure.v;
        return;
    }
    *arg0 = g_resultSuccess.v;
    }
}

/* An unaligned little-endian word of an event record. */
static inline void readWord(const char *p, void *out) {
    *(int *)out = ((unsigned char)p[0]) | ((((unsigned char)p[1]) << 8) | ((((unsigned char)p[3]) << 24) | (((unsigned char)p[2]) << 16)));
}

static inline void readVarint(const char *p, int *out) {
    int shift = 0;
    *out = 0;
    for (;;) {
        *out |= (*p & 0x7F) << shift;
        if ((*p++ & 0x80) == 0) break;
        shift += 7;
    }
}

/* The varint that follows the word slot 29 reads: the record starts with its type (a varint below
 * 32), a version byte no newer than the tracker's and a flags varint whose bit 0 says the two
 * values are present. The word itself is read and dropped. */
void Gap__Core__igEventTracker__vfunc_30(int *result, igEventTracker *self, char *record, int *value) {
    int flags;
    int type;
    int byte;
    int shift;
    int flagShift;
    int flagByte;
    int bits;
    int flagBits;
    shift = 0;
    type = 0;
    record = (char *)(((igCharList *)self->_eventRecords)->_data + (int)record);
    do {
        byte = *record;
        bits = byte & 0x7F;
        record++;
        bits = bits << shift;
        byte = byte & 0x80;
        type |= bits;
        if (byte == 0) break;
        shift += 7;
    } while (1);
    if (type >= 0x20) {
        *result = g_resultFailure.v;
        return;
    }
    {
    char *q = record + 1;
    byte = *record;
    if (byte > DAT_004c1ea8[0]) {
        *result = g_resultFailure.v;
        return;
    }
    flags = 0;
    flagShift = 0;
    do {
        flagByte = *q;
        flagBits = flagByte & 0x7F;
        q++;
        flagBits = flagBits << flagShift;
        flagByte = flagByte & 0x80;
        flags |= flagBits;
        if (flagByte == 0) break;
        flagShift += 7;
    } while (1);
    if (flags & 1) {
        int word;
        readWord(q, &word);
        readVarint(q + 4, value);
    } else {
        *result = g_resultFailure.v;
        return;
    }
    *result = g_resultSuccess.v;
    }
}

void Gap__Core__igEventTracker__vfunc_33(igEventTrackerView *arg0, int arg1, int arg2, int arg3, int *arg4, int *arg5, int *arg6, int *arg7)
{
    int var_s1;
    int var_s0;
    EventRecord ev;
    int key = arg3;
    var_s1 = 0;
    var_s0 = 0;
    FUN_002e2130((int)&ev);
    if (arg2 == -1) {
        arg2 = arg0->_count - 1;
    }
    *arg4 = 0;
    *arg5 = 0;
    *arg6 = 0;
    *arg7 = 0;
    while (var_s1 < arg1) {
        var_s0 = arg0->vfunc_34(var_s0);
        var_s1 += 1;
    }
    for (;;) {
        int c = arg0->vfunc_27(var_s0, &ev).Code();
        if (c != g_resultSuccess.v) break;
        if (ev.str != 0 && *ev.str != 0 && strcmp(ev.str, key) == 0) {
            switch (ev.type) {
            case 6:
                *arg4 += 1;
                *arg6 = *arg6 + ev.getVal();
                break;
            case 8:
                *arg5 += 1;
                *arg7 = *arg7 + ev.getVal();
                break;
            }
        }
        var_s0 = arg0->vfunc_34(var_s0);
        var_s1 += 1;
        if (var_s1 >= arg2 || var_s0 == -1) break;
    }
    FUN_002e2300(&ev, (long long)(-1));
}

int Gap__Core__igEventTracker__vfunc_31(igEventTrackerView *arg0, int arg1) {
    int out;
    int k;
    int idx;
    int n;
    int i;

    k = arg0->vfunc_48(arg1);
    i = 0;
    n = arg0->_hashIndex->_count;
    for (;;) {
        idx = arg0->_hashIndex->_data[k];
        if (idx == -1) {
            return -1;
        }
        arg0->vfunc_29(idx, &out);
        if (out == arg1) {
            return idx;
        }
        k++;
        if (k >= n) {
            k = 0;
        }
        i++;
        if (i >= n) {
            return -1;
        }
    }
}

int Gap__Core__igEventTracker__vfunc_34(igEventTrackerView *self, int arg1) {
    igTDataList<signed char> *q;
    signed char *p;
    int n;
    int c;

    q = self->_eventRecords;
    n = q->_count;
    if (n < arg1) {
        return -1;
    }
    p = q->_data + arg1;
    if ((unsigned int)*p++ >= 0x20U) {
        return -1;
    }
    c = *p;
    if (DAT_004c1ea8[0] < c) {
        return -1;
    }
    arg1 = arg1 + (c + 2);
    if (arg1 >= n) {
        arg1 = -1;
    }
    return arg1;
}

/* Map a hash value to a bucket of the tracker's hash index: the value modulo the count stored at
 * +8 of the `_hashIndex` object, or 0 while that count is 0. */

unsigned int Gap__Core__igEventTracker__vfunc_48(igEventTracker *self, unsigned int hash) {
    unsigned int bucketCount;

    bucketCount = *(int *)((char *)(self->_hashIndex) + 8);
    if (bucketCount != 0) {
        return hash % bucketCount;
    }
    return 0U;
}

void Gap__Core__igEventTracker__vfunc_49(igEventTrackerView *self, int arg1, int arg2) {
    int sp9C;
    int idx, tried, n, half, cnt;
    igTDataList<int> *tb;
    int *slot;
    int v;
loop:
    n = self->_hashIndex->_count;
    half = n >> 1;
    if (n < 0) half = (n + 1) >> 1;
    tried = 0;
    bool z = !(n != 0);
    if (z) goto done;
    {
        idx = self->vfunc_48(arg1);
again:
        tb = self->_hashIndex;
        slot = tb->_data + idx;
        v = *slot;
        if (v == -1) {
            cnt = tb->_count;
            if (cnt != 0 && idx >= 0 && idx < cnt) *slot = arg2;
        } else {
            self->vfunc_29(v, &sp9C);
            if (sp9C == arg1) {
                tb = self->_hashIndex;
                cnt = tb->_count;
                if (cnt != 0 && idx >= 0 && idx < cnt) tb->_data[idx] = arg2;
            } else {
                idx += 1;
                if (idx >= n) idx = 0;
                tried += 1;
                if (tried >= half) {
                    self->vfunc_50(n * 2);
                    goto loop;
                }
                goto again;
            }
        }
    }
done: ;
}

static inline void setCount(igTDataList<int> *l, int n) {
    if (n >= 0) {
        if (n <= l->_capacity) {
            l->_count = n;
        } else {
            List_Resize((void *)l, n, 4);
        }
    }
}

void Gap__Core__igEventTracker__vfunc_50(igEventTrackerView *self, int n) {
    char *base;
    int value;
    char *end;
    char *p;
    int len;
    int offset;
    FUN_002dcc40((int)self, n);
    if (n >= self->_hashIndex->_count) {
        List_Reserve((igDataList *)self->_hashIndex, n, 4);
    }
    setCount(self->_hashIndex, n);
    {
        int count = self->_hashIndex->_count;
        int *data = self->_hashIndex->_data;
        int i;
        for (i = 0; i < count; i++) {
            data[i] = DAT_004c2120[0];
        }
    }
    base = (char *)self->_eventRecords->_data;
    p = base;
    end = base + self->_eventRecords->_count;
    while (p < end) {
        offset = p - base;
        len = p[1];
        p += 2;
        if (self->vfunc_29(offset, &value) == g_resultSuccess) {
            self->vfunc_49(value, offset);
        }
        p += len;
    }
}

int FUN_002e14b0(void *arg0, int arg1) {
    int temp_a1;
    int idx;

    if (arg1 >= 0 && arg1 < 0x20) {
        idx = arg1 * 4;
        temp_a1 = *(int *)((char *)(idx + (int)arg0) + 96);
        if (temp_a1 != -1) {
            return ((int)FUN_0030d1d0((int *)(*(int *)((char *)(arg0) + 48)), temp_a1));
        }
    }
    return 0;
}

int FUN_002e1500(void *arg0, int arg1) {
    int off;
    int temp_a1;

    if (arg1 >= 0 && arg1 < 0x20) {
        off = arg1 * 4;
        temp_a1 = *(int *)((char *)(off + (int)arg0) + 228);
        if (temp_a1 != -1) {
            return ((int)FUN_0030d1d0((int *)(*(int *)((char *)(arg0) + 48)), temp_a1));
        }
    }
    return 0;
}

int FUN_002e1550(igEventTrackerView *tracker, int type) {
    int t;
    if (type >= 0 && type < 32) {
        t = tracker->_markerTypeNameOffsets[type];
        if (t != -1) {
            return ((int)FUN_0030d1d0((int *)tracker->_names, t));
        }
    }
    return 0;
}

int FUN_002e15a0(igEventTrackerView *tracker, int type) {
    int offset;

    if (type >= 0 && type < 16) {
        offset = tracker->_notificationTypeNameOffsets[type];
        if (offset != -1) {
            return ((int)FUN_0030d1d0((int *)tracker->_names, offset));
        }
    }
    return 0;
}

int FUN_002e15f0(void *arg0, int arg1) {
    int t; if (arg1 >= 0 && arg1 < 0x40) { t = *(int *)((arg1 << 2) + (int)arg0 + 548); if (t != -1) return ((int)FUN_0030d1d0((int *)(*(int *)((char *)arg0 + 48)), t)); } return 0;
}

igResult Gap__Core__igEventTracker__vfunc_39(igEventTrackerView *self, int addr, int format, long long output, long long outputSize) {
    char buf[256];
    char name[256];
    int offset;
    int line;
    igResult r = self->vfunc_40(addr, buf, 255, &offset, name, 255, &line);
    self->_callStackTracer->vfunc_28(addr, buf, offset, name, line, format, output, outputSize);
    return r;
}

igResult Gap__Core__igEventTracker__vfunc_40(igEventTrackerView *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line) {
    int s0;
    if (FUN_002eb210((void *)self->_locations) != 0) {
        s0 = self->_locations->vfunc_27(addr, buf, size, offset, name, nameSize, line).v;
        if (s0 == g_resultFailure.v) {
            if (self->_callStackTracer->vfunc_25() != 0) {
                s0 = self->_callStackTracer->vfunc_27(addr, buf, size, offset, name, nameSize, line).v;
                self->_locations->vfunc_29(addr, buf, *offset, name, *line);
                DAT_00586e08[0] = DAT_00586e08[0] + 1;
                goto join;
            }
        }
        DAT_00586e10[0] += 1;
    } else {
        s0 = self->_callStackTracer->vfunc_27(addr, buf, size, offset, name, nameSize, line).v;
        DAT_00586e08[0] = DAT_00586e08[0] + 1;
    }
join:
    DAT_00586e00[0] += 1;
    return igResult(s0);
}

void Gap__Core__igEventTracker__vfunc_42(igEventTrackerView *self) {
    int s = 0;
    while (s != -1) {
        self->vfunc_41(s);
        s = self->vfunc_34(s);
    }
}

static inline bool hasFlag(const igEventTrackerView *tracker, unsigned mask) { return (tracker->_flags & mask) != 0; }

igResult Gap__Core__igEventTracker__vfunc_44(igEventTrackerView *arg1, int arg2) {
    bool had;
    bool trk;
    int r;
    igObject *a;
    igObject *old;
    igIGBFileView *o;
    had = hasFlag(arg1, 2);
    arg1->_flags = arg1->_flags | 2;
    trk = hasFlag(arg1, 4);
    if (trk == false) {
        arg1->vfunc_45();
    }
    {
    igSmartPointer<igIGBFileView> sp7C(((igIGBFileView *)FUN_002c37e0((int)(((igObject *)igObject_GetAllocator((int)arg1))))));
    a = ((igObject *)igObject_GetAllocator((int)arg1));
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = (igObject *)o->_temporaryMemoryPool;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->_temporaryMemoryPool = (igMemoryPoolView *)a;
    a = ((igObject *)igObject_GetAllocator((int)arg1));
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = (igObject *)o->_objectMemoryPool;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->_objectMemoryPool = (igMemoryPoolView *)a;
    a = ((igObject *)igObject_GetAllocator((int)arg1));
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = (igObject *)o->_dataMemoryPool;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->_dataMemoryPool = (igMemoryPoolView *)a;
    sp7C.p->_useMemoryPoolAssignmentsState = 1;
    FUN_002d8620((int)sp7C.p, (int)arg1, DAT_004c1ed8[0], 0);
    r = sp7C.p->vfunc_28(arg2);
    }
    arg1->_flags = had ? (arg1->_flags | 2) : (arg1->_flags & ~2);
    return igResult(r);
}

void Gap__Core__igEventTracker__vfunc_45(igEventTrackerView *self) {
    int a;
    int b;
    char bufA[256];
    char bufB[256];
    int count;
    int i;
    unsigned int *row;
    bool wasSet;
    count = ((igCallStackTableView *)self->_callStacks)->vfunc_23();
    a = 0;
    b = 0;
    wasSet = (self->getFlags() & 2) != 0;
    self->_flags |= 2;
    row = ((igCallStackTableView *)self->_callStacks)->vfunc_25(0);
    if (row != 0) {
        for (i = 0; i < count; i++) {
            while (*row != 0) {
                self->vfunc_40(*row, bufA, 255, &a, bufB, 255, &b);
                row++;
            }
            row++;
        }
        self->_flags |= 4;
        { int f; if (wasSet) { f = self->_flags | 2; } else { f = self->_flags & ~2; } self->_flags = f; }
    }
}

void Gap__Core__igEventTracker__vfunc_46(igEventTrackerView *self)
{
    self->_callStackTracer->vfunc_29();
}

void Gap__Core__igEventTracker__vfunc_47(igEventTrackerView *self)
{
    self->_callStackTracer->vfunc_30();
}

void Gap__Core__igEventTracker__vfunc_13(igEventTrackerView *self) {
    int i;
    self->_eventTag[0] = 0;
    self->_eventTag[255] = 0;
    self->_eventClassName[0] = 0;
    self->_eventClassName[255] = 0;
    if (((Cfg * *)g_objectSystem)[0] != 0) {
        self->_eventTypeFilterFlags = ((Cfg * *)g_objectSystem)[0]->a;
        self->_markerTypeFilterFlags = ((Cfg * *)g_objectSystem)[0]->b;
        self->_notificationTypeFilterFlags = ((Cfg * *)g_objectSystem)[0]->c;
        self->_notificationCodeFilterFlags = ((Cfg * *)g_objectSystem)[0]->d;
    }
    FUN_0030cf20(self->_names, 0x1000);
    FUN_0030cf30(self->_names, 0x100);
    FUN_0030cf40((void *)self->_names);
    memset(self->_eventFormatOffsets, 0xFF, 0x80);
    memset(self->_eventTypeNameOffsets, 0xFF, 0x80);
    memset(self->_markerTypeNameOffsets, 0xFF, 0x80);
    memset(self->_notificationTypeNameOffsets, 0xFF, 0x40);
    memset(self->_notificationCodeNameOffsets, 0xFF, 0x100);
    for (i = 0; i < 32; i++) {
        self->_eventTypeNameOffsets[i] = FUN_0030d300(self->_names, DAT_004c1ee0[i]);
    }
    for (i = 0; i < 32; i++) {
        self->_markerTypeNameOffsets[i] = FUN_0030d300(self->_names, DAT_004c1f60[i]);
    }
    for (i = 0; i < 16; i++) {
        self->_notificationTypeNameOffsets[i] = FUN_0030d300(self->_names, DAT_004c1fe0[i]);
    }
    for (i = 0; i < 64; i++) {
        self->_notificationCodeNameOffsets[i] = FUN_0030d300(self->_names, DAT_004c2020[i]);
    }
}

int FUN_002e2130(int arg0) {
    FUN_002e2350(arg0);
    return arg0;
}

int FUN_002e2160(int arg0, int arg1) {
    memcpy(arg0, arg1, 0x94);
    return arg0;
}

void *FUN_002e2190(void *arg0, int arg1, void *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18) {
    FUN_002e2350((int)arg0);
    *(int *)((char *)arg0 + 0) = arg1;
    *(void **)((char *)arg0 + 8) = arg2;
    *(int *)((char *)arg0 + 12) = arg3;
    *(int *)((char *)arg0 + 16) = arg4;
    *(int *)((char *)arg0 + 44) = arg5;
    *(int *)((char *)arg0 + 48) = arg6;
    *(int *)((char *)arg0 + 52) = arg7;
    *(int *)((char *)arg0 + 56) = arg_sp0;
    *(int *)((char *)arg0 + 68) = arg_sp8;
    *(int *)((char *)arg0 + 72) = arg_sp10;
    *(int *)((char *)arg0 + 64) = arg_sp18;
    return arg0;
}

void *FUN_002e2250(void *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8) {
    FUN_002e2350((int)arg0);
    *(int *)((char *)arg0 + 0) = 0xD;
    *(int *)((char *)arg0 + 20) = arg1;
    *(int *)((char *)arg0 + 24) = arg2;
    *(int *)((char *)arg0 + 28) = arg3;
    *(int *)((char *)arg0 + 44) = arg4;
    *(int *)((char *)arg0 + 48) = arg5;
    *(int *)((char *)arg0 + 52) = arg6;
    *(int *)((char *)arg0 + 56) = arg7;
    *(int *)((char *)arg0 + 68) = arg_sp0;
    *(int *)((char *)arg0 + 72) = arg_sp8;
    return arg0;
}

void *FUN_002e2300(void *arg0, long long arg1) {
    if (arg0 != 0) {
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasB(arg0);
        }
    }
    return arg0;
}

void FUN_002e2350(int arg0) {
    memset(arg0, 0, 148);
}

int FUN_002e2360(void *arg0) {
    int i;
    for (i = 0; i < 0x10; i++) {
        if (!(*(int *)((char *)(arg0) + 80) & (3 << (i * 2)))) {
            return i;
        }
    }
    return 0;
}

int FUN_002e23b0(struct BitSlots *arg0, int arg1)
{
  if (arg1 < 0x10)
  {
    return (arg0->bits >> (arg1 * 2)) & 3;
  }
  return 0;
}

int FUN_002e23e0(int arg0, int arg1) {
    if (arg1 < 0x10) {
        return *(int *)((char *)(((arg1 << 2) + arg0)) + 84);
    }
    return -1;
}

void FUN_002e2400(void *arg0, int arg1, int arg2) {
    int t, idx;
    char *p;
    if (arg1 < 0x10) {
        t = arg1 * 2;
        *(int *)((char *)(arg0) + 80) = (1 << t) | (*(int *)((char *)(arg0) + 80) & ~(3 << t));
        idx = arg1 << 2; p = (char *)idx + (int)arg0; *(int *)(p + 84) = arg2;
    }
}

int FUN_002e2450(int arg0, int arg1) {
    int var_v0;

    var_v0 = -1;
    if (arg1 < 0x10) {
        var_v0 = *(int *)((char *)((arg1 << 2) + arg0) + 84);
    }
    return var_v0;
}

void FUN_002e2470(void *arg0, int arg1, int arg2) {
    int temp_a5;

    if (arg1 < 0x10) {
        temp_a5 = arg1 * 2;
        *(int *)((char *)(arg0) + 80) = (int)((int) ((2 << temp_a5) | (*(int *)((char *)(arg0) + 80) & ~(3 << temp_a5))));
        *(int *)((arg1 << 2) + (int)arg0 + 84) = arg2;
    }
}

int FUN_002e24c0(int arg0, int arg1) {
    int r = 0; if (arg1 < 0x10) { r = arg1 * 4; r += arg0; r = *(int *)((char *)r + 84); } return r;
}

void FUN_002e24e0(void *arg0, int arg1, int arg2) {
    int temp_a4;
    int idx;
    char *p;
    if (arg1 < 0x10) {
        temp_a4 = 3 << (arg1 * 2);
        *(int *)((char *)(arg0) + 80) = (int)((int) (temp_a4 | (*(int *)((char *)(arg0) + 80) & ~temp_a4)));
        idx = arg1 * 4;
        p = (char *)(idx + (int)arg0);
        *(int *)(p + 84) = arg2;
    }
}

void FUN_002e2520(int arg0, int arg1, void *arg2) {
    if ((arg2 != 0) && (arg1 < 0x10)) {
        *(int *)((char *)arg2 + 0) = FUN_002e2450(arg0, arg1);
        *(int *)((char *)arg2 + 4) = FUN_002e2450(arg0, arg1 + 1);
        *(int *)((char *)arg2 + 8) = FUN_002e2450(arg0, arg1 + 2);
    }
}

