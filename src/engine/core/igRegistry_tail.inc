void Gap__Core__igRegistry__vfunc_11(void *arg0) {
    Gap__Core__igObject__vfunc_09((int)arg0);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)(*(int *)((char *)arg0 + 8)), 0x100);
}

static inline int pool_305d30() {
    if ((*(int *)g_stringPool) == 0) {
        int p = ((int)StringPool_Allocate(0x10));
        if (p != 0) { p = ((int)StringPool_Construct((StringPool *)p)); }
        (*(int *)g_stringPool) = p;
    }
    return (*(int *)g_stringPool);
}

static inline void assign_305d30(char **slot, char *text) {
    char *v = ((char *)StringPool_Intern((StringPool *)(pool_305d30()), (const char *)text));
    char *old = *slot;
    dropString(old);
    *slot = v;
}

static inline void setText(igFolderView *o, char *text) {
    char *v = ((char *)StringPool_Intern((StringPool *)(pool_305d30()), (const char *)text));
    char *old = o->_folderName;
    dropString(old);
    o->_folderName = v;
}

static inline void dropPath(igFolderView *o) {
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

static inline char *pathText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return (*(char * *)g_stringObjEmptyText); } return t; }

static inline int tryPath(igRegistry *self, igFolderView *base, char *name) {
    FolderPath joined = base->vfunc_23(name);
    igFileView *file = (igFileView *)self->_registryFile;
    return file->Open(pathText(joined.p), ((char *)DAT_004f96a8));
}

bool FUN_00305d30(igRegistry *self, char *name, char *dir) {
    char *held;
    char *interned;
    int found;
    igFolderView *base;
    igFolderView *other;
    char *second;
    if (name == 0) {
        interned = 0;
    } else {
        interned = ((char *)StringPool_Intern((StringPool *)(pool_305d30()), (const char *)name));
    }
    *(char **)&held = interned;
    if (held == 0 || strlen(held) == 0) {
        assign_305d30(&held, text_alchemy_ini);
    }
    found = ((igFileView *)self->_registryFile)->Open(held, ((char *)DAT_004f96a8));
    if (found == 0) {
        if (dir == 0 || strlen(dir) == 0) {
            dir = ((char *)FUN_002d1c20((int *)((*(void * *)g_objectSystem))));
        }
        if (dir != 0 && strlen(dir) != 0) {
            *(igFolderView **)&base = ((igFolderView *)FUN_002c43b0(((int)igObject_GetAllocator((int)self))));
            setText(base, dir);
            found = tryPath(self, base, held);
            dropPath(base);
        }
    }
    if (found == 0) {
        *(igFolderView **)&other = ((igFolderView *)FUN_002c43b0(((int)igObject_GetAllocator((int)self))));
        second = ((char *)FUN_002d1c30((int *)((*(void * *)g_objectSystem))));
        setText(other, second);
        found = tryPath(self, other, held);
        dropPath(other);
    }
    if (found == 0) {
        dropString(held);
        return false;
    }
    FUN_003077a0(self);
    FUN_00307870(self, self->_registryFile, 1);
    ((igFileView *)self->_registryFile)->Close();
    dropString(held);
    return true;
}

static inline char *textOf_3061c0(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText[0]; } return t; }

int FUN_003061c0(void *self, igRegistry *inc, int overwrite) {
    int i = 0;
    igSmartPointer<igRegistryValue> cur;
    for (; i < ((igTDataList<igRegistryValue *> *)inc->_valueTable)->_count; i++) {
        cur = ((igTDataList<igRegistryValue *> *)inc->_valueTable)->_data[i];
        if (cur.p != 0) {
            int section = FUN_00306360((igRegistry *)self, (char *)(FUN_00307f80(inc, cur.p->_section)), 1);
            if (overwrite == 0 && ((int)FUN_00307c10((igRegistry *)self, section, textOf_3061c0((igStringObj *)cur.p->_valueName), 0)) != 0) {
                continue;
            }
            igStringObj *value = (igStringObj *)cur.p->_value;
            igStringObj *key = (igStringObj *)cur.p->_valueName;
            FUN_00307700(self, section, textOf_3061c0(key), (int)(textOf_3061c0(value)));
        }
    }
    return 1;
}

