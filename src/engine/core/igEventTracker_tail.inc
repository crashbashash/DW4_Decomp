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

void igEventTracker_SetCapacity(int tracker, int capacity)
{
    ((igEventTracker *)tracker)->_capacity = capacity;
}

int igEventTracker_GetCount(int *tracker)
{
    return ((igEventTracker *)tracker)->_count;
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

void igEventTracker_Initialize(igEventTrackerView *self) {
    int n;
    igStringTable_SetCapacity(self->_groups, 0x100);
    igStringTable_SetHashCapacity(self->_groups, 0x20);
    igStringTable_Reserve((void *)self->_groups);
    igStringTable_SetCapacity(self->_classNames, 0x1000);
    igStringTable_SetHashCapacity(self->_classNames, 0x100);
    igStringTable_Reserve((void *)self->_classNames);
    igStringTable_SetCapacity(self->_sourceFileNames, 0x200);
    igStringTable_SetHashCapacity(self->_sourceFileNames, 0x20);
    igStringTable_Reserve((void *)self->_sourceFileNames);
    igStringTable_SetCapacity(self->_annotations, 0x10000);
    igStringTable_SetHashCapacity(self->_annotations, 0x1000);
    igStringTable_Reserve((void *)self->_annotations);
    igStringTable_SetCapacity(self->_sourceFileNames, 0x2000);
    igStringTable_SetHashCapacity(self->_sourceFileNames, 0x100);
    igStringTable_Reserve((void *)self->_sourceFileNames);
    igCallStackTable_SetCapacity(self->_callStacks, 0x10000);
    igCallStackTable_SetHashCapacity((igCallStackTableView *)self->_callStacks, 0x1000);
    igCallStackTable_ApplyCapacity((igCallStackTableView *)self->_callStacks);
    if (self->_callStackTracer->hasSymbols() != 0) {
        StringPool_SetBlockSize((int)self->_locations, 0x4000);
        igLocationTable_SetHashCapacity((int)self->_locations, 0x4000);
        igLocationTable_Allocate(self->_locations);
    }
    n = self->_capacity * 0x14;
    if (n >= self->_eventRecords->_count) {
        List_Reserve((igDataList *)self->_eventRecords, n, 1);
    }
    self->RebuildHashIndex(self->_capacity * 2);
    igEventTracker_CodeReference();
    self->_codeReferenceAddress = (int)igEventTracker_CodeReference;
    igEventTracker_SetThreadSafe(self, 1);
}

void igEventTracker_Shutdown(igEventTrackerView *self) {
    int busy = (self->getFlags() & 2) != 0;
    if (!busy) {
        self->_flags = self->_flags | 2;
        igStringTable_Clear((igStringTableView *)self->_groups);
        igStringTable_Clear((igStringTableView *)self->_classNames);
        igStringTable_Clear((igStringTableView *)self->_sourceFileNames);
        igStringTable_Clear((igStringTableView *)self->_annotations);
        igStringTable_Clear((igStringTableView *)self->_sourceFileNames);
        igCallStackTable_Clear((igCallStackTableView *)self->_callStacks);
        if (self->_callStackTracer->hasSymbols() != 0) {
            igLocationTable_Clear(self->_locations);
        }
        if (0 <= self->_eventRecords->_capacity) {
            self->_eventRecords->_count = 0;
        } else {
            List_Resize(self->_eventRecords, 0, 1);
        }
        if (!(0 < self->_eventRecords->_count)) {
            List_Reserve((igDataList *)self->_eventRecords, 0, 1);
        }
        igEventTracker_SetThreadSafe(self, 0);
        self->_flags = self->_flags & ~2;
    }
}

void igEventTracker_Reset(igEventTrackerView *self) {
    ScopedLock guard(self->_lock);
    self->_count = 0;
    igStringTable_RemoveAll(self->_groups);
    igStringTable_RemoveAll(self->_classNames);
    igStringTable_RemoveAll(self->_sourceFileNames);
    igStringTable_RemoveAll(self->_annotations);
    igStringTable_RemoveAll(self->_sourceFileNames);
    igCallStackTable_RemoveAllCallStacks((igCallStackTableView *)self->_callStacks);
    igTDataList<signed char> *l = self->_eventRecords;
    if (0 <= l->_capacity) {
        l->_count = 0;
    } else {
        List_Resize(l, 0, 1);
    }
    self->RebuildHashIndex(self->_hashIndex->_capacity);
}

/* The value seven bits at a time, low bits first; bit 7 marks a byte that is not the last. */
static inline void encodeUnsigned(char *&p, unsigned int value) {
    do {
        *p = value & 0x7F;
        value >>= 7;
        if (value != 0) {
            *p |= 0x80;
        }
        p++;
    } while (value != 0);
}

/* As encodeUnsigned, ending when the rest is all sign bits; bit 6 of the last byte is the sign, so
 * a byte of pure sign is added when the last data byte's bit 6 disagrees. */
static inline void encodeSigned(char *&p, int value) {
    char *q = p;
    int sign;
    char signBit;
    if (value < 0) {
        sign = -1;
        signBit = 0x40;
    } else {
        sign = 0;
        signBit = 0;
    }
    for (;;) {
        *q = value & 0x7F;
        value >>= 7;
        if (value == sign) {
            if ((*q & 0x40) != signBit) {
                *q |= 0x80;
                q++;
                *q = sign & 0x7F;
            }
            break;
        }
        *q |= 0x80;
        q++;
    }
    p = q + 1;
}

static inline void writeHalf(char *&p, unsigned int half) {
    *p++ = half;
    *p++ = half >> 8;
}

static inline void writeWord(char *&p, unsigned int word) {
    writeHalf(p, word);
    writeHalf(p, word >> 16);
}

static inline unsigned char tracksEventType(const igEventTrackerView &self, int type) {
    return (self._eventTypeFilterFlags & (1 << type)) != 0;
}

static inline unsigned char tracksMarkerType(const igEventTrackerView &self, int type) {
    return (self._markerTypeFilterFlags & (1 << type)) != 0;
}

static inline unsigned char tracksNotificationType(const igEventTrackerView &self, int type) {
    return (self._notificationTypeFilterFlags & (1 << type)) != 0;
}

static inline unsigned char tracksField(const igEventTrackerView &self, int field) {
    return (self._memoryFieldFilterFlags & field) != 0;
}

static inline unsigned char detachesAllocations(const igEventTrackerView &self) {
    return self._detachAllocationsCounter != 0;
}

static inline unsigned char isFlagSet(const igEventTrackerView &self, int flag) {
    return (self._flags & flag) != 0;
}

typedef igSmartPointer<igTDataList<signed char> > igCharListRef;

/* Appends an event to the record list: its type, a length byte, the flags of the fields that follow,
 * then those fields; strings go to the string tables and are stored as offsets. Returns the event's
 * offset, or -1 when its type is filtered out or the tracker is already recording. */
extern "C" int igEventTracker_AddEvent(igEventTrackerView *self, EventRecord *record, int callStackSkip);
int igEventTracker_AddEvent(igEventTrackerView *self, EventRecord *record, int callStackSkip) {
    unsigned int flags;
    int group;
    int className;
    int memberName;
    int annotation;
    int sourceFile;
    int poolName;
    int callStack;
    int slot;
    int state;
    int length;
    int offset;
    char *p;
    if (!tracksEventType(*self, record->type)) {
        return -1;
    }
    switch (record->type) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12:
        break;
    case 13:
        if (!tracksMarkerType(*self, record->markerType)) {
            return -1;
        }
        break;
    case 14:
        if (!tracksNotificationType(*self, record->notificationType)) {
            return -1;
        }
        if (!tracksNotificationType(*self, record->notificationCode)) {
            return -1;
        }
        break;
    case 15:
        break;
    }
    {
        ScopedLock guard(self->_lock);
        char buffer[32];
        if (isFlagSet(*self, 2)) {
            return -1;
        }
        self->_flags |= 2;
        group = -1;
        flags = 0;
        className = -1;
        memberName = -1;
        annotation = -1;
        callStack = -1;
        p = buffer;
        slot = 0;
        sourceFile = -1;
        poolName = -1;
        offset = self->_eventRecords->_count;
        encodeUnsigned(p, record->type);
        if (tracksField(*self, 0x2)) {
            if (record->group != 0 && *record->group != 0) {
                group = igStringTable_FindOrAddString(self->_groups, (int)record->group);
            }
        }
        if (tracksField(*self, 0x40)) {
            if (record->str != 0 && *record->str != 0) {
                className = igStringTable_FindOrAddString(self->_classNames, (int)record->str);
            } else {
                className = self->_eventClassNameOffset;
            }
        }
        if (tracksField(*self, 0x80)) {
            if (record->memberName != 0 && *record->memberName != 0) {
                memberName = igStringTable_FindOrAddString(self->_memberNames, (int)record->memberName);
            }
        }
        if (tracksField(*self, 0x4)) {
            if (record->annotation != 0 && *record->annotation != 0) {
                annotation = igStringTable_FindOrAddString(self->_annotations, (int)record->annotation);
            }
        }
        if (tracksField(*self, 0x8)) {
            if (record->f68 != 0 && *(char *)record->f68 != 0) {
                sourceFile = igStringTable_FindOrAddString(self->_sourceFileNames, record->f68);
            }
        }
        if (tracksField(*self, 0x10)) {
            if (record->f64 != 0 && *record->f64 != 0) {
                poolName = igStringTable_FindOrAddString(self->_groups, (int)record->f64);
            }
        }
        if (tracksField(*self, 0x20)) {
            if (callStackSkip != -1) {
                callStack = ((igCallStackTableView *)self->_callStacks)->vfunc_27(self->_callStackTracer->vfunc_24(g_eventTrackerMaxCallStackDepth, callStackSkip + 1));
                if (callStack != -1) {
                    flags |= 0x20;
                }
            }
        }
        if (group != -1) flags |= 0x2;
        if (className != -1) flags |= 0x40;
        if (memberName != -1) flags |= 0x80;
        if (annotation != -1) flags |= 0x4;
        if (tracksField(*self, 0x100) && self->_eventTagOffset != -1) flags |= 0x100;
        if (sourceFile != -1 || record->f72 != 0) flags |= 0x8;
        if (poolName != -1) flags |= 0x10;
        if (callStack != -1) flags |= 0x20;
        if (tracksField(*self, 0x8000) && record->slotStates != 0) flags |= 0x8000;
        switch (record->type) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: {
            int previousType;
            int size;
            flags |= 0x1;
            if (isFlagSet(*self, 8) && record->type == 3) {
                int previous = self->vfunc_31(record->address);
                if (previous != -1) {
                    if (self->vfunc_28(previous, &previousType) == g_resultSuccess && previousType == 3) {
                        annotation = igStringTable_FindOrAddString(self->_annotations, (int)"Double-deletion");
                        flags |= 0x4;
                    }
                }
            }
            p++;
            encodeUnsigned(p, flags);
            writeWord(p, record->address);
            if ((size = record->val) == 0 && (record->type == 3 || record->type == 8)) {
                int previous = self->vfunc_31(record->address);
                if (previous != -1) {
                    self->vfunc_30(previous, &size);
                }
            }
            encodeSigned(p, size);
            encodeSigned(p, record->f16);
            self->InsertHashIndex(record->address, offset);
            break;
        }
        case 13: {
            int name = -1;
            if (record->markerType != 0) flags |= 0x200;
            if (record->markerValue != 0) flags |= 0x400;
            if (record->markerName != 0 && *record->markerName != 0) {
                name = igStringTable_FindOrAddString(self->_annotations, (int)record->markerName);
                if (name != -1) flags |= 0x800;
            }
            p++;
            encodeUnsigned(p, flags);
            if (record->markerType != 0) encodeUnsigned(p, record->markerType);
            if (record->markerValue != 0) encodeSigned(p, record->markerValue);
            if (name != -1) encodeSigned(p, name);
            break;
        }
        case 14: {
            int text = -1;
            if (record->notificationType != 0) flags |= 0x1000;
            if (record->notificationCode != 0) flags |= 0x2000;
            if (record->notificationText != 0 && *record->notificationText != 0) {
                text = igStringTable_FindOrAddString(self->_annotations, (int)record->notificationText);
                if (text != -1) flags |= 0x4000;
            }
            p++;
            encodeUnsigned(p, flags);
            if (record->notificationType != 0) encodeUnsigned(p, record->notificationType);
            if (record->notificationCode != 0) encodeSigned(p, record->notificationCode);
            if (text != -1) encodeSigned(p, text);
            break;
        }
        case 15:
            p++;
            encodeUnsigned(p, flags);
            break;
        default:
            p++;
            encodeUnsigned(p, flags);
            break;
        }
        encodeSigned(p, self->_count);
        if (group != -1) encodeSigned(p, group);
        if (className != -1) encodeSigned(p, className);
        if (memberName != -1) encodeSigned(p, memberName);
        if (annotation != -1) encodeSigned(p, annotation);
        if (tracksField(*self, 0x100)) {
            if (self->_eventTagOffset != -1) encodeSigned(p, self->_eventTagOffset);
        }
        if (sourceFile != -1) {
            encodeSigned(p, sourceFile);
            encodeUnsigned(p, record->f72);
        }
        if (poolName != -1) encodeSigned(p, poolName);
        if (callStack != -1) encodeSigned(p, callStack);
        if (tracksField(*self, 0x8000)) {
            if (record->slotStates != 0) {
                encodeUnsigned(p, record->slotStates);
                do {
                    state = igEventTracker_GetEventDataType(record, slot);
                    switch (state) {
                    case 0:
                        break;
                    case 1:
                        encodeSigned(p, igEventTracker_GetEventDataInt(record, slot));
                        break;
                    case 2:
                        encodeUnsigned(p, igEventTracker_GetEventDataUnsigned(record, slot));
                        break;
                    case 3: {
                        char *string = igEventTracker_GetEventDataString(record, slot);
                        if (string != 0 && *string != 0) {
                            int index = igStringTable_FindOrAddString(self->_annotations, (int)string);
                            if (index != -1) encodeSigned(p, index);
                        }
                        break;
                    }
                    }
                    slot++;
                } while (state != 0);
            }
        }
        length = p - buffer;
        buffer[1] = (char)length - 2;
        if (((igCharListRef &)self->_eventRecords)->count() + length > ((igCharListRef &)self->_eventRecords)->capacity()) {
            setCapacity(((igCharListRef &)self->_eventRecords).get(), ((igCharListRef &)self->_eventRecords)->capacity() * 2);
        }
        List_AppendBytes((igDataList *)self->_eventRecords, length, (int)buffer, 1);
        self->_count++;
        self->_flags &= ~2;
    }
    if (detachesAllocations(*self) && (record->type == 1 || record->type == 6)) {
        EventRecord detach;
        igEventTracker_CopyEvent(&detach, record);
        if (record->type == 1) {
            detach.type = 2;
        } else {
            detach.type = 7;
        }
        self->AddEvent(&detach, callStackSkip + 1);
        igEventTracker_DestructEvent(&detach, -1);
    }
    return offset;
}

