inline bool igResult_2e3a10::isFailed(int &f) const { f = g_allocatorFailureStatus.v; return *this == g_allocatorFailureStatus; }

inline bool igResult_2e3a10::failed() const { return v == g_allocatorFailureStatus.v; }

int FUN_002e3a10(void *arg0, int arg1) {
    int sp1C;
    void **temp_v0;

    sp1C = *(int *)((char *)(arg1) + 4);
    if (*(unsigned char *)((char *)(arg0) + 168) != 0) {
        temp_v0 = (void **)(((void *)igIntMetaField_GetDefaultDescriptor()));
        ((DW4VC_208_2_2e3a10 *)(temp_v0))->vX(&sp1C, 1);
    }
    return sp1C;
}

inline StreamHolder::~StreamHolder() {
    IG_OBJECT_RELEASE(p);
}

static inline void assign(MediaStreamOwner *self, const StreamHolder &h) {
    MediaStream *v = h.p;
    MediaStream *old;
    if (v != 0) {
        v->_refCount = v->_refCount + 1;
    }
    old = self->stream;
    IG_OBJECT_RELEASE(old);
    self->stream = v;
}

igResult_2e3a10 FUN_002e3a60(MediaStreamOwner *self, int data, int mode) {
    if (data == 0 && self->stream == 0) {
        return g_allocatorFailureStatus;
    }
    if (data == 0 && self->stream != 0) {
        return self->stream->Open(mode);
    }
    if (self->stream == 0 && data != 0) {
        {
            StreamHolder h(((MediaStream *)igFile_Create((int)self->source)));
            assign(self, h);
        }
        if (self->stream == 0) {
            return g_allocatorFailureStatus;
        }
        FUN_002e30b0((int *)self->stream, data);
        return self->stream->Open(mode);
    }
    self->stream->Close();
    {
        StreamHolder h(((MediaStream *)igFile_Create((int)self->source)));
        assign(self, h);
    }
    FUN_002e30b0((int *)self->stream, data);
    return self->stream->Open(mode);
}

void FUN_002e3cb0(S3 *self) {
    Ref3 *r;
    if (self->ref != 0) {
        self->ref->v22();
        r = self->ref;
        if (r != 0) {
            r->u.w = r->u.w - 1;
            if (r->u.b.cnt == 0) igObject_Destroy(r);
        }
        self->ref = 0;
    }
}