typedef igSmartPointer<igTDataList<igRegistryValue *> > IniPairListRef;

/* The number of keys a section holds. */
int FUN_003064b0(int registry, int section) {
    int keys = 0;
    for (int i = 0; i < ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->count(); i++) {
        igRegistryValue *entry = ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->get(i);
        if (entry != 0 && entry->_section == section) {
            keys++;
        }
    }
    return keys;
}

/* Copies the index-th key of a section to *key, retained; false when the section has fewer keys. */
bool igRegistry_GetKeyName(int registry, int section, int index, igStringObj **key) {
    int i;
    int seen = 0;
    bool found = false;
    for (i = 0; i < ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->count(); i++) {
        igRegistryValue *entry = ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->get(i);
        if (entry != 0 && entry->_section == section) {
            if (seen == index) {
                *(igSmartPointer<igStringObj> *)key = (igStringObj *)entry->_valueName;
                found = true;
                break;
            }
            seen++;
        }
    }
    return found;
}

bool FUN_003065f0(int arg0, int arg1, const char *arg2, int *arg3, int arg4, int arg5) {
    bool var_s0;
    void *temp_v0;

    var_s0 = false;
    temp_v0 = ((void *)FUN_00307c10((igRegistry *)arg0, arg1, arg2, 0));
    if ((temp_v0 != 0) && (igStringObj_ToInt((void *)(*(int *)((char *)(temp_v0) + 12)), (int)arg3) != 0)) {
        var_s0 = true;
    }
    if (!var_s0) {
        *arg3 = arg4;
        if (arg5 != 0) {
            FUN_00307660((void *)arg0, arg1, arg2, arg4);
        }
    }
    return var_s0;
}

bool FUN_003066b0(int arg0, int arg1, const char *arg2, float *arg3, int arg4, float fparg0) {
    bool var_s0;
    void *temp_v0;

    var_s0 = false;
    temp_v0 = (void *)(((void *)FUN_00307c10((igRegistry *)arg0, arg1, arg2, 0)));
    if ((temp_v0 != 0) && (igStringObj_ToFloat((void *)(*(int *)((char *)(temp_v0) + 12)), (int)arg3) != 0)) {
        var_s0 = true;
    }
    if (!var_s0) {
        *arg3 = fparg0;
        if (arg4 != 0) {
            FUN_003076b0(arg0, arg1, arg2, fparg0);
        }
    }
    return var_s0;
}

int FUN_00306770(int arg0, int arg1, const char *arg2, igStringObj **arg3, const char *arg4, int arg5) {
    igRegistryValue *node;
    igStringObj *t;
    igStringObj *old;
    StringObjHolder h;
    node = FUN_00307c10((igRegistry *)arg0, arg1, arg2, 0);
    if (node != 0) {
        t = (igStringObj *)node->_value;
        if (t) {
            ++t->_refCount;
        }
        old = *arg3;
        if (old) {
            --old->_refCount;
            if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)old);
        }
        *arg3 = t;
    } else {
    h.ref = ((igStringObj *)igStringObj_Create(((int)igObject_GetAllocator(arg0))));
    igStringObj_Set((int)h.ref, (int)arg4);
    t = h.ref;
    if (t) {
        ++t->_refCount;
    }
    old = *arg3;
    if (old) {
        --old->_refCount;
        if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)old);
    }
    *arg3 = t;
    if (arg5 != 0) {
        FUN_00307700((void *)arg0, arg1, arg2, (int)arg4);
    }
    h.release();
    }
    return node != 0;
}

static inline int pool_306910(void) {
    int p;
    if (g_stringPool[0] == 0) {
        p = ((int)StringPool_Allocate(0x10));
        if (p != 0) {
            p = ((int)StringPool_Construct((StringPool *)p));
        }
        g_stringPool[0] = p;
    }
    return g_stringPool[0];
}

static inline char *text_306910(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText[0]; } return t; }

