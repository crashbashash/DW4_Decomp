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
    sp5C = x;
    sp58 = ((igObject **)((igObjectList *)arg0->_subPropertyValues)->_data)[arg1];
    if (arg2 == 0) {
        v = 0;
    } else {
        if (g_stringPool[0] == 0) {
            int al = ((int)StringPool_Allocate(16));
            if (al != 0) al = ((int)StringPool_Construct((StringPool *)al));
            g_stringPool[0] = al;
        }
        v = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg2);
    }
    sp54 = v;
    idx = FUN_001cafc0(sp5C.p, &sp54, 0);
    releaseString((const char *)sp54);
    if (idx >= 0) {
        StringList_CopyRetained(&sp50, sp58.p, idx);
        r = sp50;
        releaseString((const char *)r);
        return r;
    }
    return 0;
}

static inline char *textOf(const igSmartPointer<igStringObj> &ref) {
    char *s = (char *)ref.get()->_buffer;
    s = (s == 0) ? g_stringObjEmptyText[0] : s;
    return s;
}

void FUN_002da010(void *self, igTDataList<igVisualContextView *> *list) {
    int i;
    igSmartPointer<igStringObj> text(((igStringObj *)igStringObj_Create((int)(((void *)igObject_GetAllocator((int)self))))));
    if (FUN_002dac30((void *)(text.get())) != 0) {
        FUN_002d96f0(self, 0, (int)(textOf(text)));
    }
    if (FUN_002dac60((void *)(text.get())) != 0) {
        FUN_002d96f0(self, 6, (int)(textOf(text)));
    }
    if (FUN_002dac90((void *)(text.get())) != 0) {
        FUN_002d96f0(self, 7, (int)(textOf(text)));
    }
    if (list == 0 || list->_count == 0) {
        return;
    }
    for (i = 0; i < list->_count; i++) {
        list->_data[i]->Describe(self);
    }
}

static inline int openPath(igDriverDatabase *database, const igSmartPointer<igStringObj> &path) {
    igFileView *file = (igFileView *)database->_databaseFile;
    int text = path.p->_buffer;
    if (text == 0) text = ((int *)g_stringObjEmptyText)[0];
    return file->Open((const char *)text, (const char *)&DAT_004f96a8[0]);
}

int FUN_002da1c0(igDriverDatabase *arg0, const char *arg1, const char *arg2) {
    int s0;
    igStringRef name((char *)arg1);
    const char *p5 = name.p;
    if (p5 == 0 || strlen(p5) == 0) {
        name = (char *)&text_drivers_ini[0];
    }
    {
        int al = ((int)igObject_GetAllocator((int)arg0));
        igRelease((igObject *)arg0->_databaseFile);
        arg0->_databaseFile = (int)((igObject *)igFile_Create(al));
    }
    s0 = ((igFileView *)arg0->_databaseFile)->Open(name.p, (const char *)&DAT_004f96a8[0]);
    if (s0 == 0) {
        if (arg2 == 0 || strlen(arg2) == 0) {
            arg2 = ((const char *)FUN_002d1c20((int *)(((int *)g_objectSystem)[0])));
        }
        if (arg2 != 0 && strlen(arg2) != 0) {
            igSmartPointer<igFolderView> folder((igFolderView *)FUN_002c43b0(((int)igObject_GetAllocator((int)arg0))));
            folder.p->setFolderName((char *)arg2);
            s0 = openPath(arg0, folder.p->vfunc_23(name.p));
        }
    }
    if (s0 == 0) {
        igSmartPointer<igFolderView> folder((igFolderView *)FUN_002c43b0(((int)igObject_GetAllocator((int)arg0))));
        folder.p->setFolderName((char *)FUN_002d1c30((int *)(((int *)g_objectSystem)[0])));
        s0 = openPath(arg0, folder.p->vfunc_23(name.p));
    }
    if (s0 == 0) {
        igRelease((igObject *)arg0->_databaseFile);
        arg0->_databaseFile = 0;
        return 0;
    }
    igStringObj_Set(arg0->_databaseFileName, *(int *)((char *)s0 + 12));
    FUN_002daac0(arg0, arg0->_databaseFile);
    ((igFileView *)arg0->_databaseFile)->Close();
    igRelease((igObject *)arg0->_databaseFile);
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
    return igStringObj_Clear((igStringObj *)(*(int *)((char *)p + 40)));
}

