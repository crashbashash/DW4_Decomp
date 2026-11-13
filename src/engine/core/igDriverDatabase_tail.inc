static inline void setAt_2d9540(igDriverDatabase *database, int index, const PropertyRef &value) {
    igObject *retained = value.p;
    igObjectList *list = (igObjectList *)database->_currentProperties;
    if (retained != 0) {
        retained->_refCount++;
    }
    release(((igObject **)list->_data)[index]);
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((igObject **)list->_data)[index] = retained;
    }
}

void Gap__Core__igDriverDatabase__vfunc_12(int self) {
    FUN_002da770((int *)self);
    Gap__Core__igObject__vfunc_10(self);
}

void FUN_002d96f0(void *arg0, int arg1, int arg2) {
    igStringObj_Set(*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4)), arg2);
}

int FUN_002d9710(void *arg0, int arg1) {
    int var_v0;

    var_v0 = *(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4)))) + 8);
    if (var_v0 == 0) {
        var_v0 = ((int *)g_stringObjEmptyText)[0];
    }
    return var_v0;
}

int FUN_002d9cf0(igDriverDatabase *arg0, int arg1, int arg2) {
    igSmartPointer<igObject> sp5C;
    igSmartPointer<igObject> sp58;
    int sp54, sp50;
    igObject *x;
    int idx;
    int v;
    int r;
    sp5C.p = 0;
    sp58.p = 0;
    x = ((igObject **)((igObjectList *)arg0->_subPropertyNames)->_data)[arg1];
    if (x == 0) return 0;
    Util_2d9cf0::assign(sp5C, x);
    Util_2d9cf0::assign(sp58, ((igObject **)((igObjectList *)arg0->_subPropertyValues)->_data)[arg1]);
    if (arg2 == 0) {
        v = 0;
    } else {
        if (g_stringPool[0] == 0) {
            int al = ((int)StringPool_Allocate(16));
            if (al != 0) al = ((int)StringPool_Construct((struct S_2eadf0 *)al));
            g_stringPool[0] = al;
        }
        v = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg2);
    }
    sp54 = v;
    idx = FUN_001cafc0(sp5C.p, &sp54, 0);
    Util_2d9cf0::relstr(sp54);
    if (idx >= 0) {
        StringList_CopyRetained(&sp50, sp58.p, idx);
        r = sp50;
        Util_2d9cf0::relstr(r);
        return r;
    }
    return 0;
}

static inline char *textOf(const igSmartPointer<ConfigPlatformText> &ref) {
    char *s = ref.get()->text;
    s = (s == 0) ? g_stringObjEmptyText[0] : s;
    return s;
}

void FUN_002da010(void *self, ConfigPlatformSourceList *list) {
    int i;
    igSmartPointer<ConfigPlatformText> text(((ConfigPlatformText *)FUN_002b9500((int)(((void *)igObject_GetAllocator((int)self))))));
    if (FUN_002dac30((void *)(text.get())) != 0) {
        FUN_002d96f0(self, 0, (int)(textOf(text)));
    }
    if (FUN_002dac60((void *)(text.get())) != 0) {
        FUN_002d96f0(self, 6, (int)(textOf(text)));
    }
    if (FUN_002dac90((void *)(text.get())) != 0) {
        FUN_002d96f0(self, 7, (int)(textOf(text)));
    }
    if (list == 0 || list->count == 0) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        list->data[i]->Describe(self);
    }
}

static inline int openPath(igDriverDatabase *database, const Mem &path) {
    O100 *file = (O100 *)database->_databaseFile;
    int text = path.p->f8;
    if (text == 0) text = ((int *)g_stringObjEmptyText)[0];
    return file->vX((const char *)text, &DAT_004f96a8[0]);
}