static inline void assign_306910(int **slot, char *s) {
    int *v = ((int *)StringPool_Intern((StringPool *)(pool_306910()), (const char *)s));
    int *old = *slot;
    int *hd;
    int rc;
    if (old != 0) {
        hd = old - 2;
        rc = old[-1] - 1;
        old[-1] = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd), (int)hd);
        }
    }
    *slot = v;
}

int FUN_00306910(int arg0, int arg1, const char *arg2, int **out, char *def, int create) {
    igRegistryValue *p;

    p = FUN_00307c10((igRegistry *)arg0, arg1, arg2, 0);
    if (p != 0) {
        assign_306910(out, text_306910((igStringObj *)p->_value));
    } else {
        assign_306910(out, def);
        if (create != 0) {
            FUN_00307700((void *)arg0, arg1, arg2, (int)def);
        }
    }
    return p != 0;
}

static inline int pool_306aa0(void) {
    int p;
    if (g_stringPool[0] == 0) {
        p = ((int)StringPool_Allocate(0x10));
        if (p != 0) {
            p = ((int)StringPool_Construct((StringPool *)p));
        }
        g_stringPool[0] = p;
    }
    return g_stringPool[0];
}

static inline char *text_306aa0(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText[0]; } return t; }

static inline int *intern(char *s) {
    if (s == 0) {
        return 0;
    }
    return ((int *)StringPool_Intern((StringPool *)(pool_306aa0()), (const char *)s));
}

static inline void releaseRef(int *old) {
    int *hd;
    int rc;
    if (old != 0) {
        hd = old - 2;
        rc = old[-1] - 1;
        old[-1] = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd), (int)hd);
        }
    }
}

static inline void setAt_306aa0(igStringRefList *l, int i, int **v) {
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) {
        int **slot = &((int **)l->_data)[i];
        int *w = *v;
        if (w != 0) {
            w[-1] = w[-1] + 1;
        }
        releaseRef(*slot);
        *slot = *v;
    }
}

int FUN_00306aa0(void *self, int section, const char *key, igStringRefList *list, int create) {
    igStringObj *a;
    igStringObj *b;
    int *r1;
    int *tmp;
    int *r2;
    int *r3;
    const char *saved;
    int i; igRegistryValue *p; int n; int j; igStringObj *c; char *s2; igStringObj *held; igStringObj *c2; int at; int at2;

    saved = key;
    p = FUN_00307c10((igRegistry *)self, section, key, 0);
    if (p != 0) {
        FUN_0030bce0((igStringObj *)p->_value, 0x2C, (igTDataList<char *> *)list);
        *(igStringObj **)&a = (igStringObj *)(igStringObj_Create(((int)igObject_GetAllocator((int)self))));
        for (i = 0; i < list->_count; i++) {
            StringList_CopyRetained(&r1, list, i);
            igStringObj_Set((int)a, (int)r1);
            releaseRef(r1);
            FUN_0030bee0(a);
            *(int **)&tmp = intern(text_306aa0(a));
            setAt_306aa0(list, i, &tmp);
            releaseRef(tmp);
        }
        held = a;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    } else if (create != 0) {
        *(igStringObj **)&b = (igStringObj *)(igStringObj_Create(((int)igObject_GetAllocator((int)self))));
        n = list->_count;
        if (n != 0) {
            StringList_CopyRetained(&r2, list, 0);
            igStringObj_Set((int)b, (int)r2);
            releaseRef(r2);
        }
        for (j = 1; j < n; j++) {
            c = b; at = c->_length;
            igStringObj_Insert(c, (char *)DAT_004fb190, at, strlen(DAT_004fb190));
            StringList_CopyRetained(&r3, list, j);
            c2 = b; s2 = (char *)r3; at2 = c2->_length; igStringObj_Insert(c2, s2, at2, strlen(s2));
            releaseRef(r3);
        }
        FUN_00307700(self, section, saved, (int)(text_306aa0(b)));
        held = b;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
    return p != 0;
}

static inline bool sameChar(int a, int b) { return (char)a == (char)b; }

static inline int isSpaceChar(char c) { return _ctype_[c + 1] & 8; }

static inline int pool_307470(void *o) { int a = *(int *)((char *)(*(int *)((char *)(o) + 12)) + 8); if (a == 0) { return ((int *)g_stringObjEmptyText)[0]; } return a; }

int FUN_00307470(int arg0, int arg1, const char *arg2, int arg3, int *arg4, int arg5, int arg6) {
    void *temp_v0;
    temp_v0 = (void *)(((void *)FUN_00307c10((igRegistry *)arg0, arg1, arg2, 0)));
    if (temp_v0 != 0) {
        FUN_00307200((char *)(pool_307470(temp_v0)), (int)arg4, (void *)arg3, (char *)&DAT_004f95a0[0]);
    } else {
        *arg4 = arg5;
        if (arg6 != 0) {
            FUN_00307660((void *)arg0, arg1, arg2, arg5);
        }
    }
    return temp_v0 != 0;
}

static inline int pool_307550(void *o) { int a = *(int *)((char *)(*(int *)((char *)(o) + 12)) + 8); if (a == 0) { return ((int *)g_stringObjEmptyText)[0]; } return a; }

int FUN_00307550(int arg0, int arg1, const char *arg2, int arg3, int *arg4, int arg5, int arg6) {
    void *temp_v0;
    temp_v0 = (void *)(((void *)FUN_00307c10((igRegistry *)arg0, arg1, arg2, 0)));
    if (temp_v0 != 0) {
        FUN_00306f10((char *)(pool_307550(temp_v0)), arg4, arg3, (char *)&DAT_004f95a0[0]);
    } else {
        *arg4 = arg5;
        if (arg6 != 0) {
            FUN_00307660((void *)arg0, arg1, arg2, arg5);
        }
    }
    return temp_v0 != 0;
}

int FUN_00307630(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4));
}

