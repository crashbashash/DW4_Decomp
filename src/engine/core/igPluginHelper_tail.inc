static inline char *keyText(IniKeyText *s) { char *t = s->text; if (t == 0) { return (*(char * *)g_stringObjEmptyText); } return t; }

static inline void dropKey(IniKeyText *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

static inline void dropValues_304b10(IniValueList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

void FUN_00304b10(void *self) {
    void *ini;
    int section;
    unsigned int n;
    unsigned int i;
    int j;
    IniKeyText *key;
    IniValueList *values;
    char *string;
    char *text;
    IniValueList *held;
    ini = (*(IniSystemTables * *)g_objectSystem)->ini;
    section = FUN_00306360((IniSectionsView *)ini, PLUGINS, 1);
    if (section >= 0) {
        n = ((unsigned int)FUN_003064b0((int)ini, section));
        for (i = 0; i < n; i++) {
            key = 0;
            if (!igRegistry_GetKeyName((int)ini, section, i, &key)) {
                dropKey(key);
            } else {
                *(IniValueList **)&values = ((IniValueList *)igStringRefList_Create(((int)igObject_GetAllocator((int)self))));
                held = values;
                if (FUN_00306aa0(ini, section, keyText(key), (SL *)held, 0) == 0) {
                    dropValues_304b10(values);
                    dropKey(key);
                } else {
                    for (j = 0; j < (held = values)->count; j++) {
                        StringList_CopyRetained(&string, values, j);
                        text = string;
                        FUN_00304840((igPluginHelper *)self, (int)(keyText(key)), (int)text);
                        dropString(string);
                    }
                    dropValues_304b10(held);
                    dropKey(key);
                }
            }
        }
    }
}

void Gap__Core__igPluginHelper__vfunc_10(S_304d90 *arg0) {
    int temp_s1;
    int var_s0;
    R_304d90 *sp4C;

    temp_s1 = arg0->f14->cnt;
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        sp4C = arg0->f14->arr[var_s0];
        if (sp4C != 0) {
            sp4C->refs = sp4C->refs + 1;
        }
        arg0->f10->vX(&sp4C);
        if (sp4C != 0) {
            sp4C->refs = sp4C->refs - 1;
            if ((sp4C->refs & 0x7fffff) == 0) {
                igObject_Destroy(sp4C);
            }
        }
    }
}

int FUN_00304e60(Args *args) {
    int key;
    Iter *it;
    igResult (*fn)(int);

    it = args->it;
    fn = args->fn;
    Memory_FreeBuffer((void *)args);
    for (it->vNext(&key, 1); fn(key) == g_resultSuccess; it->vNext(&key, 1)) {
    }
    return 0;
}

void **FUN_00304f00(void *arg0, int arg1, int arg2) {
    void **a; void *b;
    a = (void **)(((void **)igObject_GetAllocator((int)arg0)));
    b = (void *)(((DW4VC_216_1 *)(a))->vX((int)(8)));
    *(int *)((char *)(b) + 0) = arg1;
    *(int *)((char *)(b) + 4) = (int)(arg0);
    a = (void **)(((void **)FUN_002b7f40((int)a)));
    ((DW4VCSR_132_1 *)(a))->vX((int (*)(...))FUN_00304e60);
    ((DW4VCSR_140_1 *)(a))->vX((int)(b));
    ((DW4VCSR_156_1 *)(a))->vX((int)(arg2));
    if (((DW4VCSR_120_0 *)(a))->vX() == g_resultSuccess) {
        ObjectList_AppendRetained((igObjectList *)(*(int *)((char *)(arg0) + 8)), (igObject *)a);
    }
    return a;
}

int FUN_00305000(H_305000 *h) {
    R_305000 sp58, sp5C;
    int n;
    O_305000 *p;
    int c;
    int k;
    Lst_305000 *l;
    int i;
    int m;
    O_305000 *o;
    int j;

    n = h->l->n;
    for (i = 0; i < n; i++) {
        o = h->l->d[i];
        if (o->v30()) {
            sp5C = o->v42();
        }
        if (o->v30()) {
            sp58 = ((Y_305000 * *)g_threadManager)[0]->v21()->v22(o);
        }
        o->rc = o->rc - 1;
        if (((unsigned long long)((long long)o->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    if (n > 0) {
        l = h->l;
        m = l->n;
        for (j = 0; j < m; j++) {
            p = l->d[j];
            if (p != 0) {
                p->rc = p->rc - 1;
                if (((unsigned long long)((long long)p->rc << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        c = l->n;
        for (k = 0; k < c; k++) {
            l->d[k] = 0;
        }
        l->n = 0;
    }
}

int thunk_FUN_00305000(int extra0)
{
    return FUN_00305000((H_305000 *)extra0);
}