/* An unaligned little-endian word of an event record. */
static inline void readWord(const char *p, void *out) {
    *(int *)out = ((unsigned char)p[0]) | ((((unsigned char)p[1]) << 8) | ((((unsigned char)p[3]) << 24) | (((unsigned char)p[2]) << 16)));
}

static inline void decodeUnsigned(const char *&p, unsigned int &out) {
    const char *q = p;
    int shift = 0;
    out = 0;
    for (;;) {
        out |= (*q & 0x7F) << shift;
        if ((*q++ & 0x80) == 0) break;
        shift += 7;
    }
    p = q;
}

/* A signed value ends on a byte with bit 6 set: the bits above its top set bit are filled in. */
static inline void decodeSigned(const char *&p, int &out) {
    const char *q = p;
    int shift = 0;
    out = 0;
    for (;;) {
        char byte = *q;
        out |= (byte & 0x7F) << shift;
        if ((byte & 0x80) == 0) {
            if (byte & 0x40) {
                int mask = 0x80000000;
                while ((out & mask) == 0) mask >>= 1;
                out |= mask;
            }
            break;
        }
        q++;
        shift += 7;
    }
    p = q + 1;
}

/* Decodes the event stored at `offset`: its type, version and flags, then each field its flag says
 * is present, then the extra slots. */