int FUN_002da1c0(igDriverDatabase *arg0, const char *arg1, const char *arg2) {
    int s0;
    const char *tok;
    if (arg1 == 0) {
        tok = 0;
    } else {
        POOL()
        tok = ((const char *)StringPool_Intern((StringPool *)(((void * *)g_stringPool)[0]), arg1));
    }
    StringRef name(tok);
    const char *p5 = name.p;
    if (p5 == 0 || strlen(p5) == 0) {
        POOL()
        tok = ((const char *)StringPool_Intern((StringPool *)(((void * *)g_stringPool)[0]), (const char *)&DAT_004f9698[0]));
        releaseString(name.p);
        name.p = tok;
    }
    {
        int al = ((int)igObject_GetAllocator((int)arg0));
        release_2da1c0((T *)arg0->_databaseFile);
        arg0->_databaseFile = (int)((T *)igFile_Create(al));
    }
    s0 = ((O100 *)arg0->_databaseFile)->vX(name.p, &DAT_004f96a8[0]);
    if (s0 == 0) {
        if (arg2 == 0 || strlen(arg2) == 0) {
            arg2 = ((const char *)FUN_002d1c20((int *)(((int *)g_objectSystem)[0])));
        }
        if (arg2 != 0 && strlen(arg2) != 0) {
            BLOCK(FUN_002c43b0, arg2)
        }
    }
    if (s0 == 0) {
        BLOCK(FUN_002c43b0, ((const char *)FUN_002d1c30((int *)(((int *)g_objectSystem)[0]))))
    }
    if (s0 == 0) {
        release_2da1c0((T *)arg0->_databaseFile);
        arg0->_databaseFile = 0;
        return 0;
    }
    igStringObj_Set(arg0->_databaseFileName, *(int *)((char *)s0 + 12));
    FUN_002daac0((S_2daac0 *)arg0, arg0->_databaseFile);
    ((O104 *)arg0->_databaseFile)->vX();
    release_2da1c0((T *)arg0->_databaseFile);
    arg0->_databaseFile = 0;
    return 1;
}

int FUN_002da710(void *arg0, int arg1, int arg2) {
    if (arg1 == 0) {
        return 0;
    }
    igStringObj_Set(*(int *)((char *)arg0 + 36), arg2);
    FUN_002dab80(arg0, arg1);
    return 1;
}

int FUN_002da770(int *p)
{
    return igStringObj_Clear((S0_30b420 *)(*(int *)((char *)p + 40)));
}

static inline int n_of(const struct L_2da780 *list) { return list->n; }

struct L_2da780 *FUN_002da780(struct S_2da780 *s) {
    int cnt;
    int r;
    struct L_2da780 *l;
    int v;

    l = ((struct L_2da780 *)FUN_002c8450(((int)igObject_GetAllocator((int)s))));
    s->f44 = 1;
    v = s->src->c;
    if (v == 0) {
        v = ((int *)g_stringObjEmptyText)[0];
    }
    s->f52 = v;
    do {
        r = FUN_002dae40(s);
        if (r != 0) {
            cnt = l->n;
            if (cnt < l->cap) {
                l->n = n_of(l) + 1;
            } else {
                List_Resize(l, cnt + 1, 4);
            }
            l->arr[cnt] = r;
        }
    } while (r != 0);
    return l;
}

static inline void clearSlot(TrackedEntryList *l, int i) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = 0;
    }
}