int FUN_00307650(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8);
}

int FUN_00307660(void *arg0, int arg1, const char *arg2, int arg3) {
    void *temp_v0;
    temp_v0 = (void *)((void *)FUN_00307c10((igRegistry *)arg0, arg1, arg2, 1));
    if (temp_v0 == 0) return 0;
    FUN_0030b720(*(int *)((char *)(temp_v0) + 12), arg3, (int)&DAT_004f95c0[0]);
    return 1;
}

int FUN_003076b0(int a0, int a1, const char *a2, float x) {
    igRegistryValue *o = FUN_00307c10((igRegistry *)a0, a1, a2, 1);
    if (o == 0) {
        return 0;
    }
    FUN_0030b730(o->_value, (void *)((int)(((char *)DAT_004f9a70))), x);
    return 1;
}

int FUN_00307700(void *arg0, int arg1, const char *arg2, int arg3) {
    void *temp_v0;
    temp_v0 = (void *)((void *)FUN_00307c10((igRegistry *)arg0, arg1, arg2, 1));
    if (temp_v0 == 0) return 0;
    igStringObj_Set(*(int *)((char *)(temp_v0) + 12), arg3);
    return 1;
}

int FUN_00307750(int arg0, int arg1, const char *arg2, int arg3) {
    void *temp_v0;

    temp_v0 = (void *)(((void *)FUN_00307c10((igRegistry *)arg0, arg1, arg2, 1)));
    if (temp_v0 == 0) {
        return 0;
    }
    FUN_0030b770(*(int *)((char *)(temp_v0) + 12), arg3, 0);
    return 1;
}

void FUN_003077a0(igRegistry *self) {
    int n2;
    int j;
    igTDataList<igObject *> *l;
    int n1;
    int i;
    igObject *p;

    l = (igTDataList<igObject *> *)self->_additionalSectionNames;
    n1 = l->_count;
    for (i = 0; i < n1; i++) {
        p = l->_data[i];
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        l->_data[j] = 0;
    }
    l->_count = 0;
    ObjectList_ClearRetainedPreserveCount((igTDataList<igObject *> *)self->_valueTable, n2);
}