extern "C" igResult igEventTracker_ReadEvent(igEventTrackerView *self, int offset, EventRecord *record);
igResult igEventTracker_ReadEvent(igEventTrackerView *self, int offset, EventRecord *record) {
    ScopedLock guard(self->_lock);
    unsigned int flags;
    int slot;
    int state;
    unsigned int type;
    int value;
    unsigned int unsignedValue;
    const char *p;
    if (offset < 0 || offset >= self->_eventRecords->_count) {
        return g_resultFailure;
    }
    p = (const char *)self->_eventRecords->_data + offset;
    slot = 0;
    igEventTracker_ClearEvent((int)record);
    decodeUnsigned(p, type);
    record->type = type;
    if (record->type >= 32) {
        return g_resultFailure;
    }
    if (*p > g_igEventTracker_maxEventDataSize[0]) {
        return g_resultFailure;
    }
    p++;
    decodeUnsigned(p, flags);
    if (flags & 0x1) {
        readWord(p, &record->address);
        p += 4;
        decodeSigned(p, value); record->val = value;
        decodeSigned(p, value); record->f16 = value;
    }
    if (flags & 0x200) { decodeUnsigned(p, unsignedValue); record->markerType = unsignedValue; }
    if (flags & 0x400) { decodeSigned(p, value); record->markerValue = value; }
    if (flags & 0x800) { decodeSigned(p, value); record->markerName = igStringTable_GetString((int *)self->_annotations, value); }
    if (flags & 0x1000) { decodeUnsigned(p, unsignedValue); record->notificationType = unsignedValue; }
    if (flags & 0x2000) { decodeSigned(p, value); record->notificationCode = value; }
    if (flags & 0x4000) { decodeSigned(p, value); record->notificationText = igStringTable_GetString((int *)self->_annotations, value); }
    decodeSigned(p, value); record->index = value;
    if (flags & 0x2) { decodeSigned(p, value); record->group = igStringTable_GetString((int *)self->_groups, value); }
    if (flags & 0x40) { decodeSigned(p, value); record->str = igStringTable_GetString((int *)self->_classNames, value); }
    if (flags & 0x80) { decodeSigned(p, value); record->memberName = igStringTable_GetString((int *)self->_memberNames, value); }
    if (flags & 0x4) { decodeSigned(p, value); record->annotation = igStringTable_GetString((int *)self->_annotations, value); }
    if (flags & 0x100) { decodeSigned(p, value); record->f60 = igStringTable_GetString((int *)self->_groups, value); }
    if (flags & 0x8) {
        decodeSigned(p, value);
        record->f68 = (int)igStringTable_GetString((int *)self->_sourceFileNames, value);
        decodeUnsigned(p, unsignedValue); record->f72 = unsignedValue;
    }
    if (flags & 0x10) { decodeSigned(p, value); record->f64 = igStringTable_GetString((int *)self->_groups, value); }
    if (flags & 0x20) { decodeSigned(p, value); record->callStack = (int *)((igCallStackTableView *)self->_callStacks)->getCallStack(value); }
    if (flags & 0x8000) {
        decodeUnsigned(p, unsignedValue); record->slotStates = unsignedValue;
        do {
            state = igEventTracker_GetEventDataType(record, slot);
            switch (state) {
            case 0:
                break;
            case 1:
                decodeSigned(p, value);
                igEventTracker_SetEventDataInt(record, slot, value);
                break;
            case 2:
                decodeUnsigned(p, unsignedValue);
                igEventTracker_SetEventDataUnsigned(record, slot, unsignedValue);
                break;
            case 3:
                decodeSigned(p, value);
                igEventTracker_SetEventDataString(record, slot, (int)igStringTable_GetString((int *)self->_annotations, value));
                break;
            }
            slot++;
        } while (state != 0);
    }
    return g_resultSuccess;
}