void FUN_002da850(void *self, TrackedEntryList *list) {
    int i = 0;
    goto first;
next:
    if (list->data[i] != 0) {
        list->data[i]->Delete(1);
    }
    clearSlot(list, i);
    i++;
test:
    if (i < list->count) {
        goto next;
    }
done:
    list->_refCount = (int)list->_refCount - 1;
    if (((unsigned long long)((long long)(int)list->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(list);
    }
    return;
first:
    if (0 < list->count) {
        goto test;
    }
    goto done;
}

void *FUN_002da940(void *arg0, long long arg1) {
    if (arg0 != 0) {
        *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasB((void *)arg0);
        }
    }
    return arg0;
}

int FUN_002da990(Owner_2da990 *arg0, int arg1, int arg2, int arg3) {
    int r;
    Arr_2da990 *a;
    int i;
    igSmartPointer<Obj_2da990> sp7C(((Obj_2da990 *)FUN_002baff0(((int)igObject_GetAllocator((int)arg0)))));
    a = ((Arr_2da990 *)FUN_002da780((struct S_2da780 *)arg0));
    for (i = 0; i < a->count; i++) {
        FUN_002db040((void *)arg0, a->items[i], (void *)sp7C.p, (void *)arg2);
    }
    FUN_003061c0((void *)arg1, (IniIncludeView *)sp7C.p, arg3);
    r = *arg0->p52 == 0;
    FUN_002da850((void *)arg0, (TrackedEntryList *)a);
    FUN_002da770((int *)arg0);
    return r;
}

int FUN_002daab0(void)
{
    return 1;
}

void FUN_002dab80(void *arg0, int arg1) {
    char buf[4096];
    char *s2;
    int s1;
    char *p;
    int c;
    FUN_002da770((int *)arg0);
    while (FUN_002dada0(arg0, (char **)&arg1, (char *)buf, 0x1000) != 0) {
        p = buf;
        while ((c = *p) != 0) {
            if (c == 0x3B) {
                *p = 0xA;
                p[1] = 0;
                break;
            }
            p++;
        }
        s2 = (char *)(*(int *)((char *)(arg0) + 40));
        s1 = *(int *)(s2 + 12);
        igStringObj_Insert((IniStringView *)s2, (char *)buf, s1, strlen(buf));
    }
}

int FUN_002dac30(void *arg0) {
    igStringObj_Set((int)arg0, (int)&DAT_004f96b0[0]);
    return 1;
}

int FUN_002dac60(void *arg0) {
    igStringObj_Set((int)arg0, (int)&DAT_004f96b8[0]);
    return 1;
}

int FUN_002dac90(void *arg0) {
    igStringObj_Set((int)arg0, (int)&DAT_004f96b0[0]);
    return 1;
}

bool FUN_002dacc0(void *a0, S_2dacc0 *s, char *buf, int n) {
    int c = s->vX();
    int i = 0;
    while (c != -1 && c != 10 && c != 13 && c != 0) {
        if (i < n - 2) buf[i] = c;
        c = s->vX();
        i++;
    }
    if (n - 2 < i) i = n - 2;
    buf[i] = 10;
    buf[i+1] = 0;
    return i > 0 || ~c != 0;
}

static inline char *text(KeyValueText *s) {
    char *t = s->text;
    if (t == 0) {
        t = g_stringObjEmptyText[0];
    }
    return t;
}

static inline void releaseValue(ConfigValueToken *t) {
    if (t != 0) {
        t->_refCount = (int)t->_refCount - 1;
        if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)t);
        }
    }
}

static inline char *textOf_2db2f0(ConfigValueToken *t) {
    char *s = t->text;
    s = (s == 0) ? g_stringObjEmptyText[0] : s;
    return s;
}

void FUN_002db480(int *arg0) {
    char c;
    while (_ctype_[(c = *(char *)arg0[13]) + 1] & 8) {
        if (c == 10) {
            arg0[11] = arg0[11] + 1;
        }
        arg0[13] = arg0[13] + 1;
    }
}

void FUN_002db4e0(int arg0, char *arg1) {
    int i;

    i = strlen(arg1) - 1;
    while (i >= 0 && (_ctype_[arg1[i] + 1] & 8)) {
        arg1[i] = 0;
        i--;
    }
}

bool FUN_002db540(S_2db540 *arg0, int *arg1) {
    char sp40[4096];
    bool var_s0;

    var_s0 = 0;
    FUN_002db480((int *)arg0);
    if (sscanf(arg0->f52, &DAT_004f96d0[0], sp40) == 1) {
        arg0->f52 = arg0->f52 + strlen(sp40);
        *arg1 = ((int)FUN_002b9500(((int)igObject_GetAllocator((int)arg0))));
        igStringObj_Set(*arg1, (int)sp40);
        var_s0 = 1;
    }
    return var_s0;
}

bool FUN_002db5e0(char *arg0, int *arg1) {
    char buf[4096];
    bool var_s0;

    var_s0 = false;
    FUN_002db480((int *)arg0);
    if (sscanf(*(int *)(arg0 + 52), &DAT_004f9718[0], buf) == 1) {
        *(int *)(arg0 + 52) = *(int *)(arg0 + 52) + strlen(buf);
        FUN_002db4e0((int)arg0, (char *)buf);
        *arg1 = ((int)FUN_002b9500(((int)igObject_GetAllocator((int)arg0))));
        igStringObj_Set(*arg1, (int)buf);
        var_s0 = true;
    }
    return var_s0;
}

