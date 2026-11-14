void igEventTracker_CodeReference(void)
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

void igEventTracker_SetThreadSafe(igEventTrackerView *self, int open) {
    if (open != 0) {
        if (self->_lock == 0) {
            igSmartPointer<igSemaphoreView> created(((igSemaphoreView *)igSemaphore_Create(((int)igObject_GetAllocator((int)self)))));
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

void igEventTracker_SetCapacity(int a0, int a1)
{
    *(int *)((char *)a0 + 36) = a1;
}

int igEventTracker_GetCount(int *p)
{
    return *(int *)((char *)p + 40);
}

void igEventTracker_SetEventTag(igEventTrackerView *tracker, int tag) {
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
        tracker->_eventTagOffset = igStringTable_FindOrAddString(tracker->_groups, (int)tracker->_eventTag);
    } else {
        tracker->_eventTagOffset = -1;
    }
    tracker->_flags = tracker->_flags & ~2;
}

void igEventTracker_SetEventClassName(igEventTrackerView *tracker, int className) {
    ScopedLock guard(tracker->_lock);
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
        tracker->_eventClassNameOffset = igStringTable_FindOrAddString(tracker->_classNames, (int)tracker->_eventClassName);
    } else {
        tracker->_eventClassNameOffset = -1;
    }
    tracker->_flags = tracker->_flags & ~2;
}

void igEventTracker_Initialize(igEventTrackerView *arg0) {
    int n;
    igStringTable_SetCapacity(arg0->_groups, 0x100);
    igStringTable_SetHashCapacity(arg0->_groups, 0x20);
    igStringTable_Reserve((void *)arg0->_groups);
    igStringTable_SetCapacity(arg0->_classNames, 0x1000);
    igStringTable_SetHashCapacity(arg0->_classNames, 0x100);
    igStringTable_Reserve((void *)arg0->_classNames);
    igStringTable_SetCapacity(arg0->_sourceFileNames, 0x200);
    igStringTable_SetHashCapacity(arg0->_sourceFileNames, 0x20);
    igStringTable_Reserve((void *)arg0->_sourceFileNames);
    igStringTable_SetCapacity(arg0->_annotations, 0x10000);
    igStringTable_SetHashCapacity(arg0->_annotations, 0x1000);
    igStringTable_Reserve((void *)arg0->_annotations);
    igStringTable_SetCapacity(arg0->_sourceFileNames, 0x2000);
    igStringTable_SetHashCapacity(arg0->_sourceFileNames, 0x100);
    igStringTable_Reserve((void *)arg0->_sourceFileNames);
    igCallStackTable_SetCapacity(arg0->_callStacks, 0x10000);
    igCallStackTable_SetHashCapacity((igCallStackTableView *)arg0->_callStacks, 0x1000);
    igCallStackTable_ApplyCapacity((igCallStackTableView *)arg0->_callStacks);
    if (arg0->_callStackTracer->vfunc_25() != 0) {
        StringPool_SetBlockSize((int)arg0->_locations, 0x4000);
        igLocationTable_SetHashCapacity((int)arg0->_locations, 0x4000);
        igLocationTable_Allocate(arg0->_locations);
    }
    n = arg0->_capacity * 0x14;
    if (n >= arg0->_eventRecords->_count) {
        List_Reserve((igDataList *)arg0->_eventRecords, n, 1);
    }
    arg0->vfunc_50(arg0->_capacity * 2);
    igEventTracker_CodeReference();
    arg0->_codeReferenceAddress = (int)igEventTracker_CodeReference;
    igEventTracker_SetThreadSafe(arg0, 1);
}

void igEventTracker_Shutdown(igEventTrackerView *arg0) {
    int busy = (arg0->getFlags() & 2) != 0;
    if (!busy) {
        arg0->_flags = arg0->_flags | 2;
        igStringTable_Clear((igStringTableView *)arg0->_groups);
        igStringTable_Clear((igStringTableView *)arg0->_classNames);
        igStringTable_Clear((igStringTableView *)arg0->_sourceFileNames);
        igStringTable_Clear((igStringTableView *)arg0->_annotations);
        igStringTable_Clear((igStringTableView *)arg0->_sourceFileNames);
        igCallStackTable_Clear((igCallStackTableView *)arg0->_callStacks);
        if (arg0->_callStackTracer->vfunc_25() != 0) {
            igLocationTable_Clear(arg0->_locations);
        }
        if (0 <= arg0->_eventRecords->_capacity) {
            arg0->_eventRecords->_count = 0;
        } else {
            List_Resize(arg0->_eventRecords, 0, 1);
        }
        if (!(0 < arg0->_eventRecords->_count)) {
            List_Reserve((igDataList *)arg0->_eventRecords, 0, 1);
        }
        igEventTracker_SetThreadSafe(arg0, 0);
        arg0->_flags = arg0->_flags & ~2;
    }
}

void igEventTracker_Reset(igEventTrackerView *arg0) {
    ScopedLock guard(arg0->_lock);
    arg0->_count = 0;
    igStringTable_RemoveAll(arg0->_groups);
    igStringTable_RemoveAll(arg0->_classNames);
    igStringTable_RemoveAll(arg0->_sourceFileNames);
    igStringTable_RemoveAll(arg0->_annotations);
    igStringTable_RemoveAll(arg0->_sourceFileNames);
    igCallStackTable_RemoveAllCallStacks((igCallStackTableView *)arg0->_callStacks);
    igTDataList<signed char> *l = arg0->_eventRecords;
    if (0 <= l->_capacity) {
        l->_count = 0;
    } else {
        List_Resize(l, 0, 1);
    }
    arg0->vfunc_50(arg0->_hashIndex->_capacity);
}

void igEventTracker_ReadEventType(int *arg0, char *arg1, char *arg2, int *arg3) {
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

void igEventTracker_ReadEventKey(int *arg0, char *arg1, char *arg2, int *arg3) {
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
void igEventTracker_ReadEventValue(int *result, igEventTracker *self, char *record, int *value) {
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

/* Walks the events from `first` to `last` totalling memory: bytes allocated and freed, the net
 * amount and its peak, the largest allocation, and the net amount at the chosen occurrence of two
 * markers (-1: the last one); then counts the allocations in that range still outstanding. */
void Gap__Core__igEventTracker__vfunc_32(igEventTrackerView *self, int first, int last, int *eventCount, int *typeCounts,
                                         int *outstandingCount, unsigned int *allocatedBytes, unsigned int *freedBytes,
                                         unsigned int *netBytes, unsigned int *peakNetBytes, unsigned int *largestAllocation,
                                         unsigned int *netAtMarkerA, int markerA, int markerAOccurrence,
                                         unsigned int *netAtMarkerB, int markerB, int markerBOccurrence) {
    int i = 0;
    int offset = 0;
    EventRecord record;
    int markerASeen;
    int markerBSeen;
    int count;
    int type;
    igEventTracker_InitEvent((int)&record);
    markerASeen = -1;
    markerBSeen = -1;
    count = self->_hashIndex->_count;
    if (last == -1) {
        last = self->_count - 1;
    }
    *eventCount = 0;
    if (typeCounts != 0) {
        memset(typeCounts, 0, 128);
    }
    *outstandingCount = 0;
    *allocatedBytes = 0;
    *freedBytes = 0;
    *netBytes = 0;
    *peakNetBytes = 0;
    *largestAllocation = 0;
    *netAtMarkerA = 0;
    *netAtMarkerB = 0;
    for (; i < first; i++) {
        offset = self->vfunc_34(offset);
    }
    do {
        if (self->vfunc_27(offset, &record) != g_resultSuccess) break;
        type = record.type;
        (*eventCount)++;
        if (typeCounts != 0 && type >= 0 && type < 32) {
            typeCounts[type]++;
        }
        switch (type) {
        case kMemoryAllocation:
            *allocatedBytes += record.val;
            *netBytes = *allocatedBytes - *freedBytes;
            if (*peakNetBytes < *netBytes) *peakNetBytes = *netBytes;
            if (*largestAllocation < (unsigned int)record.val) *largestAllocation = record.val;
            break;
        case kMemoryDeallocation:
            *freedBytes += record.val;
            *netBytes = *allocatedBytes - *freedBytes;
            break;
        case kMarker:
            if (markerA == record.markerType) {
                markerASeen++;
                if (markerASeen == markerAOccurrence || markerAOccurrence == -1) *netAtMarkerA = *netBytes;
            }
            if (markerB == record.markerType) {
                markerBSeen++;
                if (markerBSeen == markerBOccurrence || markerBOccurrence == -1) *netAtMarkerB = *netBytes;
            }
            break;
        case kEventTypeAny:
        case kMemoryDetach:
        case kMemoryRead:
        case kMemoryWrite:
        case kObjectAllocation:
        case kObjectDetach:
        case kObjectDeallocation:
        case kObjectRead:
        case kObjectWrite:
        case kMemberRead:
        case kMemberWrite:
        case kNotification:
        case kCustom:
            break;
        }
        offset = self->vfunc_34(offset);
        i++;
    } while (i < last && offset != -1);
    for (i = 0; i < count; i++) {
        offset = self->_hashIndex->_data[i];
        if (offset != -1 && self->vfunc_27(offset, &record) != g_resultFailure) {
            if (record.index >= first && record.index <= last) {
                int type = record.type;
                if (record.getType() != kMemoryDeallocation && type != kObjectDeallocation && type != kMemoryDetach && type != kObjectDetach) {
                    (*outstandingCount)++;
                }
            }
        }
    }
    igEventTracker_DestructEvent(&record, (long long)(-1));
}

void igEventTracker_GetStatisticsByName(igEventTrackerView *arg0, int arg1, int arg2, int arg3, int *arg4, int *arg5, int *arg6, int *arg7)
{
    int var_s1;
    int var_s0;
    EventRecord ev;
    int key = arg3;
    var_s1 = 0;
    var_s0 = 0;
    igEventTracker_InitEvent((int)&ev);
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
        int c = arg0->vfunc_27(var_s0, &ev).get();
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
    igEventTracker_DestructEvent(&ev, (long long)(-1));
}

int igEventTracker_FindIndex(igEventTrackerView *arg0, int arg1) {
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

int igEventTracker_GetNextEventOffset(igEventTrackerView *self, int arg1) {
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

/* Mark as freed every allocation still recorded whose call stack, below `main`, passes through a
 * function whose name contains `wanted`. */
void igEventTracker_IgnoreEventsInFunction(igEventTrackerView *self, char *wanted) {
    ScopedLock guard(self->_lock);
    int i;
    int n = self->_hashIndex->_count;
    EventRecord record;
    char name[256];
    int offset;
    int line;
    igEventTracker_InitEvent((int)&record);
    if (self->_callStackTracer->vfunc_25() == 0) {
        igEventTracker_DestructEvent(&record, -1);
        return;
    }
    for (i = 0; i < n; i++) {
        int at = self->_hashIndex->_data[i];
        if (at != -1 && self->vfunc_27(at, &record) != g_resultFailure && record.type != 3) {
            int **frame = &record.callStack;
            if (*frame == 0) {
                continue;
            }
            while (**frame != 0) {
                self->vfunc_40(**frame, name, 255, &offset, 0, 0, &line);
                if (strcmp(name, text_main) == 0) {
                    break;
                }
                if (strstr(name, wanted) != 0) {
                    record.type = 3;
                    record.f68 = 0;
                    record.f72 = 0;
                    self->vfunc_26(&record, -1);
                }
                *frame = *frame + 1;
            }
        }
    }
    igEventTracker_DestructEvent(&record, -1);
}

/* Map a hash value to a bucket of the tracker's hash index: the value modulo the count stored at
 * +8 of the `_hashIndex` object, or 0 while that count is 0. */

int Gap__Core__igEventTracker__vfunc_35(igEventTrackerView *self) {
    ScopedLock guard(self->_lock);
    int i;
    int count = self->_hashIndex->_count;
    int offset;
    EventRecord record;
    int outstanding;
    igEventTracker_InitEvent((int)&record);
    outstanding = 0;
    for (i = 0; i < count; i++) {
        offset = self->_hashIndex->_data[i];
        if (offset != -1 && self->vfunc_27(offset, &record) != g_resultFailure) {
            int type = record.type;
            if (record.getType() != kMemoryDeallocation && type != kObjectDeallocation && type != kMemoryDetach && type != kObjectDetach) {
                outstanding++;
            }
        }
    }
    igEventTracker_DestructEvent(&record, (long long)(-1));
    return outstanding;
}

int Gap__Core__igEventTracker__vfunc_36(igEventTrackerView *self, int *cursor) {
    ScopedLock guard(self->_lock);
    int offset;
    int count = self->_hashIndex->_count;
    EventRecord record;
    igEventTracker_InitEvent((int)&record);
    for (; *cursor < count; (*cursor)++) {
        offset = self->_hashIndex->_data[*cursor];
        if (offset != -1 && self->vfunc_27(offset, &record) != g_resultFailure) {
            int type = record.type;
            if (record.getType() != kMemoryDeallocation && type != kObjectDeallocation && type != kMemoryDetach && type != kObjectDetach) {
                (*cursor)++;
                igEventTracker_DestructEvent(&record, (long long)(-1));
                return offset;
            }
        }
    }
    igEventTracker_DestructEvent(&record, (long long)(-1));
    return -1;
}

unsigned int igEventTracker_GetHashBucketIndex(igEventTracker *self, unsigned int hash) {
    unsigned int bucketCount;

    bucketCount = *(int *)((char *)(self->_hashIndex) + 8);
    if (bucketCount != 0) {
        return hash % bucketCount;
    }
    return 0U;
}

void igEventTracker_InsertHashIndex(igEventTrackerView *self, int arg1, int arg2) {
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

void igEventTracker_RebuildHashIndex(igEventTrackerView *self, int n) {
    char *base;
    int value;
    char *end;
    char *p;
    int len;
    int offset;
    igEventTracker_SetCapacity((int)self, n);
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

int igEventTracker_GetEventFormat(void *arg0, int arg1) {
    int temp_a1;
    int idx;

    if (arg1 >= 0 && arg1 < 0x20) {
        idx = arg1 * 4;
        temp_a1 = *(int *)((char *)(idx + (int)arg0) + 96);
        if (temp_a1 != -1) {
            return ((int)igStringTable_GetString((int *)(*(int *)((char *)(arg0) + 48)), temp_a1));
        }
    }
    return 0;
}

int igEventTracker_GetEventTypeName(void *arg0, int arg1) {
    int off;
    int temp_a1;

    if (arg1 >= 0 && arg1 < 0x20) {
        off = arg1 * 4;
        temp_a1 = *(int *)((char *)(off + (int)arg0) + 228);
        if (temp_a1 != -1) {
            return ((int)igStringTable_GetString((int *)(*(int *)((char *)(arg0) + 48)), temp_a1));
        }
    }
    return 0;
}

int igEventTracker_GetMarkerTypeName(igEventTrackerView *tracker, int type) {
    int t;
    if (type >= 0 && type < 32) {
        t = tracker->_markerTypeNameOffsets[type];
        if (t != -1) {
            return ((int)igStringTable_GetString((int *)tracker->_names, t));
        }
    }
    return 0;
}

int igEventTracker_GetNotificationTypeName(igEventTrackerView *tracker, int type) {
    int offset;

    if (type >= 0 && type < 16) {
        offset = tracker->_notificationTypeNameOffsets[type];
        if (offset != -1) {
            return ((int)igStringTable_GetString((int *)tracker->_names, offset));
        }
    }
    return 0;
}

int igEventTracker_GetNotificationCodeName(void *arg0, int arg1) {
    int t; if (arg1 >= 0 && arg1 < 0x40) { t = *(int *)((arg1 << 2) + (int)arg0 + 548); if (t != -1) return ((int)igStringTable_GetString((int *)(*(int *)((char *)arg0 + 48)), t)); } return 0;
}

igResult igEventTracker_FormatAddress(igEventTrackerView *self, int addr, int format, long long output, long long outputSize) {
    char buf[256];
    char name[256];
    int offset;
    int line;
    igResult r = self->vfunc_40(addr, buf, 255, &offset, name, 255, &line);
    self->_callStackTracer->vfunc_28(addr, buf, offset, name, line, format, output, outputSize);
    return r;
}

igResult igEventTracker_ResolveAddress(igEventTrackerView *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line) {
    int s0;
    if (igLocationTable_IsInitialized((void *)self->_locations) != 0) {
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

/* Print the record at `offset` through the tracker's format buffer, 128 characters at a time. */
void igEventTracker_PrintEvent(igEventTrackerView *self, int offset) {
    EventRecord record;
    igEventTracker_InitEvent((int)&record);
    if (self->vfunc_27(offset, &record) != g_resultSuccess) {
        igEventTracker_DestructEvent(&record, -1);
        return;
    }
    self->vfunc_38(&record, self->_formatBuffer, 0x2003);
    {
        ScopedLock guard(self->_lock);
        int length = strlen(self->_formatBuffer);
        int i;
        for (i = 0; i < length; i += 128) {
            char saved;
            char *end = self->_formatBuffer + 128 + i;
            saved = *end;
            *end = 0;
            igReport_Printf(self->_formatBuffer + i);
            igReport_Flush();
            *end = saved;
        }
    }
    igEventTracker_DestructEvent(&record, -1);
}

void igEventTracker_PrintAllEvents(igEventTrackerView *self) {
    int s = 0;
    while (s != -1) {
        self->vfunc_41(s);
        s = self->vfunc_34(s);
    }
}



























































void Gap__Core__igEventTracker__vfunc_43(igEventTrackerView *self) {
    int i;
    int count = self->_hashIndex->_count;
    int offset;
    EventRecord record;
    igEventTracker_InitEvent((int)&record);
    for (i = 0; i < count; i++) {
        offset = self->_hashIndex->_data[i];
        if (offset != -1 && self->vfunc_27(offset, &record) != g_resultFailure) {
            int type = record.type;
            if (record.getType() != kMemoryDeallocation && type != kObjectDeallocation && type != kMemoryDetach && type != kObjectDetach) {
                self->vfunc_41(offset);
            }
        }
    }
    igEventTracker_DestructEvent(&record, (long long)(-1));
}

static inline bool hasFlag(const igEventTrackerView *tracker, unsigned mask) { return (tracker->_flags & mask) != 0; }

igResult igEventTracker_WriteFile(igEventTrackerView *arg1, int arg2) {
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
    igSmartPointer<igIGBFileView> sp7C(((igIGBFileView *)igIGBFile_Create((int)(((igObject *)igObject_GetAllocator((int)arg1))))));
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
    igDirectory_AddObjectRecursive((int)sp7C.p, (int)arg1, DAT_004c1ed8[0], 0);
    r = sp7C.p->vfunc_28(arg2);
    }
    arg1->_flags = had ? (arg1->_flags | 2) : (arg1->_flags & ~2);
    return igResult(r);
}

void igEventTracker_ResolveAllCallStackSymbols(igEventTrackerView *self) {
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

void Gap__Core__igEventTracker__resetFields(igEventTrackerView *self) {
    int i;
    self->_eventTag[0] = 0;
    self->_eventTag[255] = 0;
    self->_eventClassName[0] = 0;
    self->_eventClassName[255] = 0;
    if (((ObjectSystemView **)g_objectSystem)[0] != 0) {
        self->_eventTypeFilterFlags = ((ObjectSystemView **)g_objectSystem)[0]->eventTrackerEventTypeFilter;
        self->_markerTypeFilterFlags = ((ObjectSystemView **)g_objectSystem)[0]->eventTrackerMarkerTypeFilter;
        self->_notificationTypeFilterFlags = ((ObjectSystemView **)g_objectSystem)[0]->eventTrackerNotificationTypeFilter;
        self->_notificationCodeFilterFlags = ((ObjectSystemView **)g_objectSystem)[0]->eventTrackerNotificationCodeFilter;
    }
    igStringTable_SetCapacity(self->_names, 0x1000);
    igStringTable_SetHashCapacity(self->_names, 0x100);
    igStringTable_Reserve((void *)self->_names);
    memset(self->_eventFormatOffsets, 0xFF, 0x80);
    memset(self->_eventTypeNameOffsets, 0xFF, 0x80);
    memset(self->_markerTypeNameOffsets, 0xFF, 0x80);
    memset(self->_notificationTypeNameOffsets, 0xFF, 0x40);
    memset(self->_notificationCodeNameOffsets, 0xFF, 0x100);
    for (i = 0; i < 32; i++) {
        self->_eventTypeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, DAT_004c1ee0[i]);
    }
    for (i = 0; i < 32; i++) {
        self->_markerTypeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, DAT_004c1f60[i]);
    }
    for (i = 0; i < 16; i++) {
        self->_notificationTypeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, DAT_004c1fe0[i]);
    }
    for (i = 0; i < 64; i++) {
        self->_notificationCodeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, DAT_004c2020[i]);
    }
}

int igEventTracker_InitEvent(int arg0) {
    igEventTracker_ClearEvent(arg0);
    return arg0;
}

int igEventTracker_CopyEvent(int arg0, int arg1) {
    memcpy(arg0, arg1, 0x94);
    return arg0;
}

void *igEventTracker_InitMemoryEvent(void *arg0, int arg1, void *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18) {
    igEventTracker_ClearEvent((int)arg0);
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

void *igEventTracker_InitMarkerEvent(void *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8) {
    igEventTracker_ClearEvent((int)arg0);
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

void *igEventTracker_DestructEvent(void *arg0, long long arg1) {
    if (arg0 != 0) {
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasB(arg0);
        }
    }
    return arg0;
}

void igEventTracker_ClearEvent(int arg0) {
    memset(arg0, 0, 148);
}

int igEventTracker_FindFreeEventDataSlot(void *arg0) {
    int i;
    for (i = 0; i < 0x10; i++) {
        if (!(*(int *)((char *)(arg0) + 80) & (3 << (i * 2)))) {
            return i;
        }
    }
    return 0;
}

int igEventTracker_GetEventDataType(EventRecord *record, int slot)
{
  if (slot < 0x10)
  {
    return (record->slotStates >> (slot * 2)) & 3;
  }
  return 0;
}

int igEventTracker_GetEventDataInt(int arg0, int arg1) {
    if (arg1 < 0x10) {
        return *(int *)((char *)(((arg1 << 2) + arg0)) + 84);
    }
    return -1;
}

void igEventTracker_SetEventDataInt(void *arg0, int arg1, int arg2) {
    int t, idx;
    char *p;
    if (arg1 < 0x10) {
        t = arg1 * 2;
        *(int *)((char *)(arg0) + 80) = (1 << t) | (*(int *)((char *)(arg0) + 80) & ~(3 << t));
        idx = arg1 << 2; p = (char *)idx + (int)arg0; *(int *)(p + 84) = arg2;
    }
}

int igEventTracker_GetEventDataUnsigned(int arg0, int arg1) {
    int var_v0;

    var_v0 = -1;
    if (arg1 < 0x10) {
        var_v0 = *(int *)((char *)((arg1 << 2) + arg0) + 84);
    }
    return var_v0;
}

void igEventTracker_SetEventDataUnsigned(void *arg0, int arg1, int arg2) {
    int temp_a5;

    if (arg1 < 0x10) {
        temp_a5 = arg1 * 2;
        *(int *)((char *)(arg0) + 80) = (int)((int) ((2 << temp_a5) | (*(int *)((char *)(arg0) + 80) & ~(3 << temp_a5))));
        *(int *)((arg1 << 2) + (int)arg0 + 84) = arg2;
    }
}

int igEventTracker_GetEventDataString(int arg0, int arg1) {
    int r = 0; if (arg1 < 0x10) { r = arg1 * 4; r += arg0; r = *(int *)((char *)r + 84); } return r;
}

void igEventTracker_SetEventDataString(void *arg0, int arg1, int arg2) {
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

void igEventTracker_GetEventDataUnsigned3(int arg0, int arg1, void *arg2) {
    if ((arg2 != 0) && (arg1 < 0x10)) {
        *(int *)((char *)arg2 + 0) = igEventTracker_GetEventDataUnsigned(arg0, arg1);
        *(int *)((char *)arg2 + 4) = igEventTracker_GetEventDataUnsigned(arg0, arg1 + 1);
        *(int *)((char *)arg2 + 8) = igEventTracker_GetEventDataUnsigned(arg0, arg1 + 2);
    }
}

