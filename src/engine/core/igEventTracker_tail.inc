void FUN_002dca90(void)
{
}

static inline void setPool(PoolOwner *self, RefPool *pool) {
    RefPool *previous;
    if (pool != 0) {
        pool->_refCount = pool->_refCount + 1;
    }
    previous = self->pool;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->pool = pool;
}

void FUN_002dcaa0(PoolOwner *self, int open) {
    if (open != 0) {
        if (self->pool == 0) {
            igSmartPointer<RefPool> created(((RefPool *)FUN_002ba650(((int)igObject_GetAllocator((int)self)))));
            created.get()->open();
            setPool(self, created.get());
        }
    } else {
        if (self->pool != 0) {
            igSmartPointer<RefPool> kept(self->pool);
            kept.retain();
            setPool(self, 0);
            if (kept.get() != 0) {
                kept.get()->close();
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

void FUN_002dcc60(FileRequest *request, int path) {
    ScopedLock guard(request->mutex);
    if (request->busy()) {
        return;
    }
    request->flags = request->flags | 2;
    if (path != 0) {
        strncpy(request->path, path, 0xFF);
    } else {
        request->path[0] = 0;
    }
    if (request->path[0] != 0) {
        request->result = FUN_0030d300(request->handle, (int)request->path);
    } else {
        request->result = -1;
    }
    request->flags = request->flags & ~2;
}

void FUN_002dcd70(W_2dcd70 *arg0, int arg1) {
    ScopedLock_2dcd70 guard(arg0->lock);
    if (arg0->isBusy() != false) {
        return;
    }
    arg0->flags = arg0->flags | 2;
    if (arg1 != 0) {
        strncpy(arg0->buf, arg1, 0xFF);
    } else {
        arg0->buf[0] = 0;
    }
    if (arg0->buf[0] != 0) {
        arg0->res = FUN_0030d300(arg0->h, (int)arg0->buf);
    } else {
        arg0->res = -1;
    }
    arg0->flags = arg0->flags & ~2;
}

void Gap__Core__igEventTracker__vfunc_23(Ev *arg0) {
    int n;
    FUN_0030cf20(arg0->f52, 0x100);
    FUN_0030cf30(arg0->f52, 0x20);
    FUN_0030cf40((void *)arg0->f52);
    FUN_0030cf20(arg0->f56, 0x1000);
    FUN_0030cf30(arg0->f56, 0x100);
    FUN_0030cf40((void *)arg0->f56);
    FUN_0030cf20(arg0->f68, 0x200);
    FUN_0030cf30(arg0->f68, 0x20);
    FUN_0030cf40((void *)arg0->f68);
    FUN_0030cf20(arg0->f64, 0x10000);
    FUN_0030cf30(arg0->f64, 0x1000);
    FUN_0030cf40((void *)arg0->f64);
    FUN_0030cf20(arg0->f68, 0x2000);
    FUN_0030cf30(arg0->f68, 0x100);
    FUN_0030cf40((void *)arg0->f68);
    FUN_002d38d0(arg0->f72, 0x10000);
    FUN_002d38e0(arg0->f72, 0x1000);
    FUN_002d38f0((void *)arg0->f72);
    if (arg0->f92->v23() != 0) {
        FUN_002eb090(arg0->f76, 0x4000);
        FUN_002eb0a0(arg0->f76, 0x4000);
        FUN_002eb0b0((int *)arg0->f76);
    }
    n = arg0->f36 * 0x14;
    if (n >= arg0->f80->cap) {
        List_Reserve((L_2d6680 *)arg0->f80, n, 1);
    }
    arg0->v48(arg0->f36 * 2);
    FUN_002dca90();
    arg0->f88 = (int)FUN_002dca90;
    FUN_002dcaa0((PoolOwner *)arg0, 1);
}

void Gap__Core__igEventTracker__vfunc_24(E_2dd000 *arg0) {
    int busy = (arg0->getFlags() & 2) != 0;
    if (!busy) {
        arg0->flags = arg0->flags | 2;
        FUN_0030cfa0((struct ClearOwner *)arg0->f52);
        FUN_0030cfa0((struct ClearOwner *)arg0->f56);
        FUN_0030cfa0((struct ClearOwner *)arg0->f68);
        FUN_0030cfa0((struct ClearOwner *)arg0->f64);
        FUN_0030cfa0((struct ClearOwner *)arg0->f68);
        FUN_002d3950((struct S_2d3950 *)arg0->f72);
        if (arg0->f92->vA() != 0) {
            FUN_002eb150((struct O_2eb150 *)arg0->f76);
        }
        if (0 <= arg0->f80->cap) {
            arg0->f80->cnt = 0;
        } else {
            List_Resize(arg0->f80, 0, 1);
        }
        if (!(0 < arg0->f80->cnt)) {
            List_Reserve((L_2d6680 *)arg0->f80, 0, 1);
        }
        FUN_002dcaa0((PoolOwner *)arg0, 0);
        arg0->flags = arg0->flags & ~2;
    }
}

void Gap__Core__igEventTracker__vfunc_25(E_2dd0f0 *arg0) {
    EventTrackerScopedLock guard(arg0->lock);
    arg0->f40 = 0;
    FUN_0030d050(arg0->f52);
    FUN_0030d050(arg0->f56);
    FUN_0030d050(arg0->f68);
    FUN_0030d050(arg0->f64);
    FUN_0030d050(arg0->f68);
    FUN_002d3a20((void **)arg0->f72);
    Lst_2dd0f0 *l = arg0->f80;
    if (0 <= l->_capacity) {
        l->_count = 0;
    } else {
        List_Resize(l, 0, 1);
    }
    arg0->v200(arg0->f84->f12);
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

void Gap__Core__igEventTracker__vfunc_33(T_2df6d0 *arg0, int arg1, int arg2, int arg3, int *arg4, int *arg5, int *arg6, int *arg7)
{
    int var_s1;
    int var_s0;
    Ev_2df6d0 ev;
    int key = arg3;
    var_s1 = 0;
    var_s0 = 0;
    FUN_002e2130((int)&ev);
    if (arg2 == -1) {
        arg2 = arg0->f40 - 1;
    }
    *arg4 = 0;
    *arg5 = 0;
    *arg6 = 0;
    *arg7 = 0;
    while (var_s1 < arg1) {
        var_s0 = arg0->v32(var_s0);
        var_s1 += 1;
    }
    for (;;) {
        int c = arg0->v25(var_s0, &ev).Code();
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
        var_s0 = arg0->v32(var_s0);
        var_s1 += 1;
        if (var_s1 >= arg2 || var_s0 == -1) break;
    }
    FUN_002e2300(&ev, (long long)(-1));
}

int Gap__Core__igEventTracker__vfunc_31(ET *arg0, int arg1) {
    int out;
    int k;
    int idx;
    int n;
    int i;

    k = arg0->vB();
    i = 0;
    n = arg0->f84->n;
    for (;;) {
        idx = arg0->f84->data[k];
        if (idx == -1) {
            return -1;
        }
        arg0->vA(idx, &out);
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

int Gap__Core__igEventTracker__vfunc_34(int *arg0, int arg1) {
    struct Q_2df990 *q;
    signed char *p;
    int n;
    int c;

    q = (struct Q_2df990 *)arg0[20];
    n = q->count;
    if (n < arg1) {
        return -1;
    }
    p = q->data + arg1;
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

void Gap__Core__igEventTracker__vfunc_49(O_2dff30 *self, int arg1, int arg2) {
    int sp9C;
    int idx, tried, n, half, cnt;
    TB *tb;
    int *slot;
    int v;
loop:
    n = self->tab->count;
    half = n >> 1;
    if (n < 0) half = (n + 1) >> 1;
    tried = 0;
    bool z = !(n != 0);
    if (z) goto done;
    {
        idx = self->v46(arg1);
again:
        tb = self->tab;
        slot = tb->data + idx;
        v = *slot;
        if (v == -1) {
            cnt = tb->count;
            if (cnt != 0 && idx >= 0 && idx < cnt) *slot = arg2;
        } else {
            self->v27(v, &sp9C);
            if (sp9C == arg1) {
                tb = self->tab;
                cnt = tb->count;
                if (cnt != 0 && idx >= 0 && idx < cnt) tb->data[idx] = arg2;
            } else {
                idx += 1;
                if (idx >= n) idx = 0;
                tried += 1;
                if (tried >= half) {
                    self->v48(n * 2);
                    goto loop;
                }
                goto again;
            }
        }
    }
done: ;
}

static inline void setCount(EventSlotList *l, int n) {
    if (n >= 0) {
        if (n <= l->capacity) {
            l->count = n;
        } else {
            List_Resize((void *)l, n, 4);
        }
    }
}

void Gap__Core__igEventTracker__vfunc_50(EventTrackerSlots *self, int n) {
    char *base;
    int value;
    char *end;
    char *p;
    int len;
    int offset;
    FUN_002dcc40((int)self, n);
    if (n >= self->slots->count) {
        List_Reserve((L_2d6680 *)self->slots, n, 4);
    }
    setCount(self->slots, n);
    {
        int count = self->slots->count;
        int *data = self->slots->data;
        int i;
        for (i = 0; i < count; i++) {
            data[i] = DAT_004c2120[0];
        }
    }
    base = self->bytes->data;
    p = base;
    end = base + self->bytes->count;
    while (p < end) {
        offset = p - base;
        len = p[1];
        p += 2;
        if (self->Lookup(offset, &value) == g_resultSuccess) {
            self->Bind(value, offset);
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

int FUN_002e1550(struct S_2e1550 *arg0, int arg1) {
    int t;
    if (arg1 >= 0 && arg1 < 32) {
        t = arg0->tab[arg1];
        if (t != -1) {
            return ((int)FUN_0030d1d0((int *)arg0->a, t));
        }
    }
    return 0;
}

int FUN_002e15a0(S_2e15a0 *arg0, int arg1) {
    int temp_a1;

    if (arg1 >= 0 && arg1 < 16) {
        temp_a1 = arg0->tbl[arg1];
        if (temp_a1 != -1) {
            return ((int)FUN_0030d1d0((int *)arg0->f48, temp_a1));
        }
    }
    return 0;
}

int FUN_002e15f0(void *arg0, int arg1) {
    int t; if (arg1 >= 0 && arg1 < 0x40) { t = *(int *)((arg1 << 2) + (int)arg0 + 548); if (t != -1) return ((int)FUN_0030d1d0((int *)(*(int *)((char *)arg0 + 48)), t)); } return 0;
}

R_2e1640 Gap__Core__igEventTracker__vfunc_39(Tracker *self, int a, int b, long long c, long long d) {
    char first[256];
    char second[256];
    int firstLen;
    int secondLen;
    R_2e1640 r = self->Format(a, first, 255, &firstLen, second, 255, &secondLen);
    self->sink->Write(a, first, firstLen, second, secondLen, b, c, d);
    return r;
}

R_2e1710 Gap__Core__igEventTracker__vfunc_40(T_2e1710 *arg1, int arg2, int arg3, int arg4, int *arg5, int arg6, int arg7, int *arg8) {
    int s0;
    if (FUN_002eb210((void *)arg1->f76) != 0) {
        s0 = arg1->f76->v108(arg2, arg3, arg4, arg5, arg6, arg7, arg8).a;
        if (s0 == g_resultFailure.v) {
            if (arg1->f92->v100() != 0) {
                s0 = arg1->f92->v108(arg2, arg3, arg4, arg5, arg6, arg7, arg8).a;
                arg1->f76->v116(arg2, arg3, *arg5, arg6, *arg8);
                DAT_00586e08[0] = DAT_00586e08[0] + 1;
                goto join;
            }
        }
        DAT_00586e10[0] += 1;
    } else {
        s0 = arg1->f92->v108(arg2, arg3, arg4, arg5, arg6, arg7, arg8).a;
        DAT_00586e08[0] = DAT_00586e08[0] + 1;
    }
join:
    DAT_00586e00[0] += 1;
    return R_2e1710(s0);
}

void Gap__Core__igEventTracker__vfunc_42(V_2e1a40 *arg0) {
    int s = 0;
    while (s != -1) {
        arg0->vX(s);
        s = arg0->vY(s);
    }
}

static inline bool hasFlag(const Tk_2e1bb0 *tracker, unsigned mask) { return (tracker->flags & mask) != 0; }

R_2e1bb0 Gap__Core__igEventTracker__vfunc_44(Tk_2e1bb0 *arg1, int arg2) {
    bool had;
    bool trk;
    int r;
    igObject *a;
    igObject *old;
    Ob *o;
    had = hasFlag(arg1, 2);
    arg1->flags = arg1->flags | 2;
    trk = hasFlag(arg1, 4);
    if (trk == false) {
        arg1->v180();
    }
    {
    igSmartPointer<Ob> sp7C(((Ob *)FUN_002c37e0((int)(((igObject *)igObject_GetAllocator((int)arg1))))));
    a = ((igObject *)igObject_GetAllocator((int)arg1));
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = o->f280;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->f280 = a;
    a = ((igObject *)igObject_GetAllocator((int)arg1));
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = o->f288;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->f288 = a;
    a = ((igObject *)igObject_GetAllocator((int)arg1));
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = o->f284;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->f284 = a;
    sp7C.p->f65 = 1;
    FUN_002d8620((int)sp7C.p, (int)arg1, DAT_004c1ed8[0], 0);
    r = sp7C.p->v112(arg2);
    }
    arg1->flags = had ? (arg1->flags | 2) : (arg1->flags & ~2);
    return R_2e1bb0(r);
}

void Gap__Core__igEventTracker__vfunc_45(EventTrackerRunner *self) {
    int a;
    int b;
    char bufA[256];
    char bufB[256];
    int count;
    int i;
    int *row;
    bool wasSet;
    count = self->table->rowCount();
    a = 0;
    b = 0;
    wasSet = (self->getFlags() & 2) != 0;
    self->flags |= 2;
    row = self->table->rows(0);
    if (row != 0) {
        for (i = 0; i < count; i++) {
            while (*row != 0) {
                self->run(*row, bufA, 255, &a, bufB, 255, &b);
                row++;
            }
            row++;
        }
        self->flags |= 4;
        { int f; if (wasSet) { f = self->flags | 2; } else { f = self->flags & ~2; } self->flags = f; }
    }
}

void Gap__Core__igEventTracker__vfunc_46(igEventTrackerView *self)
{
    self->_callStackTracer->vfunc_27();
}

void Gap__Core__igEventTracker__vfunc_47(igEventTrackerView *self)
{
    self->_callStackTracer->vfunc_28();
}

void Gap__Core__igEventTracker__vfunc_13(TrackerConfig *self) {
    int i;
    self->s0[0] = 0;
    self->pad9255 = 0;
    self->s1[0] = 0;
    self->s1end = 0;
    if (((Cfg * *)g_objectSystem)[0] != 0) {
        self->a = ((Cfg * *)g_objectSystem)[0]->a;
        self->b = ((Cfg * *)g_objectSystem)[0]->b;
        self->c = ((Cfg * *)g_objectSystem)[0]->c;
        self->d = ((Cfg * *)g_objectSystem)[0]->d;
    }
    FUN_0030cf20((int)self->map, 0x1000);
    FUN_0030cf30((int)self->map, 0x100);
    FUN_0030cf40(self->map);
    memset(self->mask0, 0xFF, 0x80);
    memset(self->t0, 0xFF, 0x80);
    memset(self->t1, 0xFF, 0x80);
    memset(self->t2, 0xFF, 0x40);
    memset(self->t3, 0xFF, 0x100);
    for (i = 0; i < 32; i++) {
        self->t0[i] = FUN_0030d300((int)self->map, DAT_004c1ee0[i]);
    }
    for (i = 0; i < 32; i++) {
        self->t1[i] = FUN_0030d300((int)self->map, DAT_004c1f60[i]);
    }
    for (i = 0; i < 16; i++) {
        self->t2[i] = FUN_0030d300((int)self->map, DAT_004c1fe0[i]);
    }
    for (i = 0; i < 64; i++) {
        self->t3[i] = FUN_0030d300((int)self->map, DAT_004c2020[i]);
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