bool FUN_002db690(char *arg0, int *arg1) {
    char buf[4096];
    bool var_s1;
    int var_s0;

    var_s1 = false;
    FUN_002db480((int *)arg0);
    if (sscanf(*(int *)(arg0 + 52), &DAT_004f9728[0], buf) == 1) {
        *(int *)(arg0 + 52) = *(int *)(arg0 + 52) + strlen(buf);
        for (var_s0 = 0; var_s0 < 3; var_s0++) {
            if (strcmp(buf, DAT_004f9670[var_s0]) == 0) {
                *arg1 = var_s0;
                var_s1 = true;
                break;
            }
        }
    }
    return var_s1;
}

static inline void storeToken(int table, ConfigToken *n) {
    char *text = n->text;
    int kind = n->kind;
    int t = table;
    text = (text == 0) ? g_stringObjEmptyText[0] : text;
    FUN_0030b320((struct S_30b320 *)t, (int)text, kind);
}

static inline void releaseToken(ConfigToken *n) {
    n->_refCount = (int)n->_refCount - 1;
    if (((unsigned long long)((long long)(int)n->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy((void *)n);
    }
}

static inline void append(ConfigChildList *l, int v) {
    int i = l->count;
    if (i < l->capacity) {
        l->count = l->getCount() + 1;
    } else {
        List_Resize((void *)l, i + 1, 4);
    }
    l->data[i] = v;
}

static inline char *textOf_2dba50(ConfigToken *n) { char *t = n->text; return (t == 0) ? g_stringObjEmptyText[0] : t; }

int FUN_002dbca0(int arg0, int arg1) {
    switch (arg1) {
    case 8:
    case 10:
        return 1;
    case 11:
        return 2;
    case 12:
        return 3;
    case 9:
    default:
        return 0;
    }
}

int FUN_002dbfb0(int dummy0, int arg1, int arg2, int arg3) {
    switch (arg2) {
    case 0:
        return strcasecmp(arg1, arg3) == 0;
    case 1:
        return strncasecmp(arg1, arg3, strlen(arg3)) == 0;
    case 2:
        return strcasecmp(arg1, arg3) != 0;
    default:
        return 0;
    }
}

int FUN_002dc050(int dummy0, int arg1, int arg2, int arg3) {
    switch (arg2) {
    case 0:
        return arg1 == arg3;
    case 1:
        return arg1 >= arg3;
    case 2:
        return arg1 != arg3;
    default:
        return 0;
    }
}

int FUN_002dc120(int p, unsigned char a, int m, unsigned char b) { switch (m) { case 0: return a == b; case 1: goto z; case 2: return a != b; } z: return 0; }

void *FUN_002dc180(void *arg0) {
    *(int *)((char *)(arg0) + 8) = (int)(&DAT_00530608[0]);
    *(int *)((char *)(arg0) + 0) = ((int)FUN_002b9500(((int)Memory_GetAllocatorBySelector(DAT_00587048[0]))));
    *(int *)((char *)(arg0) + 4) = ((int)FUN_002b9500(((int)Memory_GetAllocatorBySelector(DAT_00587048[0]))));
    return arg0;
}

O_2dc1e0 *FUN_002dc1e0(O_2dc1e0 *self, int delete_storage) {
    T_2dc1e0 *p;
    T_2dc1e0 *q;
    if (self) {
        self->vt = &DAT_00530608[0];
        p = self->a;
        --p->references;
        if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0)
            igObject_Destroy((void *)p);
        self->a = 0;
        q = self->b;
        --q->references;
        if (((unsigned long long)(long long)q->references & 0x7fffffULL) == 0)
            igObject_Destroy((void *)q);
        self->b = 0;
        if ((short)delete_storage > 0) Memory_FreeBufferAliasB(self);
    }
    return self;
}

void *FUN_002dc2a0(void *arg0) {
    int var_v0;

    *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
    *(int *)((char *)(arg0) + 0) = 1;
    *(int *)((char *)(arg0) + 4) = (int)(&DAT_005305f8[0]);
    if (g_useOwnerAllocator != 0) {
        var_v0 = ((int)Memory_GetAllocatorBySelector(DAT_00587028[0]));
    } else {
        var_v0 = ((int)Memory_GetAllocatorBySelector(DAT_00587058[0]));
    }
    *(int *)((char *)(arg0) + 8) = ((int)FUN_002c8450(var_v0));
    *(int *)((char *)(arg0) + 12) = ((int)FUN_002b9500(((int)Memory_GetAllocatorBySelector(DAT_00587048[0]))));
    return arg0;
}

void *FUN_002dc340(S_2dc340 *arg0, long long arg1) {
    int var_s0;
    int s3;
    RO *a0;
    RO *v1;
    int v0;
    E_2dc340 *e;
    if (arg0 != 0) {
        arg0->vt = (int)&DAT_005305f8[0];
        for (var_s0 = 0; var_s0 < arg0->l->count; var_s0++) {
            s3 = var_s0 * 4;
            e = arg0->l->data[var_s0];
            if (e != 0) {
                e->d0(1);
            }
            v1 = arg0->l;
            v0 = v1->count;
            if (v0 != 0 && var_s0 >= 0 && var_s0 < v0) {
                *(int *)((char *)v1->data + s3) = 0;
            }
        }
        a0 = arg0->l;
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) igObject_Destroy(a0);
        arg0->l = 0;
        a0 = arg0->r;
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) igObject_Destroy(a0);
        arg0->r = 0;
        if (arg0 != 0) {
            arg0->vt = (int)&DAT_00530618[0];
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAliasB(arg0);
        }
    }
    return arg0;
}