bool FUN_00307a50(void *unused, igFileView *s, char *buf, int *lines) {
    int c = s->vfunc_33();
    int prev = 0;
    bool comment = false;
    int n = 0;
    bool ret = false;
    bool lead = true;
    while (c != -1 && c != 0) {
        while (lead) {
            if (c == 0x20 || c == 9) { prev = c; c = s->vfunc_33(); }
            else lead = false;
        }
        if (c == 13) { c = s->vfunc_33(); continue; }
        if (c != 10) {
            if (!comment) {
                if (c == 0x3B) comment = true;
                else if (c == 0x2F && prev == 0x2F) { n -= 1; comment = true; }
                else {
                    if (n < 0xFFF) buf[n] = c;
                    n += 1;
                }
            }
            goto next;
        }
        if (prev != 0x5C) break;
        lead = true;
        *lines += 1;
        if (!comment) n -= 1;
    next:
        prev = c;
        c = s->vfunc_33();
    }
    if (n > 0 || c != -1) {
        ret = true;
        *lines += 1;
    }
    if (n >= 0x1000) n = 0xFFF;
    buf[n] = 0;
    return ret;
}

igRegistryValue *FUN_00307c10(igRegistry *arg0, int arg1, const char *arg2, int arg3) {
    int s2 = 0;
    int s1 = -1;
    RegistryValueRef r;
    r.p = 0;
    for (; s2 < ((igRegistryValueList *)arg0->_valueTable)->_count; s2++) {
        igRegistryValue *s0 = ((igRegistryValue **)((igRegistryValueList *)arg0->_valueTable)->_data)[s2];
        igRegistryValue *old;
        if (s0 != 0) s0->_refCount = s0->_refCount + 1;
        old = r.p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        r.p = s0;
        if (r.p != 0 && arg1 == r.p->_section) {
            int nm;
            if (arg0->_valueNameCaseSensitive != 0) {
                nm = (((igStringObj *)r.p->_valueName)->_buffer == 0) ? ((int *)g_stringObjEmptyText)[0] : ((igStringObj *)r.p->_valueName)->_buffer;
                if (strcmp(nm, arg2) == 0) {
                    igRegistryValue *ret = r.p;
                    return ret;
                }
            } else {
                nm = (((igStringObj *)r.p->_valueName)->_buffer == 0) ? ((int *)g_stringObjEmptyText)[0] : ((igStringObj *)r.p->_valueName)->_buffer;
                if (thunk_strcasecmp((const char *)nm, arg2) == 0) {
                    igRegistryValue *ret = r.p;
                    return ret;
                }
            }
        } else if (r.p == 0 && s1 < 0) {
            s1 = s2;
        }
    }
    if (arg3 != 0) {
        int s0;
        igRegistryValueList *l;
        igRegistryValue *old;
        igRegistryValue *t;
        if (s1 < 0) {
            s1 = ((igRegistryValueList *)arg0->_valueTable)->_count;
            ObjectList_ResizeRetained((igTDataList<igObject *> *)(((igRegistryValueList *)arg0->_valueTable)), s1 * 2);
        }
        s0 = ((int)igObject_GetAllocator((int)arg0));
        old = r.p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        r.p = (igRegistryValue *)FUN_002bb500(s0);
        l = (igRegistryValueList *)arg0->_valueTable;
        arg0 = (igRegistry *)r.p;
        if (arg0 != 0) ((igRegistryValue *)arg0)->_refCount = ((igRegistryValue *)arg0)->_refCount + 1;
        old = ((igRegistryValue **)l->_data)[s1];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        if (l->_count != 0 && s1 >= 0 && s1 < l->_count) ((igRegistryValue **)l->_data)[s1] = (igRegistryValue *)arg0;
        r.p->_section = arg1;
        igStringObj_Set((int)(((igStringObj *)r.p->_valueName)), (int)arg2);
        {
            igRegistryValue *ret = r.p;
            return ret;
        }
    }
    return 0;
}

int FUN_00307f80(void *arg0, int arg1) {
    int var_v0;

    if (arg1 < 0xB) {
        return ((int *)DAT_004fb160)[arg1];
    }
    var_v0 = *(int *)((char *)(*(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 16) + (arg1 * 4))) - 44)) + 8);
    if (var_v0 == 0) return ((int *)g_stringObjEmptyText)[0]; return var_v0;
}