void igEventTracker_ReadEventType(int *result, char *self, char *record, int *type) {
    int acc;
    int c;
    int sh;
    int t;
    sh = 0;
    acc = 0;
    record = (char *)(*(int *)(*(char **)(self + 80) + 16) + (int)record);
    do {
        c = *record;
        t = c & 0x7F;
        record++;
        t = t << sh;
        c = c & 0x80;
        acc |= t;
        if (c == 0) break;
        sh += 7;
    } while (1);
    *type = acc;
    if (*type >= 0x20) {
        *result = g_resultFailure.v;
    } else {
        *result = g_resultSuccess.v;
    }
}

void igEventTracker_ReadEventKey(int *result, char *self, char *record, int *key) {
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
    record = (char *)(*(int *)(*(char **)(self + 80) + 16) + (int)record);
    do {
        c = *record;
        t = c & 0x7F;
        record++;
        t = t << sh;
        c = c & 0x80;
        acc |= t;
        if (c == 0) break;
        sh += 7;
    } while (1);
    if (acc >= 0x20) {
        *result = g_resultFailure.v;
        return;
    }
    {
    char *q = record + 1;
    c = *record;
    if (c > g_igEventTracker_maxEventDataSize[0]) {
        *result = g_resultFailure.v;
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
        *key = ((unsigned char)q[0]) | ((((unsigned char)q[1]) << 8) | ((((unsigned char)q[3]) << 24) | (((unsigned char)q[2]) << 16)));
    } else {
        *result = g_resultFailure.v;
        return;
    }
    *result = g_resultSuccess.v;
    }
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
    if (byte > g_igEventTracker_maxEventDataSize[0]) {
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
void igEventTracker_GetStatistics(igEventTrackerView *self, int first, int last, int *eventCount, int *typeCounts,
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
        offset = self->GetNextEventOffset(offset);
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
        offset = self->GetNextEventOffset(offset);
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

void igEventTracker_GetStatisticsByName(igEventTrackerView *self, int first, int last, int name, int *allocations, int *deallocations, int *allocatedBytes, int *deallocatedBytes)
{
    int index;
    int offset;
    EventRecord ev;
    int key = name;
    index = 0;
    offset = 0;
    igEventTracker_InitEvent((int)&ev);
    if (last == -1) {
        last = self->_count - 1;
    }
    *allocations = 0;
    *deallocations = 0;
    *allocatedBytes = 0;
    *deallocatedBytes = 0;
    while (index < first) {
        offset = self->GetNextEventOffset(offset);
        index += 1;
    }
    for (;;) {
        int c = self->vfunc_27(offset, &ev).get();
        if (c != g_resultSuccess.v) break;
        if (ev.str != 0 && *ev.str != 0 && strcmp(ev.str, key) == 0) {
            switch (ev.type) {
            case 6:
                *allocations += 1;
                *allocatedBytes = *allocatedBytes + ev.getVal();
                break;
            case 8:
                *deallocations += 1;
                *deallocatedBytes = *deallocatedBytes + ev.getVal();
                break;
            }
        }
        offset = self->GetNextEventOffset(offset);
        index += 1;
        if (index >= last || offset == -1) break;
    }
    igEventTracker_DestructEvent(&ev, (long long)(-1));
}

int igEventTracker_FindIndex(igEventTrackerView *self, int value) {
    int out;
    int k;
    int idx;
    int n;
    int i;

    k = self->GetHashBucketIndex(value);
    i = 0;
    n = self->_hashIndex->_count;
    for (;;) {
        idx = self->_hashIndex->_data[k];
        if (idx == -1) {
            return -1;
        }
        self->ReadEventKey(idx, &out);
        if (out == value) {
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

int igEventTracker_GetNextEventOffset(igEventTrackerView *self, int offset) {
    igTDataList<signed char> *q;
    signed char *p;
    int n;
    int c;

    q = self->_eventRecords;
    n = q->_count;
    if (n < offset) {
        return -1;
    }
    p = q->_data + offset;
    if ((unsigned int)*p++ >= 0x20U) {
        return -1;
    }
    c = *p;
    if (g_igEventTracker_maxEventDataSize[0] < c) {
        return -1;
    }
    offset = offset + (c + 2);
    if (offset >= n) {
        offset = -1;
    }
    return offset;
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
    if (self->_callStackTracer->hasSymbols() == 0) {
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
                self->ResolveAddress(**frame, name, 255, &offset, 0, 0, &line);
                if (strcmp(name, text_main) == 0) {
                    break;
                }
                if (strstr(name, wanted) != 0) {
                    record.type = 3;
                    record.f68 = 0;
                    record.f72 = 0;
                    self->AddEvent(&record, -1);
                }
                *frame = *frame + 1;
            }
        }
    }
    igEventTracker_DestructEvent(&record, -1);
}

/* Map a hash value to a bucket of the tracker's hash index: the value modulo the count stored at
 * +8 of the `_hashIndex` object, or 0 while that count is 0. */

int igEventTracker_GetLeakCount(igEventTrackerView *self) {
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

int igEventTracker_FindNextLeak(igEventTrackerView *self, int *cursor) {
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

void igEventTracker_InsertHashIndex(igEventTrackerView *self, int value, int offset) {
    int stored;
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
        idx = self->GetHashBucketIndex(value);
again:
        tb = self->_hashIndex;
        slot = tb->_data + idx;
        v = *slot;
        if (v == -1) {
            cnt = tb->_count;
            if (cnt != 0 && idx >= 0 && idx < cnt) *slot = offset;
        } else {
            self->ReadEventKey(v, &stored);
            if (stored == value) {
                tb = self->_hashIndex;
                cnt = tb->_count;
                if (cnt != 0 && idx >= 0 && idx < cnt) tb->_data[idx] = offset;
            } else {
                idx += 1;
                if (idx >= n) idx = 0;
                tried += 1;
                if (tried >= half) {
                    self->RebuildHashIndex(n * 2);
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
            data[i] = g_igEventTracker_emptyHashSlot[0];
        }
    }
    base = (char *)self->_eventRecords->_data;
    p = base;
    end = base + self->_eventRecords->_count;
    while (p < end) {
        offset = p - base;
        len = p[1];
        p += 2;
        if (self->ReadEventKey(offset, &value) == g_resultSuccess) {
            self->InsertHashIndex(value, offset);
        }
        p += len;
    }
}

/* String literals are read-only here, as in the original build: the literals shared with the
 * call-stack formatter are its objects. */
#pragma push
#pragma readonly_strings on
extern "C" const char *g_defaultEventFormat;
extern "C" char *igEventTracker_FormatEvent(igEventTrackerView *self, EventRecord *record, char *output, int outputSize);

/* Formats one event as a line of text. Each format character is a field, optionally followed by a
 * data slot number, a quoted printf specification ('...') and a call-stack frame format (^...^):
 * a address, c call stack one frame a line, d data slots, e alignment, f source file name, g group,
 * i index, j tag or the third data word, k one character for the event type, l source line,
 * m member name, n annotation, o class name, p source path, q pool name, r call stack on one line,
 * s size, t event type name, u marker type name, v marker value, w marker name, x notification type
 * name, y notification code name, z notification text; "..." is literal text and \n \r \t are
 * escapes. An object deallocation without a source file takes its location from the first
 * call-stack frame outside the release functions. */
char *igEventTracker_FormatEvent(igEventTrackerView *self, EventRecord *record, char *output, int outputSize) {
    int offset;
    int line;
    char function[256];
    char spec[128];
    char frameFormat[128];
    char text[256];
    char path[256];
    EventRecord event;
    const char *format;
    igEventTracker_CopyEvent(&event, record);
    if (outputSize != 0 && output != 0) {
        *output = 0;
    }
    if (record == 0) {
        igEventTracker_DestructEvent(&event, -1);
        return output;
    }
    format = (const char *)igEventTracker_GetEventFormat(self, record->type);
    if (format == 0 || *format == 0) {
        switch (record->type) {
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: {
            const char *memoryFormat = (const char *)self->_defaultMemoryEventFormat;
            if (memoryFormat != 0 && *memoryFormat != 0) {
                format = memoryFormat;
            } else {
                format = g_memoryEventFormat[0];
            }
            break;
        }
        case 13:
            format = (const char *)g_markerEventFormat[0];
            break;
        case 14:
            format = (const char *)g_notificationEventFormat[0];
            break;
        case 15:
        default:
            format = g_defaultEventFormat;
            break;
        }
    }
    switch (event.type) {
    case 8:
        if (event.getSourceFile() == 0 || *event.getSourceFile() == 0) {
            int *frame = event.getCallStack();
            if (frame != 0) {
                while (*frame != 0) {
                    self->ResolveAddress(*frame, function, 255, &offset, path, 255, &line);
                    if (strstr(function, "igObject::internalRelease") == 0 && strstr(function, "igObject::release") == 0 &&
                        strstr(function, "::~igSmartPointer<") == 0) {
                        event.callStack = frame;
                        event.f68 = (int)path;
                        event.f72 = line;
                        break;
                    }
                    frame++;
                }
            }
        }
        break;
    }
    while (*format != 0) {
        char field = *format;
        int slot;
        int n;
        spec[0] = 0;
        format++;
        frameFormat[0] = 0;
        slot = -1;
        if (*format >= '0' && *format <= '9') {
            slot = 0;
            while (*format >= '0' && *format <= '9') {
                slot = slot * 10 + (*format - '0');
                format++;
            }
        }
        if (field != '"') {
            while (*format == '\'' || *format == '^') {
                if (*format == '\'') {
                    n = 0;
                    format++;
                    while (*format && *format != '\'' && n < 127) {
                        if (*format == '\\') {
                            format++;
                            switch (*format) {
                            case 'n': spec[n++] = '\n'; break;
                            case 'r': spec[n++] = '\r'; break;
                            case 't': spec[n++] = '\t'; break;
                            }
                        } else {
                            spec[n++] = *format;
                        }
                        format++;
                    }
                    spec[n] = 0;
                    if (*format == '\'') {
                        format++;
                    }
                }
                if (*format == '^') {
                    n = 0;
                    format++;
                    while (*format && *format != '^' && n < 127) {
                        if (*format == '\\') {
                            format++;
                            switch (*format) {
                            case 'n': frameFormat[n++] = '\n'; break;
                            case 'r': frameFormat[n++] = '\r'; break;
                            case 't': frameFormat[n++] = '\t'; break;
                            }
                        } else {
                            frameFormat[n++] = *format;
                        }
                        format++;
                    }
                    frameFormat[n] = 0;
                    if (*format == '^') {
                        format++;
                    }
                }
            }
        }
        text[0] = 0;
        switch (field) {
        case 'a':
            sprintf(text, spec[0] != 0 ? spec : "0x%08x", event.getAddress());
            break;
        case 'c': {
            int *frame = event.callStack;
            if (frame != 0) {
                while (*frame != 0) {
                    self->vfunc_39(*frame, frameFormat, function, 255);
                    sprintf(text, spec[0] != 0 ? spec : "\n%s", function);
                    strncat(output, text, outputSize);
                    if (outputSize != 0) {
                        output[outputSize - 1] = 0;
                    }
                    text[0] = 0;
                    if (strncmp(function, "main", 4) == 0) {
                        break;
                    }
                    if (strstr(function, " main") != 0) {
                        break;
                    }
                    frame++;
                }
            }
            break;
        }
        case 'd': {
            int end;
            if (slot != -1) {
                end = slot + 1;
            } else {
                slot = 0;
                end = igEventTracker_FindFreeEventDataSlot(&event);
            }
            text[0] = 0;
            for (; slot < end; slot++) {
                switch (igEventTracker_GetEventDataType(&event, slot)) {
                case 1:
                    sprintf(text + strlen(text), spec[0] != 0 ? spec : "%d", igEventTracker_GetEventDataInt(&event, slot));
                    break;
                case 2:
                    sprintf(text + strlen(text), spec[0] != 0 ? spec : "%u", igEventTracker_GetEventDataUnsigned(&event, slot));
                    break;
                case 3:
                    sprintf(text + strlen(text), spec[0] != 0 ? spec : "%s",
                            igEventTracker_GetEventDataString(&event, slot) != 0 ? igEventTracker_GetEventDataString(&event, slot)
                                                                                     : (char *)emptyString_4);
                    break;
                case 0:
                    continue;
                default:
                    continue;
                }
                if (slot < end - 1) {
                    strcat(text, " ");
                }
            }
            break;
        }
        case 'e':
            sprintf(text, spec[0] != 0 ? spec : "%d", event.getAlignment());
            break;
        case 'f':
            if (event.f68 != 0 && *(char *)event.f68 != 0) {
                char *backslash = strrchr((char *)event.f68, '\\');
                char *slash = strrchr((char *)event.f68, '/');
                char *name;
                if (backslash != 0 && slash != 0) {
                    name = slash < backslash ? backslash : slash;
                } else {
                    name = backslash != 0 ? backslash : slash;
                }
                if (name != 0) {
                    name++;
                } else {
                    name = (char *)event.f68;
                }
                if (name != 0 && *name != 0) {
                    sprintf(text, spec[0] != 0 ? spec : "%s", name);
                }
            }
            break;
        case 'g':
            if (event.group != 0 && *event.group != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.group);
            }
            break;
        case 'i':
            sprintf(text, spec[0] != 0 ? spec : "%d", event.getIndex());
            break;
        case 'j':
            if (event.f60 != 0 && *event.f60 != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.f60);
            } else if (igEventTracker_FindFreeEventDataSlot(&event) == 3) {
                unsigned int words[3];
                igEventTracker_GetEventDataUnsigned3(&event, 0, words);
                if (words[2] != 0) {
                    sprintf(text, spec[0] != 0 ? spec : "%d", words[2]);
                }
            }
            break;
        case 'k': {
            char kind;
            switch (event.type) {
            case 1: kind = '+'; break;
            case 2: kind = '*'; break;
            case 3: kind = '-'; break;
            case 4: kind = '<'; break;
            case 5: kind = '>'; break;
            case 6: kind = 'o'; break;
            case 7: kind = 't'; break;
            case 8: kind = 'd'; break;
            case 9: kind = 'r'; break;
            case 10: kind = 'w'; break;
            case 11: kind = 'r'; break;
            case 12: kind = 'w'; break;
            case 13: kind = 'm'; break;
            case 14: kind = 'n'; break;
            case 15:
            default: kind = 'c'; break;
            }
            sprintf(text, spec[0] != 0 ? spec : "%c", kind);
            break;
        }
        case 'l':
            sprintf(text, spec[0] != 0 ? spec : "%d", event.getLine());
            break;
        case 'm':
            if (event.memberName != 0 && *event.memberName != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.memberName);
            }
            break;
        case 'n':
            if (event.annotation != 0 && *event.annotation != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.annotation);
            }
            break;
        case 'o':
            if (event.str != 0 && *event.str != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.str);
            }
            break;
        case 'p':
            if (event.f68 != 0 && *(char *)event.f68 != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.f68);
            }
            break;
        case 'q':
            if (event.f64 != 0 && *event.f64 != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.f64);
            }
            break;
        case 'r': {
            int *frame = event.callStack;
            if (frame != 0) {
                while (*frame != 0) {
                    self->vfunc_39(*frame, frameFormat, function, 255);
                    sprintf(text, spec[0] != 0 ? spec : "%s", function);
                    frame++;
                    if (*frame != 0) {
                        if (spec[0] == 0) {
                            strcat(text, " ");
                        }
                    }
                    strncat(output, text, outputSize);
                    if (outputSize != 0) {
                        output[outputSize - 1] = 0;
                    }
                    text[0] = 0;
                    if (strncmp(function, "main", 4) == 0) {
                        break;
                    }
                    if (strstr(function, " main") != 0) {
                        break;
                    }
                }
            }
            break;
        }
        case 's':
            sprintf(text, spec[0] != 0 ? spec : "0x%06x", event.getVal());
            break;
        case 't': {
            const char *name = (const char *)igEventTracker_GetEventTypeName(self, event.type);
            if (name == 0) {
                name = "(Unknown)";
            }
            sprintf(text, spec[0] != 0 ? spec : "%s", name);
            break;
        }
        case 'u':
            if (event.markerType != 0) {
                const char *name = (const char *)igEventTracker_GetMarkerTypeName(self, event.markerType);
                if (name == 0) {
                    name = "(Unknown)";
                }
                sprintf(text, spec[0] != 0 ? spec : "%s", name);
            }
            break;
        case 'v':
            if (event.markerValue != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%d", event.markerValue);
            } else if (igEventTracker_FindFreeEventDataSlot(&event) == 3) {
                unsigned int words[3];
                igEventTracker_GetEventDataUnsigned3(&event, 0, words);
                sprintf(text, spec[0] != 0 ? spec : "%d", words[1]);
            }
            break;
        case 'w':
            if (event.markerName != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.markerName);
            } else if (igEventTracker_FindFreeEventDataSlot(&event) == 3) {
                unsigned int words[3];
                igEventTracker_GetEventDataUnsigned3(&event, 0, words);
                sprintf(text, spec[0] != 0 ? spec : "%u", words[0]);
            }
            break;
        case 'x':
            if (event.notificationType != 0) {
                const char *name = (const char *)igEventTracker_GetNotificationTypeName(self, event.notificationType);
                if (name == 0) {
                    name = "(Unknown)";
                }
                sprintf(text, spec[0] != 0 ? spec : "%s", name);
            }
            break;
        case 'y':
            if (event.notificationCode != 0) {
                const char *name = (const char *)igEventTracker_GetNotificationCodeName(self, event.notificationCode);
                if (name != 0) {
                    sprintf(text, spec[0] != 0 ? spec : "%s", name);
                } else {
                    sprintf(text, spec[0] != 0 ? spec : "%d", event.getNotificationCode());
                }
            }
            break;
        case 'z':
            if (event.notificationText != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", event.notificationText);
            }
            break;
        case '\\':
            switch (*format++) {
            case 'n': strcpy(text, "\n"); break;
            case 'r': strcpy(text, "\r"); break;
            case 't': strcpy(text, "\t"); break;
            }
            break;
        case '"': {
            int c;
            while (*format && (c = *format) != '"') {
                if (c == '\\') {
                    format++;
                    switch (*format) {
                    case 'n': strcat(text, "\n"); break;
                    case 'r': strcat(text, "\r"); break;
                    case 't': strcat(text, "\t"); break;
                    }
                } else {
                    sprintf(text + strlen(text), "%c", c);
                }
                format++;
            }
            if (*format == '"') {
                format++;
            }
            break;
        }
        default:
            sprintf(text, "%c", field);
            break;
        }
        strncat(output, text, outputSize);
    }
    strncat(output, "\n", outputSize);
    if (outputSize > 1) {
        output[outputSize - 2] = '\n';
    }
    if (outputSize != 0) {
        output[outputSize - 1] = 0;
    }
    igEventTracker_DestructEvent(&event, -1);
    return output;
}