void *FUN_002dc490(void *arg0, int arg1) {
    int var_v0;

    *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
    *(int *)((char *)(arg0) + 0) = 0;
    *(int *)((char *)(arg0) + 4) = (int)(&DAT_005305e8[0]);
    *(int *)((char *)(arg0) + 8) = arg1;
    *(int *)((char *)(arg0) + 20) = 0;
    *(int *)((char *)(arg0) + 24) = 0;
    *(int *)((char *)(arg0) + 12) = ((int)FUN_002b9500(((int)Memory_GetAllocatorBySelector(DAT_00587048[0]))));
    if (g_useOwnerAllocator != 0) {
        var_v0 = ((int)Memory_GetAllocatorBySelector(DAT_00587028[0]));
    } else {
        var_v0 = ((int)Memory_GetAllocatorBySelector(DAT_00587058[0]));
    }
    *(int *)((char *)(arg0) + 16) = ((int)FUN_002c8450(var_v0));
    return arg0;
}

void *FUN_002dc530(S_2dc530 *arg0, long long arg1) {
    int var_s0;
    int s3;
    RO_2dc530 *a0;
    RO_2dc530 *v1;
    int v0;
    E_2dc530 *e;
    if (arg0 != 0) {
        arg0->vt = (int)&DAT_005305e8[0];
        a0 = arg0->a;
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) igObject_Destroy(a0);
        arg0->a = 0;
        a0 = arg0->b;
        if (a0 != 0) {
            a0->u.w = a0->u.w - 1;
            if (a0->u.b.cnt == 0) igObject_Destroy(a0);
            arg0->b = 0;
        }
        for (var_s0 = 0; var_s0 < arg0->l->count; var_s0++) {
            s3 = var_s0 * 4;
            e = arg0->l->data[var_s0];
            if (e != 0) {
                e->d0(1);
            }
            v1 = arg0->l;
            v0 = v1->count;
            if (v0 != 0 && var_s0 >= 0 && var_s0 < v0) {
                *(int *)((char *)v1->data + s3) = 0;
            }
        }
        a0 = arg0->l;
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) igObject_Destroy(a0);
        arg0->l = 0;
        if (arg0 != 0) {
            arg0->vt = (int)&DAT_00530618[0];
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAliasB(arg0);
        }
    }
    return arg0;
}