void FUN_002e3d30(int *arg0) {
    int temp_s1;
    int *temp_a1;
    int var_v0;
    int temp_a0_2;
    void *temp_s0;
    int var_s0;
    int temp_v1;
    void *temp_a0_3;
    void *temp_a0;

    temp_a0 = (void *)(arg0[5]);
    if ((!temp_a0) || (strcmp(temp_a0, &DAT_004f7910[0]) == 0)) {
        temp_s1 = ((int *)arg0[26])[3];
        var_s0 = strlen(temp_s1) - 1;
        while (var_s0 > 0 && 0x2F != (temp_a0_2 = *(char *)((temp_s1 + var_s0) - 1)) && temp_a0_2 != 0x5C) {
            var_s0 = var_s0 - 1;
        }
        if (0 == (*(void * *)g_stringPool)) {
            var_v0 = (int)StringPool_Allocate(0x10);
            if (var_v0) {
                var_v0 = (int)StringPool_Construct((struct S_2eadf0 *)((void *)var_v0));
            }
            (*(void * *)g_stringPool) = (void *)var_v0;
        }
        temp_s0 = (void *)(((char *)StringPool_Intern((StringPool *)((*(void * *)g_stringPool)), (const char *)(temp_s1 + var_s0))));
        temp_a0_3 = (void *)(arg0[5]);
        if (temp_a0_3) {
            temp_a1 = (int *)((char *)temp_a0_3 - 8);
            temp_v1 = *(int *)((char *)(temp_a0_3) - 4) - 1;
            *(int *)((char *)(temp_a0_3) - 4) = temp_v1;
            if (!temp_v1) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
        arg0[5] = (int)(temp_s0);
    }
}

igResult_2e3a10 FUN_002e3e30(RecordFile *f, int mode) {
    if (f->handle == 0 && mode == 0) {
        return g_allocatorFailureStatus;
    }
    if (f->handle == 0) {
        if (FUN_002e3a60((MediaStreamOwner *)f, mode, 5) == g_allocatorFailureStatus) {
            if (mode != 0) {
                Ref5 *h = f->handle;
                if (h != 0) {
                    h->_refCount = (int)h->_refCount - 1;
                    if (((unsigned long long)((long long)(int)h->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(h);
                    }
                }
                f->handle = 0;
            }
            return g_allocatorFailureStatus;
        }
        f->open = 1;
    }
    if (f->handle == 0) {
        return g_allocatorFailureStatus;
    }
    FUN_002e3d30((int *)f);
    FUN_002e31b0((int)f->handle, 5);
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e3f50(Owner_2e3a10 *arg1) {
    igMetaObject *meta;
    Holder_2e3a10 h;
    T6 *np;
    T6 *old;
    unsigned int n;
    unsigned int i;
    h.ref = ((T6 *)FUN_002c8e10(arg1->f280));
    np = h.ref;
    if (np) {
        ++np->references;
    }
    old = arg1->f192;
    if (old) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
    arg1->f192 = np;
    h.release();
    FUN_002fe600((igTDataList<ChainMeta *> *)arg1->f192, (ChainMeta *)g_igDirEntry_metaObject[0]);
    meta = g_igDirEntry_metaObject[0];
    n = ((unsigned int)igMetaObject_CountTree((MetaTreeNode *)meta));
    for (i = 0; i < n; i++) {
        ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)arg1->f192, (igObject *)(((int)FUN_002fe300((igMetaObject *)meta, (int)i))));
    }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e4090(L7 *arg1) {
    int i;

    for (i = 0; i < arg1->count; i++) {
        arg1->data[i]->f12 = i;
        arg1->data[i]->vX(arg1);
    }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e4120(S8 *o) {
    int i; int s; char *p; int j; int n; int a;
    o->f296 = 8;
    i = 0;
    do {
        a = strlen(FUN_002f8960(i)) + 1;
        i++;
        o->f296 = o->f296 + a;
    } while (i < 46);
    o->f300 = o->f280->v52(o->f296);
    j = 0;
    p = (char *)o->f300;
    ((int *)p)[0] = o->f296;
    ((int *)p)[1] = 46;
    p += 8;
    do {
        s = FUN_002f8960(j);
        n = strlen(s) + 1;
        memcpy(p, s, n);
        j++;
        p += n;
    } while (j < 46);
    if (o->f168) o->f204->v50(o->f300, 2);
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e4240(igIGBFile *arg1) {
    int var_s0;
    void *temp_a0;

    arg1->_objectCount = 0;
    arg1->_memoryRefCount = 0;
    arg1->_objectBufferSize = 0;
    arg1->_memoryRefBufferSize = 0;
    for (var_s0 = 0; var_s0 < arg1->_count; var_s0++) {
        temp_a0 = (void *)(*(int *)(arg1->_data + (var_s0 * 4)));
        ((C156 *)temp_a0)->vX(arg1);
    }
    return g_statusSucceeded;
}

static inline void bump(const Ref10 &r, int off) { int *c = (int *)((char *)r.p->data + off); *c = *c + 1; }

static inline void fillWords(MetaTableWords *l, int c, int *value) {
    if (c >= 0) { if (c <= l->cap) { l->count = c; } else { List_Resize(l, c, 4); } }
}

static inline int indexOfParent(MetaTableTypeList *l, const MetaTableKey &key) {
    int n = l->count;
    int i;
    for (i = 0; i < n; i++) {
        if (key.v == ((int *)l->data)[i]) { return i; }
    }
    return -1;
}

igResult_2e3a10 FUN_002e42d0(MetaTableWriter *self) {
    int base;
    int i;
    self->count = self->types->count;
    self->size = self->count * 24;
    {
    Ref10 inherited((MetaTableWords *)igIntList_Create((int)self->pool));
    fillWords(inherited.p, self->count, 0);
    {
        int n = inherited.p->count;
        int *d = inherited.p->data;
        int k;
        for (k = 0; k < n; k++) { d[k] = DAT_004c2130[0]; }
    }
    {
    Ref10 persistent((MetaTableWords *)igIntList_Create((int)self->pool));
    fillWords(persistent.p, self->count, 0);
    {
        int n = persistent.p->count;
        int *d = persistent.p->data;
        int k;
        for (k = 0; k < n; k++) { d[k] = DAT_004c2138[0]; }
    }
    base = igMetaObject_GetFieldCount((igMetaObject *)g_igObject_metaObject[0]);
    for (i = 0; i < self->count; i++) {
        int j;
        MetaTableFieldList *fields;
        int n;
        MetaTableType *t;
        int off;
        off = i * 4;
        t = *(MetaTableType **)((char *)self->types->data + off);
        fields = t->fields;
        n = fields->count;
        for (j = base; j < n; j++) {
            MetaTableField *f = fields->data[j];
            if (f->inherited == 0) {
                if (f->persistent != 0) {
                    self->size = self->size + 6;
                    bump(inherited, off);
                }
                bump(persistent, off);
            }
        }
        self->size = self->size + (strlen(t->name) + 1);
        self->size = (self->size + 1) & ~1;
    }
    self->block = self->pool->alloc(self->size, 16);
    {
        MetaTableType *t;
        int off;
        int k;
        MetaTableRecord *rec = self->block;
        for (k = 0; k < self->count; k++) {
            MetaTableKey key;
            int len;
            off = k * 4;
            t = *(MetaTableType **)((char *)self->types->data + off);
            len = strlen(t->name) + 1;
            rec->nameSize = (len + 1) & ~1;
            rec->a4 = t->a16;
            rec->a8 = t->a20;
            rec->fieldCount = *(int *)((char *)inherited.p->data + off);
            {
                MetaTableTypeList *l = self->types;
                *(int *)&key = t->parent;
                rec->parent = indexOfParent(l, key);
            }
            rec->persistCount = base + *(int *)((char *)persistent.p->data + off);
            rec++;
        }
    }
    {
        char *out = (char *)(self->block + self->count);
        MetaTableSwapper *desc;
        short *p;
        MetaTableField *f;
        int k;
        int j;
        int n;
        int off;
        MetaTableType *t;
        MetaTableFieldList *fields;
        desc = (MetaTableSwapper *)((void *)igShortMetaField_GetDefaultDescriptor());
        for (k = 0; k < self->count; k++) {
            off = k * 4;
            t = *(MetaTableType **)((char *)self->types->data + off);
            strcpy(out, t->name);
            fields = t->fields;
            j = base;
            n = fields->count;
            out += self->block[k].nameSize;
            p = (short *)out;
            for (; j < n; j++) {
                f = fields->data[j];
                if (f->persistent != 0 && f->inherited == 0) {
                    p[0] = igMetaField_GetTypeIndex((TypeIndexView *)f);
                    p[1] = f->size;
                    p[2] = f->offset;
                    p += 3;
                }
            }
            if (self->swapped != 0) {
                desc->swap(out, *(int *)((char *)inherited.p->data + off) * 3);
            }
            out = (char *)p;
        }
    }
    if (self->swapped != 0) { self->swapper->swap(self->block, self->count * 6); }
    return g_statusSucceeded;
    }
    }
}

igResult_2e3a10 FUN_002e47f0(S11 *arg1) {
    int i;
    int j;
    int s5;
    int *s4;
    int s2;
    O11 *p;
    arg1->f136 = ((T11 *)((void *)FUN_002fc250()))->cnt;
    arg1->f140 = arg1->f136 * 12;
    for (i = 0; i < arg1->f136; i++) {
        arg1->f140 = arg1->f140 + (strlen(((T11 *)((void *)FUN_002fc250()))->data[i]->vX()->f28) + 1);
    }
    arg1->f184 = arg1->f280->vX(arg1->f140, 16);
    s5 = 0;
    s4 = (int *)arg1->f184;
    for (i = 0; i < arg1->f136; i++) {
        p = ((T11 *)((void *)FUN_002fc250()))->data[i];
        s4[s5] = strlen(p->vX()->f28) + 1;
        s5++;
        s4[s5] = p->vX()->f16;
        s5++;
        s4[s5] = p->vX()->f20;
        s5++;
    }
    s2 = arg1->f184 + arg1->f136 * 12;
    for (j = 0; j < arg1->f136; j++) {
        strcpy(s2, ((T11 *)((void *)FUN_002fc250()))->data[j]->vX()->f28);
        s2 += *(int *)(arg1->f184 + j * 12);
    }
    if (arg1->f168 != 0) arg1->f204->vX(arg1->f184, arg1->f136 * 3);
    return g_statusSucceeded;
}

static inline char *nameOf(const Ref12 &r, int i) {
    char *n = r.p->data[i]->name;
    n = (n == 0) ? (*(char * *)DAT_004c22f0) : n;
    return n;
}

igResult_2e3a10 FUN_002e4a40(IgbNameWriter *self) {
    Ref12 names(g_globalContext->names);
    int i;
    int *lengths;
    char *out;
    self->count = (names.p != 0) ? names.p->count : 0;
    i = 0;
    self->blockSize = self->count * 4 + 12;
    for (; i < self->count; i++) {
        self->blockSize += strlen(nameOf(names, i)) + 1;
    }
    self->block = self->pool->alloc(self->blockSize, 16);
    {
        int *b = self->block;
        lengths = b + 3;
        b[0] = self->blockSize;
        b[1] = 1;
        b[2] = self->count;
    }
    for (i = 0; i < self->count; i++) {
        lengths[i] = strlen(nameOf(names, i)) + 1;
    }
    out = (char *)(lengths + self->count);
    for (i = 0; i < self->count; i++) {
        strcpy(out, nameOf(names, i));
        out += lengths[i];
    }
    if (self->swapped != 0) { self->swapper->swap(self->block, self->count + 3); }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e4c90(Self_2e3a10 *self) {
    IList_2e3a10 *l = self->list;
    int n, i, k;
    if (l != 0) { n = l->count; if (n > 0) {
        char *p;
        int *q;
        int total;
        self->b213 = 1;
        total = (n + 3) * 4;
        self->size228 = total;
        for (i = 0; i < n; i++) {
            self->size228 = self->size228 + (strlen(self->list->data[i]->name) + 1);
        }
        self->buf224 = (int *)self->alloc280->Alloc53(self->size228, 16);
        self->buf224[0] = self->size228;
        self->buf224[1] = 1;
        self->buf224[2] = n;
        q = self->buf224 + 3;
        for (i = 0; i < n; i++) {
            q[i] = strlen(self->list->data[i]->name) + 1;
        }
        p = (char *)self->buf224 + total;
        for (k = 0; k < n; k++) {
            strcpy(p, self->list->data[k]->name);
            p += strlen(p) + 1;
        }
        if (self->flag168 != 0) {
            self->sink204->Sink50(self->buf224, n + 2);
        }
    goto done; } } self->b213 = 0; done:
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e5110(IgbFixReader *self) {
    int n;
    int i;
    if (self->fixed != 0) { return g_statusSucceeded; }
    {
        IgbFixWords *old = self->words;
        int pool = self->pool;
        RELEASE(old)
        self->words = (IgbFixWords *)FUN_002c9130(pool);
    }
    {
        int c = self->count;
        IgbFixWords *l = self->words;
        if (c >= 0) { if (c <= l->cap) { l->count = c; } else { List_Resize(l, c, 4); } }
    }
    {
        IgbFixPlain *old = self->map;
        int pool = self->pool;
        RELEASE(old)
        self->map = (IgbFixPlain *)FUN_002bd680(pool);
    }
    {
        IgbFixPlain *old = self->sorted;
        int pool = self->pool;
        RELEASE(old)
        self->sorted = (IgbFixPlain *)FUN_002c72c0(pool);
    }
    n = self->count;
    for (i = 0; i < n; i++) {
        IgbFixObject *o = self->data[i];
        IgbFixObject *r;
        IgbFixObject *old;
        int c;
        if (o == o->replacement(self)) {
            IgbFixPlain *list = self->sorted;
            IgbFixRetain keep(o);
            List_InsertWords(list, FUN_00142bb0(list, &keep), 1, &keep);
        }
        {
            int word;
            IgbFixWords *w = self->words;
            word = o->word;
            int k = w->count;
            if (k != 0 && i >= 0 && k > i) { w->data[i] = word; }
        }
        o->attach(o->word);
        o->reset(0);
        o->index = i;
        r = o->replacement(self);
        if (r != 0) { r->rc = r->rc + 1; }
        old = self->data[i];
        RELEASE(old)
        c = self->count;
        if (c != 0 && i >= 0 && c > i) { self->data[i] = r; }
    }
    self->fixed = 1;
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e54e0(O17 *o) {
    int i;
    int n;
    A17 *p = o->f280; int x = o->f148;
    o->f180 = p->a(x, 16);
    o->f252 = o->f180;
    n = o->n;
    for (i = 0; i < n; i++) {
        ((B17 *)FUN_002d7e90((int *)o, i))->b(o);
    }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e5590(O18 *o) {
    int *t = (int *)o->mgr->alloc(48, 16);
    memset(t, 0, 48);
    t[0] = o->f124; t[1] = o->f112; t[2] = o->f132; t[3] = o->f128; t[4] = o->f148; t[5] = o->f144;
    t[6] = o->f156; t[7] = o->f152; t[8] = o->f140; t[9] = o->f136; t[10] = o->f96;
    int v = o->f100;
    if (o->b212) v |= 0x80000000;
    if (o->b213) v |= 0x40000000;
    if (o->b36) v |= 0x20000000;
    if (o->b65) v |= 0x10000000;
    t[11] = v;
    if (o->b168) o->f204->a(t, 12);
    o->f104->b(t, 4, 12);
    o->mgr->rel(t);
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e56f0(Obj19 *arg1) {
    int s4 = arg1->f104->v116(arg1->f184, arg1->f140, 1);
    int s3 = arg1->f104->v116(arg1->f236, arg1->f240, 1);
    int s2 = arg1->f104->v116(arg1->f172, arg1->f132, 1);
    if (arg1->f224 != 0) {
        arg1->f104->v116(arg1->f224, arg1->f228, 1);
        arg1->f280->v264(arg1->f224);
        arg1->f224 = 0;
    }
    int s1 = 1;
    if (arg1->f65 != 0) {
        s1 = arg1->f104->v116(arg1->f300, arg1->f296, s1);
    }
    int s0 = arg1->f104->v116(arg1->f176, arg1->f124, 1);
    if (arg1->f168 != 0) {
        arg1->f204->v208(arg1->f120, 2);
    }
    int s7 = arg1->f104->v116(arg1->f120, arg1->f116, 1);
    if (arg1->f220 > -1) {
        if (arg1->f168 != 0) {
            arg1->f204->v208((int)((char *)arg1 + DAT_00586280[0]->f8), 1);
        }
        arg1->f104->v116((int)((char *)arg1 + DAT_00586280[0]->f8), 4, 1);
    }
    int s8 = arg1->f104->v116(arg1->f180, arg1->f148, 1);
    int v = arg1->v136();
    if (s7 + (s3 + (s4 + (v + (s8 + (s0 + (s2 + s1)))))) == 0) {
        return g_allocatorFailureStatus;
    } else {
        return g_statusSucceeded;
    }
}

igResult_2e3a10 FUN_002e5950(void *arg1) {
    if (*(int *)((char *)arg1 + 196) != 0) {
        FUN_002e3cb0((S3 *)arg1);
    }
    return igResult_2e3a10(*(int *)0x4FB410);
}

igResult_2e3a10 FUN_002e5990(T21 *o) {
    o->mgr->rel(o->f172); o->f172 = 0;
    o->mgr->rel(o->f176); o->f176 = 0;
    o->mgr->rel(o->f180); o->f180 = 0;
    o->mgr->rel(o->f184); o->f184 = 0;
    o->mgr->rel(o->f236); o->f236 = 0;
    if (o->f120) o->mgr->rel(o->f120);
    o->f296 = 0;
    if (o->f300) { o->mgr->rel(o->f300); o->f300 = 0; }
    Rc_2e3a10 *r = o->f304;
    if (r) { r->f4 -= 1; if ((r->f4 & 0x7fffff) == 0) igObject_Destroy(r); }
    o->f304 = 0;
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e5ac0(void *arg1) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(arg1) + 28));
    if (*(int *)((char *)(temp_a1) + 8) > 0) {
        *(int *)((char *)(arg1) + 220) = FUN_002d8620((int)arg1, (int)temp_a1, 0, 0);
        *(char *)((char *)(arg1) + 212) = 1;
    }
    return g_statusSucceeded;
}

int Gap__Core__igIGBFile__vfunc_28(C23 *arg0, int arg1) {
    int *pp; Rel23 *t; Rel23 *t2; Rel23 *a; Rel23 *b;
    FUN_00306e50(((LogContext * *)g_objectSystem)[0]->f56, 2, (const char *)DAT_004f9a80, (char *)((char *)arg0 + 0x42), 0, 0);
    igResult_2e3a10 sp7C = FUN_002e3e30((RecordFile *)arg0, arg1);
    pp = (int *)((int)&sp7C + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp78 = FUN_002e5ac0(arg0);
    pp = (int *)((int)&sp78 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    FUN_00302540((L_302540 *)arg0, (Field *)DAT_00586730[0]);
    a = (Rel23 *)igIntMetaField_GetDefaultDescriptor();
    if (a != 0) a->rc = a->rc + 1;
    t = arg0->f204;
    REL23(t)
    arg0->f204 = a;
    b = (Rel23 *)igShortMetaField_GetDefaultDescriptor();
    if (b != 0) b->rc = b->rc + 1;
    t2 = arg0->f208;
    REL23(t2)
    arg0->f208 = b;
    igResult_2e3a10 sp74 = FUN_002e3f50((Owner_2e3a10 *)arg0);
    pp = (int *)((int)&sp74 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp70 = FUN_002e4090((L7 *)arg0);
    pp = (int *)((int)&sp70 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp6C = FUN_002e4120((S8 *)arg0);
    pp = (int *)((int)&sp6C + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp68 = FUN_002e4240((igIGBFile *)arg0);
    pp = (int *)((int)&sp68 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp64 = FUN_002e42d0((MetaTableWriter *)arg0);
    pp = (int *)((int)&sp64 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp60 = FUN_002e47f0((S11 *)arg0);
    pp = (int *)((int)&sp60 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp5C = FUN_002e4a40((IgbNameWriter *)arg0);
    pp = (int *)((int)&sp5C + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp58 = FUN_002e4c90((Self_2e3a10 *)arg0);
    pp = (int *)((int)&sp58 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    if (arg0->f36 == 0) {
    igResult_2e3a10 sp54 = FUN_002e53f0(arg0);
    pp = (int *)((int)&sp54 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    } else {
    igResult_2e3a10 sp50 = FUN_002e5110((IgbFixReader *)arg0);
    pp = (int *)((int)&sp50 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp4C = FUN_002e4e60((Cx *)arg0);
    pp = (int *)((int)&sp4C + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp48 = FUN_002e4f60(arg0);
    pp = (int *)((int)&sp48 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    }
    igResult_2e3a10 sp44 = FUN_002e54e0((O17 *)arg0);
    pp = (int *)((int)&sp44 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp40 = FUN_002e5590((O18 *)arg0);
    pp = (int *)((int)&sp40 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp3C = FUN_002e56f0((Obj19 *)arg0);
    pp = (int *)((int)&sp3C + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp38 = FUN_002e5950(arg0);
    pp = (int *)((int)&sp38 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    igResult_2e3a10 sp34 = FUN_002e5990((T21 *)arg0);
    pp = (int *)((int)&sp34 + 0);
    if (*pp == g_allocatorFailureStatus.v) return 0;
    if (arg0->f278 == 1) { igResult_2e3a10 sp30 = arg0->v128(); }
    return arg0->f8;
}

igResult_2e3a10 FUN_002e5f70(T24 *arg1, int arg2) {
    Obj24 *o;
    int *pp;
    if ((arg1->f104 == 0) && (arg2 == 0)) {
        return g_allocatorFailureStatus;
    }
    if (arg1->f104 == 0) {
        igResult_2e3a10 r = FUN_002e3a60((MediaStreamOwner *)arg1, arg2, 4);
        pp = (int *)((int)&r + 0);
        if (*pp == g_allocatorFailureStatus.v) {
            if (arg2 != 0) {
                o = arg1->f104;
                if (o != 0) {
                    o->refs = o->refs - 1;
                    if (((unsigned long long)((long long)(int)o->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(o);
                    }
                }
                arg1->f104 = 0;
            }
            return g_allocatorFailureStatus;
        }
        arg1->f196 = 1;
    }
    if (arg1->f104 == 0) {
        return g_allocatorFailureStatus;
    }
    FUN_002e3d30((int *)arg1);
    FUN_002e31b0((int)arg1->f104, 4);
    return g_statusSucceeded;
}

igResult_2e3a10 igIGBFile_ReadHeader(S25 *arg1) {
    igResult_2e3a10 sp5C = igIGBFile_GetSectionBuffer((IgbSectionBufferOwner *)arg1, 0xC0);
    int *pp;
    int a;
    H_2e3a10 *h;
    Obj25_2e3a10 *o;
    Obj25_2e3a10 *t;

    pp = (int *)((int)&sp5C + 0);
    a = D_004fb418[0];
    if (*pp == g_allocatorFailureStatus.v) {
        return igResult_2e3a10(a);
    }
    h = arg1->f264;
    arg1->f104->v27(h, 4, 0xC);
    o = (Obj25_2e3a10 *)igIntMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->rc = o->rc + 1;
    }
    t = arg1->f204;
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long) ((long long) t->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg1->f204 = o;
    o = (Obj25_2e3a10 *)igShortMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->rc = o->rc + 1;
    }
    t = arg1->f208;
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long) ((long long) t->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg1->f208 = o;
    if (h->f40 != arg1->f96) {
        arg1->f204->v52(h, 0xC);
        if (h->f40 == arg1->f96) {
            arg1->f168 = 1;
        }
    } else {
        arg1->f168 = 0;
    }
    if (h->f40 != arg1->f96) {
        return g_allocatorFailureStatus;
    } else {
        arg1->f100 = (int)*(unsigned short *)&h->f44;
        if ((int)arg1->f100 > 7) {
            return g_allocatorFailureStatus;
        } else {
            arg1->f212 = (h->f44 & 0x80000000) != 0;
            arg1->f213 = (h->f44 & 0x40000000) > 0;
            arg1->f214 = (h->f44 & 0x20000000) > 0;
            arg1->f215 = h->f44 == 1;
            arg1->f292 = (h->f44 & 0x10000000) > 0;
            if (arg1->f215 != 0) {
                arg1->f216 = 1;
            } else {
                arg1->f216 = 0;
            }
            arg1->f124 = h->f0;
            arg1->f112 = h->f4;
            arg1->f132 = h->f8;
            arg1->f128 = h->f12;
            arg1->f148 = h->f16;
            arg1->f144 = h->f20;
            arg1->f156 = h->f24;
            arg1->f152 = h->f28;
            arg1->f140 = h->f32;
            arg1->f136 = h->f36;
            return g_statusSucceeded;
        }
    }
}

igResult_2e3a10 FUN_002e6330(Q26 *arg1) {
    igResult_2e3a10 sp3C = igIGBFile_GetSectionBuffer((IgbSectionBufferOwner *)arg1, arg1->f132);
    int *pp;
    int a;
    bool var_a0;
    int var_v1;

    pp = (int *)((int)&sp3C + 0);
    a = D_004fb418[0];
    if (*pp == g_allocatorFailureStatus.v) {
        return igResult_2e3a10(a);
    }
    arg1->f172 = arg1->f264;
    var_a0 = true;
    if (arg1->f132 != 0) {
        var_a0 = (*(DW4VC_108_1 **)((char *)arg1 + 104))->vX(arg1->f172, arg1->f132, 1) == 1;
    }
    var_v1 = g_statusSucceeded.v;
    if (!(int)var_a0) {
        var_v1 = g_allocatorFailureStatus.v;
    }
    return igResult_2e3a10(var_v1);
}

igResult_2e3a10 FUN_002e6f50(int *arg1) {
    int n;
    char *p;
    char c;
    arg1[50] = ((VC27 *)arg1[70])->vX(*(int *)(arg1[26] + 12));
    n = strlen(arg1[50]);
    while (--n >= 0) {
        p = (char *)arg1[50] + n;
        c = *p;
        if (c == 0x2F || c == 0x5C) {
            *p = 0;
            break;
        }
    }
    if (n < 0) {
        *(char *)arg1[50] = 0;
    }
    return g_statusSucceeded;
}

void FUN_002e7000(void) {
    FUN_00306e50(*(int *)((char *)(((LogContext * *)g_objectSystem)[0]) + 56), 2, (const char *)DAT_004f9ac8, (char *)&GPR_00554c04, 0, 0);
}

igResult_2e3a10 FUN_002e7030(Z29 *arg1) {
    int hi;
    int a2;
    hi = (arg1->f260 - arg1->f80) % arg1->f260;
    if (hi > 0) {
        memcpy(arg1->f264, arg1->f264 + arg1->f80, hi);
    }
    a2 = arg1->f260 - hi;
    if (arg1->f88 < hi + (arg1->f84 + a2)) {
        a2 = (arg1->f88 - arg1->f84) - hi;
    }
    if (arg1->f104->vX(arg1->f264 + hi, a2, 1) != 1) {
        return g_allocatorFailureStatus;
    } else {
        arg1->f80 = 0;
        return g_statusSucceeded;
    }
}

static inline T30 *castToKind(T30 *object) {
    if (object != 0 && igObject_IsKindOf((void *)object, (igMetaObject *)g_igDirEntry_metaObject[0]) != 0) {
        return object;
    }
    return 0;
}

igResult_2e3a10 igIGBFile_ReadObjectSection(IGBReader31 *file) {
    int pool;
    igObjectList *list;
    int i;
    file->position = file->bufferSize;
    file->consumed = 0;
    file->bufferEnd = file->sectionSize;
    list = file->objects;
    pool = file->pool;
    if (list != 0) {
        list->_refCount = list->_refCount - 1;
        if ((list->_refCount & 0x7FFFFF) == 0) igObject_Destroy(list);
    }
    file->objects = (igObjectList *)FUN_002c72c0(pool);
    ObjectList_ResizeRetained((L_301ee0 *)file->objects, file->objectCount);
    if (FUN_002e7030((Z29 *)file) == g_allocatorFailureStatus) {
        return g_allocatorFailureStatus;
    }
    for (i = 0; i < file->objectCount; i++) {
        igSmartPointer<SectionObject> object = igIGBFile_ReadObject((C30 *)file);
        if (object.p == 0) {
            return g_allocatorFailureStatus;
        }
        if (file->remapPools != 0 && file->poolTable != 0 && g_useOwnerAllocator == 0) {
            int index = object->memoryPoolIndex();
            if (index > 0) {
                object->setMemoryPool(file->poolTable->_data[index]);
            }
        } else {
            object->setMemoryPool(-1);
        }
        SectionObject *entry = object.p;
        list = file->objects;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igObject *old = ((igObject **)list->_data)[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (list->_count != 0 && i >= 0 && i < list->_count) {
            ((SectionObject **)list->_data)[i] = entry;
        }
    }
    if (file->failed != 0) {
        return g_allocatorFailureStatus;
    }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e7640(IgbObjectSection *self) {
    int count = 0;
    int fail;
    int pos;
    int chunk;
    int words;
    int i;
    int base;
    self->stream->read(&self->size, 4, 1);
    self->stream->read(&count, 4, 1);
    if (self->swapped != 0) {
        self->swapper->swap(&self->size, 1);
        self->swapper->swap(&count, 1);
    }
    if (igIGBFile_GetSectionBuffer((IgbSectionBufferOwner *)self, 0x1000).isFailed(fail)) {
        return igResult_2e3a10(fail);
    }
    pos = 8;
    ObjectList_ResizeRetained((L_301ee0 *)self, count);
    for (; pos < self->size; pos += chunk) {
        int rest = self->size - pos;
        chunk = self->bufferCap & ~1;
        if (chunk > rest) { chunk = rest; }
        words = chunk >> 1;
        self->stream->read(self->buffer, chunk, 1);
        if (self->swapped != 0) { self->swapper16->swap(self->buffer, words); }
        base = (unsigned int)(pos - 8) >> 1;
        for (i = 0; i < words; i++) {
            IgbSectionObject *o = (IgbSectionObject *)thunk_FUN_002d7e90((int *)self->source, self->buffer[i]);
            int index;
            IgbSectionObject *old;
            int n;
            if (o != 0) { o->rc = o->rc + 1; }
            index = i + base;
            old = self->data[index];
            if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
            n = self->count;
            if (n != 0 && index >= 0 && n > index) { self->data[index] = o; }
        }
    }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e78b0(O33 *arg1) {
    int temp_s1;
    int temp_s0;
    int i;
    T33 *temp_a0;
    T33 *temp_a0_2;
    temp_a0 = arg1->list;
    temp_s1 = arg1->n;
    temp_s0 = arg1->f280;
    if (temp_a0 != 0) {
        temp_a0->references = temp_a0->references - 1;
        if (((unsigned long long)(long long)temp_a0->references & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg1->list = (T33 *)FUN_002c9130(temp_s0);
    temp_a0_2 = arg1->list;
    if (temp_s1 >= 0) {
        if (temp_s1 <= temp_a0_2->cap) {
            temp_a0_2->n = temp_s1;
        } else {
            List_Resize(temp_a0_2, temp_s1, 4);
        }
    }
    for (i = 0; i < temp_s1; i++) {
        ((E33 *)FUN_002d7e90((int *)arg1, i))->vX(arg1);
    }
    return g_statusSucceeded;
}

igResult_2e3a10 igIGBFile_ReadObjectSectionOld(IGBReader34 *file) {
    int pool;
    int i;
    file->position = file->bufferSize;
    file->consumed = 0;
    file->bufferEnd = file->sectionSize;
    if (file->oldReferences != 0) {
        IndexList *old = file->referenceIndices;
        pool = file->pool;
        igRelease((igObject *)old);
        file->referenceIndices = (IndexList *)FUN_002c9130(pool);
        int count = file->objectCount;
        IndexList *indices = file->referenceIndices;
        if (count >= 0) {
            if (count <= indices->_capacity) {
                indices->_count = count;
            } else {
                List_Resize(indices, count, 4);
            }
        }
        igObject *previous = file->resolved;
        pool = file->pool;
        igRelease(previous);
        file->resolved = (igObject *)FUN_002bd680(pool);
    }
    if (FUN_002e7030((Z29 *)file) == g_allocatorFailureStatus) {
        return g_allocatorFailureStatus;
    }
    ObjectList_ResizeRetained((L_301ee0 *)file, file->objectCount);
    for (i = 0; i < file->objectCount; i++) {
        igSmartPointer<SectionObject> object = igIGBFile_ReadObject((C30 *)file);
        if (object.p == 0) {
            return g_allocatorFailureStatus;
        }
        object->index = i;
        file->set(i, object);
        if (file->remapPools != 0 && file->poolTable != 0 && g_useOwnerAllocator == 0) {
            int index = object->memoryPoolIndex();
            if (index > 0) {
                object->setMemoryPool(file->poolTable->_data[index]);
            }
        } else {
            object->setMemoryPool(-1);
        }
        object->readFinished(file);
        if (file->oldReferences != 0) {
            int reference = object->referenceIndex;
            IndexList *indices = file->referenceIndices;
            if (indices->_count != 0 && i >= 0 && i < indices->_count) {
                indices->_data[i] = reference;
            }
            object->setReferenceIndex(object->referenceIndex);
            object->setReferenceTarget(0);
            object->index = i;
            file->setRaw(i, object->resolve(file));
        }
    }
    if (file->failed != 0) {
        return g_allocatorFailureStatus;
    }
    return g_statusSucceeded;
}

int Gap__Core__igIGBFile__vfunc_27(void *arg0) {
    if (*(int *)((char *)(*(int *)((char *)(arg0) + 104)) + 20) == 4) {
        return *(int *)((char *)(arg0) + 264) + *(int *)((char *)(arg0) + 80);
    }
    return *(int *)((char *)(arg0) + 252);
}

void Gap__Core__igIGBFile__vfunc_26(IgbBlockCursor *self, int at) {
    if (self->stream->mode == 4) {
        int prev = self->base + self->offset;
        self->offset = at - self->base;
        self->done = self->done + (at - prev);
        if (self->done != self->total) {
            if (self->offset > self->cap - 9) {
                FUN_002e7030((Z29 *)self);
                return;
            }
            if (self->offset + (self->pending * 4 + FUN_002e3a10(self, at)) > self->cap) {
                FUN_002e7030((Z29 *)self);
            }
        }
    } else {
        self->mark = at;
    }
}

igResult_2e3a10 FUN_002e7ed0(S37 *arg1) {
    arg1->f280->vX(arg1->f200);
    arg1->f200 = 0;
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e7f20(IgbMetaSection *self) {
    int fail;
    IgbRegistryTable *table;
    int count;
    int *sizes;
    char *name;
    int i;
    if (igIGBFile_GetSectionBuffer((IgbSectionBufferOwner *)self, self->bytes).isFailed(fail)) {
        return igResult_2e3a10(fail);
    }
    self->buffer = self->work;
    self->stream->read(self->buffer, self->bytes, 1);
    table = (IgbRegistryTable *)((void *)FUN_002fc250());
    count = table->count;
    sizes = self->buffer;
    name = (char *)sizes + self->entries * 12;
    if (self->swapped != 0) { self->swapper->swap(sizes, self->entries * 3); }
    {
        IgbTypeRefList *v = ((IgbTypeRefList *)FUN_002c8af0(self->pool));
        IgbTypeRefList *old;
        if (v != 0) { v->rc = v->rc + 1; }
        old = self->types;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->types = v;
    }
    {
        IgbTypeRefList *l = self->types;
        int want = self->entries;
        if (want >= l->count) { List_Reserve((L_2d6680 *)l, want, 4); }
    }
    for (i = 0; i < self->entries; i++) {
        bool found = false;
        IgbRegistryType *t = 0;
        int j;
        for (j = 0; j < count; j++) {
            t = table->data[j];
            if (strcmp(t->meta()->name, name) == 0) { found = true; break; }
        }
        if (!found) { t = 0; } else { t->meta(); }
        ObjectList_AppendRetained((igObjectList *)self->types, (igObject *)t);
        name += sizes[i * 3];
    }
    self->buffer = 0;
    return g_statusSucceeded;
}

void Gap__Core__igIGBFile__vfunc_13(Obj39 *arg0) {
    T39 *s0;
    s0 = ((T39 *)Memory_GetDefaultAllocator());
    if (s0) s0->references++;
    Rel39::go(arg0->m280);
    arg0->m280 = s0;
    s0 = ((T39 *)Memory_GetDefaultAllocator());
    if (s0) s0->references++;
    Rel39::go(arg0->m284);
    arg0->m284 = s0;
    s0 = ((T39 *)Memory_GetDefaultAllocator());
    if (s0) s0->references++;
    Rel39::go(arg0->m288);
    arg0->m288 = s0;
}

static inline void assignTypes(IgbTypeReader *self, const TypeListHolder &h) {
    ReflectedTypeList *v = h.p;
    ReflectedTypeList *old;
    if (v != 0) { v->rc = v->rc + 1; }
    old = self->types;
    if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
    self->types = v;
}

static inline void addType(ReflectedTypeList *l, int v) {
    int idx;
    idx = l->count;
    if (l->cap > idx) { l->count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
    l->data[idx] = v;
}

igResult_2e3a10 FUN_002e82a0(IgbTypeReader *self) {
    IgbTypeHeader hdr;
    int *sizes;
    char *name;
    int value;
    int nameCount;
    int i;
    if (self->stream->read(&hdr, 12, 1) != 1) { return g_allocatorFailureStatus; }
    if (self->swapped != 0) { self->swapper->swap(&hdr, 3); }
    self->bufferSize = hdr.size - 12;
    self->typeCount = hdr.count;
    if (self->typeCount <= 0) { return g_statusSucceeded; }
    self->buffer = self->work;
    if (self->stream->read(self->buffer, self->bufferSize, 1) != 1) { return g_allocatorFailureStatus; }
    sizes = self->buffer;
    if (self->swapped != 0) { self->swapper->swap(sizes, self->typeCount); }
    name = (char *)sizes + self->typeCount * 4;
    {
    Ref40 names(g_globalContext->names);
    Ref40 values(g_globalContext->values);
    nameCount = 0;
    if (names.p != 0) { nameCount = ((ReflectedNameList *)names.p)->count; }
    {
        TypeListHolder h((ReflectedTypeList *)igIntList_Create((int)self->pool));
        assignTypes(self, h);
    }
    {
        ReflectedTypeList *l = self->types;
        int want = self->typeCount;
        if (want >= l->count) { List_Reserve((L_2d6680 *)l, want, 4); }
    }
    for (i = 0; i < self->typeCount; i++) {
        bool found = false;
        value = 16;
        int j;
        for (j = 0; j < nameCount; j++) {
            char *n = ((ReflectedNameList *)names.p)->data[j]->name;
            n = (n == 0) ? (*(char * *)DAT_004c22f0) : n;
            if (strcmp(n, name) == 0) { found = true; break; }
        }
        if (found) { value = ((ReflectedValueList *)values.p)->data[j]; }
        addType(self->types, value);
        name += sizes[i];
    }
    self->buffer = 0;
    return g_statusSucceeded;
    }
}

inline int load(T41 *t, int *fail) {
    igResult_2e3a10 r = FUN_002e7030((Z29 *)t);
    int *pp;
    pp = (int *)((int)&r + 0);
    *fail = D_004fb418[0];
    return *pp;
}

igResult_2e3a10 FUN_002e8670(T41 *arg1) {
    int fail;
    int n;
    int i;

    arg1->f252 = arg1->f180;
    arg1->f80 = arg1->f260;
    arg1->f84 = 0;
    arg1->f88 = arg1->f148;
    int got = load(arg1, &fail);
    if (got == g_allocatorFailureStatus.v) {
        return igResult_2e3a10(fail);
    }
    n = arg1->count;
    for (i = 0; i < n; i++) {
        if (igObject_IsKindOf(arg1->data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
            ((EE *)FUN_002d7e90((int *)arg1, i))->v128(arg1);
        }
    }
    if (arg1->f100 < 4) {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(arg1->data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                ((EE *)FUN_002d7e90((int *)arg1, i))->v132(arg1);
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(arg1->data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                Ref41 e((EE *)FUN_002d7e90((int *)arg1, i));
                e.p->v136(arg1);
            }
        }
    }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e8880(L42 *arg1) {
    int i;
    for (i = 0; i < arg1->n; i++) {
        if (((igObject_IsKindOf(arg1->arr[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
            ((O42 *)FUN_002d7e90((int *)arg1, i))->v30(arg1);
        }
    }
    if (arg1->f100 < 4) {
        for (i = 0; i < arg1->n; i++) {
            if (((igObject_IsKindOf(arg1->arr[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
                ((O42 *)FUN_002d7e90((int *)arg1, i))->v31(arg1);
            }
        }
    } else {
        for (i = 0; i < arg1->n; i++) {
            if (((igObject_IsKindOf(arg1->arr[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
                ((O42 *)FUN_002d7e90((int *)arg1, i))->v32(arg1);
            }
        }
    }
    return g_statusSucceeded;
}

void FUN_002e8a10(void *arg0) {
    if (*(int *)((char *)arg0 + 196) > 0) {
        FUN_002e3cb0((S3 *)arg0);
    }
}

void FUN_002e8a40(T44 *a) {
    REL44(a->f188);
    REL44(a->f188);
    a->f188 = 0;
    REL44(a->f192);
    a->f192 = 0;
    REL44(a->f60);
    a->f60 = 0;
    a->f172 = 0;
    a->f176 = 0;
    a->f184 = 0;
    a->f180 = 0;
    REL44(a->f92);
    a->f92 = 0;
    a->f120 = 0;
    REL44(a->f40);
    a->f40 = 0;
    a->f280->v64(a->f264);
    a->f264 = 0;
    a->f296 = 0;
    int t = a->f300;
    if (t != 0) {
        a->f280->v64(t);
        a->f300 = 0;
    }
    REL44(a->f304);
    a->f304 = 0;
}

void Gap__Core__igIGBFile__vfunc_04(S_arg0 *arg0) {
    /* matching construct: variant search — local declaration order [4, 3, 2, 1, 0] decides the stack slots and registers */
    int var_s1;
    int temp_s0;
    S_ref_2e3a10 *temp_a0_3;
    S_ref_2e3a10 *temp_a0_2;
    S_list *temp_v0;

    temp_v0 = arg0->f44;
    if (temp_v0 != 0) {
        temp_s0 = temp_v0->f8;
        for (var_s1 = 0; var_s1 < temp_s0; var_s1++) {
            arg0->f16[var_s1]->vX(arg0->f44->f16[var_s1]);
        }
        temp_a0_2 = (S_ref_2e3a10 *)arg0->f44;
        if (temp_a0_2 != 0) {
            temp_a0_2->references = temp_a0_2->references - 1;
            if (((unsigned long long)(long long)temp_a0_2->references & 0x7fffffULL) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->f44 = 0;
    }
    temp_a0_3 = (S_ref_2e3a10 *)arg0->f44;
    if (temp_a0_3 != 0) {
        temp_a0_3->references = temp_a0_3->references - 1;
        if (((unsigned long long)(long long)temp_a0_3->references & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0_3);
        }
    }
    arg0->f44 = 0;
    Gap__Core__igObject__vfunc_02((int)arg0);
}

igResult_2e3a10 FUN_002e8d40(A46 *arg1) {
    R46 *temp_s0;
    R46 *t;

    if (arg1->f212 != 0) {
        if (arg1->f104->vX((int)((char *)arg1 + DAT_00586280[0]->f8), 4, 1) != 1) {
            return g_allocatorFailureStatus;
        }
        if (arg1->f168 != 0) {
            arg1->f204->vX((int)((char *)arg1 + DAT_00586280[0]->f8), 1);
        }
        temp_s0 = ((Q46 *)FUN_002d7e90((int *)arg1, arg1->f220))->f24;
        if (temp_s0 != 0) {
            temp_s0->f4 = temp_s0->f4 + 1;
        }
        t = arg1->f28;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg1->f28 = temp_s0;
    }
    return g_statusSucceeded;
}

static inline void *stringPool() {
    if ((*(void * *)g_stringPool) == 0) {
        void *p = StringPool_Allocate(16);
        if (p != 0) { p = ((void *)StringPool_Construct((struct S_2eadf0 *)p)); }
        (*(void * *)g_stringPool) = p;
    }
    return (*(void * *)g_stringPool);
}

static inline void setPooled(char **dst, char *src) {
    char *v = ((char *)StringPool_Intern((StringPool *)(stringPool()), src));
    char *old = *dst;
    if (old != 0) {
        PooledStringHead *h = (PooledStringHead *)(old - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunkOwnerView *)h->chunk, (int)h); }
    }
    *dst = v;
}

igResult_2e3a10 FUN_002e8e50(IgbExternalReader *self) {
    if (self->hasExternals != 0) {
        IgbExternalHeader hdr;
        int count;
        int *sizes;
        char *name;
        int i;
        IgbExternalDir *dir;
        if (self->stream->read(&hdr, 12, 1) != 1) { return g_allocatorFailureStatus; }
        if (self->swapped != 0) { self->swapper->swap(&hdr, 3); }
        self->bytes = hdr.size - 12;
        count = hdr.count;
        self->buffer = self->pool->alloc(self->bytes, 16);
        if (self->stream->read(self->buffer, self->bytes, 1) != 1) { return g_allocatorFailureStatus; }
        sizes = self->buffer;
        if (self->swapped != 0) { self->swapper->swap(sizes, count); }
        name = (char *)sizes + count * 4;
        if (self->dir == 0) { self->dir = ((IgbExternalDir *)FUN_00309a50()); }
        if (self->dir != 0) {
            setPooled(&self->savedPath, self->dir->path);
            { char *n; n = self->name; dir = self->dir; setPooled(&dir->path, n); }
        }
        for (i = 0; i < count; i++) {
            ObjectList_AppendRetained((igObjectList *)self->list, (igObject *)(((int)FUN_00308fb0((W_308fb0 *)self->dir, (int)name))));
            name += sizes[i];
        }
        self->pool->release(self->buffer);
        self->buffer = 0;
        dir = self->dir;
        if (dir != 0) {
            setPooled(&dir->path, self->savedPath);
            setPooled(&self->savedPath, 0);
        }
    }
    return g_statusSucceeded;
}

static inline void addName(IgbNameList *l, const int &v) {
    int idx = l->count;
    if (l->cap > idx) { l->count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
    l->data[idx] = v;
}

igResult_2e3a10 FUN_002e91e0(IgbNameReader *self) {
    NameHeader hdr;
    char *buf;
    char *name;
    int i;
    if (self->stream->read(&hdr, 8, 1) != 1) { return g_allocatorFailureStatus; }
    if (self->swapped != 0) { self->swapper->swap(&hdr, 2); }
    buf = self->pool->alloc(hdr.size);
    if (buf == 0) { return g_allocatorFailureStatus; }
    if (self->stream->read(buf, hdr.size - 8, 1) != 1) { self->pool->release(buf); return g_allocatorFailureStatus; }
    if (self->names != 0) {
        self->names->count = 0;
    } else {
        IgbNameList *old = self->names;
        IgbPool *pool = self->pool;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->names = (IgbNameList *)igIntList_Create((int)pool);
    }
    name = buf;
    i = 0;
    while (hdr.count-- > 0) {
        addName(self->names, FUN_002f89e0((int)name));
        { int len = strlen(name) + 1; i++; name += len; }
    }
    for (; i < 46; i++) {
        int idx; IgbNameList *l; l = self->names; idx = l->count;
        if (l->cap > idx) { l->count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
        l->data[idx] = DAT_004c2140[0];
    }
    self->pool->release(buf);
    return g_statusSucceeded;
}

int FUN_002e9470(void *arg0) {
    FUN_002e8a40((T44 *)arg0);
    *(char *)((char *)(arg0) + 48) = 0;
    *(char *)((char *)(arg0) + 49) = 0;
    FUN_002e8a10(arg0);
    return -1;
}

igResult_2e3a10 FUN_002e94b0(O50 *arg1) {
    int i;
    int n;
    int flag;
    E50 *e;
    i = 0;
    n = arg1->n;
    flag = !arg1->f56;
    while (i < n) {
        e = (E50 *)FUN_002d7e90((int *)arg1, i);
        e->vX(flag);
        i += 1;
    }
    if (flag != 0) {
        arg1->f56 = 1;
    }
    return g_statusSucceeded;
}

igResult_2e3a10 FUN_002e9560(void *arg1) {
    int i;
    void **temp_v0;
    for (i = 0; i < *(int *)((char *)(arg1) + 8); i++) {
        temp_v0 = (void **)(FUN_002d7e90((int *)arg1, i));
        ((DW4VC_148_2e3a10 *)(temp_v0))->vX(arg1);
    }
    return g_statusSucceeded;
}

int igIGBFile_ReadFile(File *self, int path) {
  int startTime;
  sprintf(DAT_00586e20, DAT_004f9ad8, path);
  startTime = DAT_005871d8[0]->now();
  self->loaded = 0;
  self->loading = 1;
  self->f56 = 0;
  if (FUN_002e5f70((T24 *)self, path).failed()) return FUN_002e9470(self);
  if (igIGBFile_ReadHeader((S25 *)self).failed()) return FUN_002e9470(self);
  if (self->version < 5 && self->hasExternalRefs) {
    if (!GPR_00554c08) {
      int answer = FUN_00308320(DAT_004f9af0, self->device->name, self->device->name);
      if (answer != 1 && answer == 2) GPR_00554c08 = 1;
    }
    return FUN_002e9470(self);
  }
  if (self->version >= 3) {
    if (FUN_002e7f20((IgbMetaSection *)self).failed()) return FUN_002e9470(self);
    if (FUN_002e82a0((IgbTypeReader *)self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e6330((Q26 *)self).failed()) return FUN_002e9470(self);
  if (FUN_002e63e0(self).failed()) return FUN_002e9470(self);
  if (FUN_002e6f50((int *)self).failed()) return FUN_002e9470(self);
  if (self->version >= 5) {
    if (FUN_002e8e50((IgbExternalReader *)self).failed()) return FUN_002e9470(self);
  }
  if (self->f292) {
    if (FUN_002e91e0((IgbNameReader *)self).failed()) return FUN_002e9470(self);
  }
  if (self->f214) {
    if (igIGBFile_ReadObjectSection((IGBReader31 *)self).failed()) return FUN_002e9470(self);
    if (FUN_002e7640((IgbObjectSection *)self).failed()) return FUN_002e9470(self);
    if (FUN_002e78b0((O33 *)self).failed()) return FUN_002e9470(self);
  } else {
    if (igIGBFile_ReadObjectSectionOld((IGBReader34 *)self).failed()) return FUN_002e9470(self);
  }
  if (self->version >= 5) {
    if (FUN_002e8d40((A46 *)self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e8670((T41 *)self).failed()) return FUN_002e9470(self);
  if (self->readTail().failed()) return FUN_002e9470(self);
  if (self->version < 3) {
    if (FUN_002e7f20((IgbMetaSection *)self).failed()) return FUN_002e9470(self);
  }
  if (self->version < 5) {
    if (FUN_002e8d40((A46 *)self).failed()) return FUN_002e9470(self);
  }
  if (self->version < 5) {
    if (FUN_002e8e50((IgbExternalReader *)self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e8880((L42 *)self).failed()) return FUN_002e9470(self);
  if (FUN_002e7ed0((S37 *)self).failed()) return FUN_002e9470(self);
  FUN_002e94b0((O50 *)self);
  if (self->f277 == 1) {
    if (self->v30().failed()) return FUN_002e9470(self);
  }
  FUN_002e8a10(self);
  FUN_002e8a40((T44 *)self);
  self->loaded = 1;
  self->loading = 0;
  if (!GPR_00554c0c) {
    int answer = FUN_00308240(DAT_004f9b90, path, dpsub(DAT_005871d8[0]->now(), startTime));
    if (answer != 1 && answer == 2) GPR_00554c0c = 1;
  }
  return self->result;
}

void Gap__Core__igIGBFile__vfunc_32(int *arg0, void *arg1) {
    if (*(unsigned char *)((char *)(arg1) + 56) == 0) {
        FUN_002d8f20((Coll *)arg1);
    }
    *arg0 = g_statusSucceeded.v;
}

void Gap__Core__igIGBFile__vfunc_30(int *arg0, struct S54 *arg1) {
    if (arg1->f279 == 0) {
        igResult_2e3a10 sp3C = FUN_002e9560(arg1);
        if (arg1->f32 != 0) {
            FUN_0030a260((Z_30a260 *)arg1->f32, arg1->f20);
        }
        arg1->f279 = 1;
        *arg0 = sp3C.v;
    } else {
        *arg0 = g_statusSucceeded.v;
    }
}

static inline IgbInfoObject *castInfo(IgbInfoObject *o) { if (o != 0 && igObject_IsKindOf((void *)o, (igMetaObject *)(((int *)g_igIGBFile_metaObject)[0])) != 0) { return o; } return 0; }

igResult_2e3a10 Gap__Core__igIGBFile__vfunc_31(IgbFileInfoView *self) {
    igResult_2e3a10 result = g_statusSucceeded;
    int i;
    int fail;
    for (i = 0; i < self->list->count; i++) {
        Ref55 o(castInfo(self->list->data[i]));
        if (o.p != 0) {
            if (o.p->check().isFailed(fail)) {
                result.v = fail;
            }
        }
    }
    if (self->finish().isFailed(fail)) {
        result.v = fail;
    }
    return result;
}

int Gap__Core__igIGBFile__vfunc_34(IGB *o) {
    int i;
    o->f260 = o->f164;
    if (o->f260 < 0) {
        o->f260 = o->f104->f32;
    }
    if (o->f156 < o->f260) {
        o->f260 = o->f156;
    }
    o->f264 = o->f280->v220(o->f260, o->f104->f36);
    o->f256 = 0;
    o->f268 = 0;
    o->f272 = o->f260;
    for (i = 0; i < o->f8; i++) {
        ((VCb *)FUN_002d7e90((int *)o, i))->v164(o);
    }
    o->f280->v264(o->f264);
    o->f264 = 0;
    return 1;
}

igResult_2e3a10 igIGBFile_GetSectionBuffer(IgbSectionBufferOwner *arg1, int arg2) {
    int a1;
    a1 = arg1->f264;
    if (a1 != 0 && arg1->f260 >= arg2) {
        return g_statusSucceeded;
    } else {
        if (a1 != 0) {
            arg1->f280->vA(a1);
        }
        arg1->f260 = arg1->f164;
        if (arg1->f260 < 0) {
            arg1->f260 = arg1->f104->f28;
        }
        if (arg1->f260 < arg2) {
            arg1->f260 = arg2;
        }
        arg1->f260 = (arg1->f260 + 3) & ~3;
        arg1->f264 = arg1->f280->vB(arg1->f260, arg1->f104->f36);
        if (arg1->f264 == 0) {
            return g_allocatorFailureStatus;
        } else {
            return g_statusSucceeded;
        }
    }
}

void Gap__Core__igIGBFile__vfunc_33(int *arg0, S58 *arg1) {
    int n;
    int i;
    arg1->f100 = 0;
    arg1->f10c = 0;
    arg1->f110 = 0;
    n = arg1->cnt;
    for (i = 0; i < n; i++) {
        ((VC58 *)FUN_002d7e90((int *)arg1, i))->vX(arg1);
    }
    *arg0 = g_statusSucceeded.v;
}