int igReportNotice(const char *arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return FUN_00308540(4, arg0, (int)((char*)__builtin_next_arg(arg0) - off));
}

int FUN_00308240(const char *arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return FUN_00308540(6, arg0, (int)((char*)__builtin_next_arg(arg0) - off));
}

void FUN_003082b0(const char *arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    FUN_00308540(5, arg0, (int)((char *)__builtin_next_arg(arg0) - off));
}

int igReportError(const char *arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return FUN_00308540(1, arg0, (int)((char*)__builtin_next_arg(arg0) - off));
}

int FUN_00308390(const char *arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    return FUN_00308540(2, arg0, (int)((char*)__builtin_next_arg(arg0) - off));
}

int FUN_00308400(int arg0, int arg1) {
    int *p;
    if (((int *)&DAT_004c22d8)[0] < arg0) {
        return 0;
    }
    p = &UNKNOWN[0];
    switch (arg0) {
    case 0: p = &INTERNAL_ERROR[0]; break;
    case 1: p = &ERROR[0]; break;
    case 2: p = &WARNING[0]; break;
    case 3: p = &DEPRECATION[0]; break;
    case 4: p = &NOTICE[0]; break;
    case 5: p = &INFO[0]; break;
    case 6: p = &DETAIL[0]; break;
    }
    if (arg0 < 4) {
        FUN_00304550((int)&DAT_004fb2f0[0], p, arg1);
        FUN_003046d0();
    } else {
        FUN_00304430(DAT_004fb2f0, p, arg1);
        FUN_00304680();
        return 0;
    }
    FUN_00304550((int)&DAT_004fb300[0]);
    FUN_003046d0();
    if (GPR_005549b0 != 0) {
        if (arg0 == 0 || arg0 == 1) return 1;
    }
    return 0;
}

int FUN_00308540(int arg0, const char *arg1, int arg2) {
    char buf[0x1000];
    int r;

    if (DAT_004c22e0[0] == 0) {
        return 0;
    }
    r = vsnprintf(buf, 0x1000, arg1, arg2);
    if ((r < 0) || (r >= 0x1000)) {
        buf[0xFFF] = 0;
    }
    return DAT_004c22e0[0](arg0, buf);
}

static inline int allocator(void) {
    int a = ((int)FUN_002f8a20());
    if (g_useOwnerAllocator != 0) {
        return a;
    }
    return ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString));
}

static inline char *levelText(igStringObj *s) {
    char *t = (char *)s->_buffer;
    if (t == 0) {
        return (*(char * *)g_stringObjEmptyText);
    }
    return t;
}

void FUN_003085c0(void) {
    GPR_00554c30 = 1;
    igRegistry *config = ((ObjectSystemView *)g_objectSystem[0])->configRegistry;
    if (config != 0) {
        FUN_00306e50((int)config, 2, text_assertOnErrors, (char *)&GPR_005549b0, 1, 0);
        igStringObj *name = (igStringObj *)igStringObj_Create(allocator());
        if (FUN_00306770((int)config, 2, text_defaultReportLevel, &name, (char *)DAT_004f7910, 0) != 0) {
            char *t = levelText(name);
            if (strcmp(t, text_kDetail) == 0) {
                DAT_004c22d8 = 6;
            } else if (strcmp(t, text_kInfo) == 0) {
                DAT_004c22d8 = 5;
            } else if (strcmp(t, text_kNotice) == 0) {
                DAT_004c22d8 = 4;
            } else if (strcmp(t, text_kWarning) == 0) {
                DAT_004c22d8 = 2;
            } else if (strcmp(t, text_kError) == 0) {
                DAT_004c22d8 = 1;
            }
        }
        igRelease(name);
    }
}

void FUN_00308770(void) {
    DAT_004c22e0[0] = (int (*)(int, char *))((int *)(&FUN_00308400));
    GPR_00554c30 = 0;
    ((int *)&DAT_004c22d8)[0] = 5;
}