#pragma pop

int igEventTracker_GetEventFormat(void *tracker, int type) {
    int nameOffset;
    int idx;

    if (type >= 0 && type < 0x20) {
        idx = type * 4;
        nameOffset = ((igEventTrackerView *)(idx + (int)tracker))->_eventFormatOffsets[0]; /* matching construct: _eventFormatOffsets[type] spelled as the tracker shifted by `type` words, so the index is added before the base */
        if (nameOffset != -1) {
            return ((int)igStringTable_GetString((int *)((igEventTrackerView *)tracker)->_names, nameOffset));
        }
    }
    return 0;
}

int igEventTracker_GetEventTypeName(void *tracker, int type) {
    int off;
    int nameOffset;

    if (type >= 0 && type < 0x20) {
        off = type * 4;
        nameOffset = ((igEventTrackerView *)(off + (int)tracker))->_eventTypeNameOffsets[0]; /* matching construct: as in igEventTracker_GetEventFormat */
        if (nameOffset != -1) {
            return ((int)igStringTable_GetString((int *)((igEventTrackerView *)tracker)->_names, nameOffset));
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

int igEventTracker_GetNotificationCodeName(void *tracker, int code) {
    int t; if (code >= 0 && code < 0x40) { t = ((igEventTrackerView *)((code << 2) + (int)tracker))->_notificationCodeNameOffsets[0]; /* matching construct: as in igEventTracker_GetEventFormat */ if (t != -1) return ((int)igStringTable_GetString((int *)((igEventTrackerView *)tracker)->_names, t)); } return 0;
}

igResult igEventTracker_FormatAddress(igEventTrackerView *self, int addr, int format, long long output, long long outputSize) {
    char buf[256];
    char name[256];
    int offset;
    int line;
    igResult r = self->ResolveAddress(addr, buf, 255, &offset, name, 255, &line);
    self->_callStackTracer->vfunc_28(addr, buf, offset, name, line, format, output, outputSize);
    return r;
}

igResult igEventTracker_ResolveAddress(igEventTrackerView *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line) {
    int s0;
    if (igLocationTable_IsInitialized((void *)self->_locations) != 0) {
        s0 = self->_locations->GetLocation(addr, buf, size, offset, name, nameSize, line).v;
        if (s0 == g_resultFailure.v) {
            if (self->_callStackTracer->hasSymbols() != 0) {
                s0 = self->_callStackTracer->lookupAddress(addr, buf, size, offset, name, nameSize, line).v;
                self->_locations->AddLocation(addr, buf, *offset, name, *line);
                g_igEventTracker_addressTracerLookups[0] = g_igEventTracker_addressTracerLookups[0] + 1;
                goto join;
            }
        }
        g_igEventTracker_addressCacheHits[0] += 1;
    } else {
        s0 = self->_callStackTracer->lookupAddress(addr, buf, size, offset, name, nameSize, line).v;
        g_igEventTracker_addressTracerLookups[0] = g_igEventTracker_addressTracerLookups[0] + 1;
    }
join:
    g_igEventTracker_addressLookups[0] += 1;
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
        self->PrintEvent(s);
        s = self->GetNextEventOffset(s);
    }
}



























































void igEventTracker_PrintLeaks(igEventTrackerView *self) {
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
                self->PrintEvent(offset);
            }
        }
    }
    igEventTracker_DestructEvent(&record, (long long)(-1));
}