static inline int n_of(const igTDataList<ConfigNode *> *list) { return list->_count; }

igTDataList<ConfigNode *> *FUN_002da780(igDriverDatabase *s) {
    int cnt;
    int r;
    igTDataList<ConfigNode *> *l;
    int v;

    l = ((igTDataList<ConfigNode *> *)FUN_002c8450(((int)igObject_GetAllocator((int)s))));
    s->_currentLine = 1;
    v = ((igStringObj *)s->_rawDatabase)->_buffer;
    if (v == 0) {
        v = ((int *)g_stringObjEmptyText)[0];
    }
    s->_dbIndex = v;
    do {
        r = FUN_002dae40(s);
        if (r != 0) {
            cnt = l->_count;
            if (cnt < l->_capacity) {
                l->_count = n_of(l) + 1;
            } else {
                List_Resize(l, cnt + 1, 4);
            }
            l->_data[cnt] = (ConfigNode *)r;
        }
    } while (r != 0);
    return l;
}

static inline void clearSlot(igTDataList<ConfigNode *> *l, int i) {
    if (l->_count != 0 && i >= 0 && i < l->_count) {
        l->_data[i] = 0;
    }
}

void FUN_002da850(void *self, igTDataList<ConfigNode *> *list) {
    int i = 0;
    goto first;
next:
    if (list->_data[i] != 0) {
        list->_data[i]->Delete(1);
    }
    clearSlot(list, i);
    i++;
test:
    if (i < list->_count) {
        goto next;
    }
done:
    list->_refCount = (int)list->_refCount - 1;
    if (((unsigned long long)((long long)(int)list->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(list);
    }
    return;
first:
    if (0 < list->_count) {
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

int FUN_002da990(igDriverDatabase *arg0, int arg1, int arg2, int arg3) {
    int r;
    igTDataList<ConfigNode *> *a;
    int i;
    igSmartPointer<igRegistry> sp7C(((igRegistry *)FUN_002baff0(((int)igObject_GetAllocator((int)arg0)))));
    a = FUN_002da780(arg0);
    for (i = 0; i < a->_count; i++) {
        FUN_002db040((void *)arg0, (int)a->_data[i], (void *)sp7C.p, (void *)arg2);
    }
    FUN_003061c0((void *)arg1, sp7C.p, arg3);
    r = *(char *)arg0->_dbIndex == 0;
    FUN_002da850((void *)arg0, a);
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
        igStringObj_Insert((igStringObj *)s2, (char *)buf, s1, strlen(buf));
    }
}

int FUN_002dac30(void *arg0) {
    igStringObj_Set((int)arg0, (int)&text_psx2_2[0]);
    return 1;
}

int FUN_002dac60(void *arg0) {
    igStringObj_Set((int)arg0, (int)&text_mips[0]);
    return 1;
}

int FUN_002dac90(void *arg0) {
    igStringObj_Set((int)arg0, (int)&text_psx2_2[0]);
    return 1;
}

bool FUN_002dacc0(void *a0, igFileView *s, char *buf, int n) {
    int c = s->vfunc_33();
    int i = 0;
    while (c != -1 && c != 10 && c != 13 && c != 0) {
        if (i < n - 2) buf[i] = c;
        c = s->vfunc_33();
        i++;
    }
    if (n - 2 < i) i = n - 2;
    buf[i] = 10;
    buf[i+1] = 0;
    return i > 0 || ~c != 0;
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

bool FUN_002db540(igDriverDatabase *arg0, int *arg1) {
    char sp40[4096];
    bool var_s0;

    var_s0 = 0;
    FUN_002db480((int *)arg0);
    if (sscanf(arg0->_dbIndex, &text_abcdefghijklmnopqrstuvwxyzABCDEF[0], sp40) == 1) {
        arg0->_dbIndex = arg0->_dbIndex + strlen(sp40);
        *arg1 = ((int)igStringObj_Create(((int)igObject_GetAllocator((int)arg0))));
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
        *arg1 = ((int)igStringObj_Create(((int)igObject_GetAllocator((int)arg0))));
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

static inline void append(igTDataList<int> *l, int v) {
    int i = l->_count;
    if (i < l->_capacity) {
        l->_count = l->count() + 1;
    } else {
        List_Resize((void *)l, i + 1, 4);
    }
    l->_data[i] = v;
}

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
    *(int *)((char *)(arg0) + 0) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    *(int *)((char *)(arg0) + 4) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    return arg0;
}

ConfigPair *FUN_002dc1e0(ConfigPair *self, int delete_storage) {
    igStringObj *p;
    igStringObj *q;
    if (self) {
        *(int **)((char *)self + 8) = &DAT_00530608[0];
        p = self->key;
        --p->_refCount;
        if (((unsigned long long)(long long)(int)p->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)p);
        self->key = 0;
        q = self->value;
        --q->_refCount;
        if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)q);
        self->value = 0;
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
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList));
    }
    *(int *)((char *)(arg0) + 8) = ((int)FUN_002c8450(var_v0));
    *(int *)((char *)(arg0) + 12) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    return arg0;
}

void *FUN_002dc340(ConfigSettingsNode *arg0, long long arg1) {
    int var_s0;
    int s3;
    igObject *a0;
    igTDataList<ConfigPair *> *v1;
    int v0;
    ConfigPair *e;
    if (arg0 != 0) {
        arg0->vtable = (int)&DAT_005305f8[0];
        for (var_s0 = 0; var_s0 < arg0->entries->_count; var_s0++) {
            s3 = var_s0 * 4;
            e = arg0->entries->_data[var_s0];
            if (e != 0) {
                e->Delete(1);
            }
            v1 = arg0->entries;
            v0 = v1->_count;
            if (v0 != 0 && var_s0 >= 0 && var_s0 < v0) {
                *(int *)((char *)v1->_data + s3) = 0;
            }
        }
        a0 = (igObject *)arg0->entries;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->entries = 0;
        a0 = arg0->name;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->name = 0;
        if (arg0 != 0) {
            arg0->vtable = (int)&DAT_00530618[0];
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
    *(int *)((char *)(arg0) + 12) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    if (g_useOwnerAllocator != 0) {
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList));
    }
    *(int *)((char *)(arg0) + 16) = ((int)FUN_002c8450(var_v0));
    return arg0;
}

void *FUN_002dc530(ConfigSectionNode *arg0, long long arg1) {
    int var_s0;
    int s3;
    igObject *a0;
    igTDataList<ConfigNode *> *v1;
    int v0;
    ConfigNode *e;
    if (arg0 != 0) {
        arg0->vtable = (int)&DAT_005305e8[0];
        a0 = arg0->name;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->name = 0;
        a0 = arg0->selector;
        if (a0 != 0) {
            a0->_refCount = a0->_refCount - 1;
            if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
            arg0->selector = 0;
        }
        for (var_s0 = 0; var_s0 < arg0->children->_count; var_s0++) {
            s3 = var_s0 * 4;
            e = arg0->children->_data[var_s0];
            if (e != 0) {
                e->Delete(1);
            }
            v1 = arg0->children;
            v0 = v1->_count;
            if (v0 != 0 && var_s0 >= 0 && var_s0 < v0) {
                *(int *)((char *)v1->_data + s3) = 0;
            }
        }
        a0 = (igObject *)arg0->children;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->children = 0;
        if (arg0 != 0) {
            arg0->vtable = (int)&DAT_00530618[0];
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAliasB(arg0);
        }
    }
    return arg0;
}