igSmartPointer<igObject> FUN_003087a0(void *directory, int name) {
    if (strcmp(name, &text_igImageDirectory[0]) == 0) {
        return igSmartPointer<igObject>((igObject *)FUN_00308a90((igResource *)directory), kRetainReference);
    }
    return igSmartPointer<igObject>((igObject *)igProperty_FindByName((igObjectList *)(*(int *)((char *)directory + 16)), (igMetaField *)DAT_00586670[0], name), kRetainReference);
}

int FUN_00308850(int *p, int extra1)
{
    return ObjectList_AppendRetained((igObjectList *)(*(int *)((char *)p + 16)), (igObject *)extra1);
}

static inline void setNames(igResource *self, const MemberRef &value) {
    igObject *held = value.p;
    igObject *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = (igObject *)self->_alignmentStrings;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->_alignmentStrings = (int)held;
}

static inline void setValues(igResource *self, const MemberRef &value) {
    igObject *held = value.p;
    igObject *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = (igObject *)self->_alignmentValues;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->_alignmentValues = (int)held;
}

void FUN_00308860(igResource *self, int name, int value) {
    if (self->_alignmentStrings == 0) {
        setNames(self, MemberRef((igObject *)FUN_002b9350((int)(((void *)igObject_GetAllocator((int)self))))));
        setValues(self, MemberRef((igObject *)igIntList_Create((int)(((void *)igObject_GetAllocator((int)self))))));
    }
    igSmartPointer<igStringObj> entry((igStringObj *)igStringObj_Create((int)(((void *)igObject_GetAllocator((int)self)))));
    igStringObj_Set((int)entry.p, name);
    ObjectList_AppendRetained((igObjectList *)self->_alignmentStrings, (igObject *)entry.p);
    igTDataList<int> *values = (igTDataList<int> *)self->_alignmentValues;
    int top = values->count();
    if (top < values->_capacity) {
        values->_count = values->_count + 1;
    } else {
        List_Resize(values, top + 1, 4);
    }
    values->_data[top] = value;
}

static inline void setImageDirectory(igResource *owner, const igSmartPointer<igDirectory> &value) {
    igDirectory *held = value.p;
    igDirectory *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = (igDirectory *)owner->_imageDirectory;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
    }
    owner->_imageDirectory = (int)held;
}

igDirectory *FUN_00308a90(igResource *self) {
    if (self->_imageDirectory == 0) {
        int *hd;
        int v;
        int s2;
        igDirectory *s0;
        int old;
        setImageDirectory(self, igSmartPointer<igDirectory>(((igDirectory *)FUN_002c72c0(FUN_00301000()))));
        s0 = (igDirectory *)self->_imageDirectory;
        if (0 == g_stringPool[0]) {
            v = ((int)StringPool_Allocate(16));
            if (v != 0) {
                v = ((int)StringPool_Construct((StringPool *)v));
            }
            g_stringPool[0] = v;
        }
        s2 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)(((char *)text_igImageDirectory)));
        old = s0->_name;
        if (old != 0) {
            hd = (int *)(old - 8);
            v = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = v;
            if (v == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd), (int)hd);
            }
        }
        s0->_name = s2;
        ((igDirectory *)self->_imageDirectory)->_managingResource = (int)self;
        FUN_00308850((int *)self, self->_imageDirectory);
    }
    fflush(_impure_ptr->_stdout);
    return (igDirectory *)self->_imageDirectory;
}

void FUN_00308c00(int *arg0, void *arg1) {
    int temp_s0;

    if (arg1 == 0) {
        *arg0 = g_resultFailure.v;
    } else {
        temp_s0 = *(int *)((char *)(arg1) + 32);
        if (*(int *)((char *)(arg1) + 52) > 1) {
            FUN_00309640((igResource *)temp_s0, (igIGBFileView *)arg1);
            igResource_UnloadDirectory((igResource *)temp_s0, *(int *)((char *)(arg1) + 20));
        }
        *arg0 = g_resultSuccess.v;
    }
}