static inline bool hasFlag(const igEventTrackerView *tracker, unsigned mask) { return (tracker->_flags & mask) != 0; }

igResult igEventTracker_WriteFile(igEventTrackerView *self, int fileName) {
    bool had;
    bool trk;
    int r;
    igObject *a;
    igObject *old;
    igIGBFileView *o;
    had = hasFlag(self, 2);
    self->_flags = self->_flags | 2;
    trk = hasFlag(self, 4);
    if (trk == false) {
        self->ResolveAllCallStackSymbols();
    }
    {
    igSmartPointer<igIGBFileView> file(((igIGBFileView *)igIGBFile_Create((int)(((igObject *)igObject_GetAllocator((int)self))))));
    a = ((igObject *)igObject_GetAllocator((int)self));
    o = file.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = (igObject *)o->_temporaryMemoryPool;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->_temporaryMemoryPool = (igMemoryPoolView *)a;
    a = ((igObject *)igObject_GetAllocator((int)self));
    o = file.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = (igObject *)o->_objectMemoryPool;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->_objectMemoryPool = (igMemoryPoolView *)a;
    a = ((igObject *)igObject_GetAllocator((int)self));
    o = file.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = (igObject *)o->_dataMemoryPool;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->_dataMemoryPool = (igMemoryPoolView *)a;
    file.p->_useMemoryPoolAssignmentsState = 1;
    igDirectory_AddObjectRecursive((int)file.p, (int)self, g_igEventTracker_memoryDataName[0], 0);
    r = file.p->writeFile(fileName);
    }
    self->_flags = had ? (self->_flags | 2) : (self->_flags & ~2);
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
    count = ((igCallStackTableView *)self->_callStacks)->getCallStackCount();
    a = 0;
    b = 0;
    wasSet = (self->getFlags() & 2) != 0;
    self->_flags |= 2;
    row = ((igCallStackTableView *)self->_callStacks)->getCallStack(0);
    if (row != 0) {
        for (i = 0; i < count; i++) {
            while (*row != 0) {
                self->ResolveAddress(*row, bufA, 255, &a, bufB, 255, &b);
                row++;
            }
            row++;
        }
        self->_flags |= 4;
        { int f; if (wasSet) { f = self->_flags | 2; } else { f = self->_flags & ~2; } self->_flags = f; }
    }
}

void igEventTracker_PreExit(igEventTrackerView *self)
{
    self->_callStackTracer->vfunc_29();
}

void igEventTracker_Exit(igEventTrackerView *self)
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
        self->_eventTypeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, g_igEventTracker_eventTypeNames[i]);
    }
    for (i = 0; i < 32; i++) {
        self->_markerTypeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, g_igEventTracker_markerTypeNames[i]);
    }
    for (i = 0; i < 16; i++) {
        self->_notificationTypeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, g_igEventTracker_notificationTypeNames[i]);
    }
    for (i = 0; i < 64; i++) {
        self->_notificationCodeNameOffsets[i] = igStringTable_FindOrAddString(self->_names, g_igEventTracker_notificationCodeNames[i]);
    }
}

int igEventTracker_InitEvent(int record) {
    igEventTracker_ClearEvent(record);
    return record;
}

EventRecord *igEventTracker_CopyEvent(EventRecord *copy, const EventRecord *source) {
    memcpy(copy, source, sizeof(EventRecord));
    return copy;
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

void *igEventTracker_DestructEvent(void *record, long long deleteFlag) {
    if (record != 0) {
        if (((long long) (deleteFlag << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasB(record);
        }
    }
    return record;
}

void igEventTracker_ClearEvent(int record) {
    memset(record, 0, 148);
}

int igEventTracker_FindFreeEventDataSlot(void *record) {
    int i;
    for (i = 0; i < 0x10; i++) {
        if (!(((EventRecord *)record)->slotStates & (3 << (i * 2)))) {
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

int igEventTracker_GetEventDataInt(const EventRecord *record, int slot) {
    if (slot < 16) {
        return record->slots[slot];
    }
    return -1;
}

void igEventTracker_SetEventDataInt(void *record, int slot, int value) {
    int t;
    if (slot < 0x10) {
        t = slot * 2;
        ((EventRecord *)record)->slotStates = (1 << t) | (((EventRecord *)record)->slotStates & ~(3 << t));
        ((EventRecord *)((slot << 2) + (int)record))->slots[0] = value; /* matching construct: as in igEventTracker_GetEventDataInt */
    }
}

unsigned int igEventTracker_GetEventDataUnsigned(const EventRecord *record, int slot) {
    unsigned int value;

    value = (unsigned int)-1;
    if (slot < 16) {
        value = record->slots[slot];
    }
    return value;
}

void igEventTracker_SetEventDataUnsigned(void *record, int slot, int value) {
    int shift;

    if (slot < 0x10) {
        shift = slot * 2;
        ((EventRecord *)record)->slotStates = (int)((int) ((2 << shift) | (((EventRecord *)record)->slotStates & ~(3 << shift))));
        ((EventRecord *)((slot << 2) + (int)record))->slots[0] = value; /* matching construct: as in igEventTracker_GetEventDataInt */
    }
}

char *igEventTracker_GetEventDataString(const EventRecord *record, int slot) {
    char *string = 0;
    if (slot < 16) {
        string = (char *)record->slots[slot];
    }
    return string;
}

void igEventTracker_SetEventDataString(void *record, int slot, int value) {
    int mask;
    int idx;
    char *p;
    if (slot < 0x10) {
        mask = 3 << (slot * 2);
        ((EventRecord *)record)->slotStates = (int)((int) (mask | (((EventRecord *)record)->slotStates & ~mask)));
        idx = slot * 4;
        p = (char *)(idx + (int)record);
        ((EventRecord *)p)->slots[0] = value; /* matching construct: as in igEventTracker_GetEventDataInt */
    }
}

void igEventTracker_GetEventDataUnsigned3(const EventRecord *record, int slot, unsigned int *values) {
    if ((values != 0) && (slot < 16)) {
        values[0] = igEventTracker_GetEventDataUnsigned(record, slot);
        values[1] = igEventTracker_GetEventDataUnsigned(record, slot + 1);
        values[2] = igEventTracker_GetEventDataUnsigned(record, slot + 2);
    }
}

