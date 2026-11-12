void FUN_001af860(igAttrStack *arg0) {
    arg0->_count = 0;
    arg0->_cachedOverride = -1;
    arg0->_lastIncrementalFlushedAttr = arg0->_default;
    arg0->_hasChangedFromLastIncrementalFlush = 0;
    arg0->_hasChangedFromRoot = 0;
    arg0->_cachedRenderPackage = 0;
}

void Gap__Sg__igAttrStackManager__vfunc_23(struct O_1af890 *arg0) {
    int var_s0;
    if (arg0->n > 0) {
        for (var_s0 = 0; var_s0 < arg0->n; var_s0++) {
            FUN_001af860((igAttrStack *)arg0->l16->arr[var_s0]);
        }
        arg0->b24->f8 = 0;
        arg0->b28->f8 = 0;
        FUN_001b0dc0((O_1b0dc0 *)arg0);
        arg0->b44->f8 = 0;
        arg0->b64->f20 = 0;
    }
}

void Gap__Sg__igAttrStackManager__vfunc_09(unsigned char *arg0, int arg1) {
    unsigned char sp4F;
    int al; int idx; int z; struct L_1af920 *l;
    Gap__Core__igObject__vfunc_07(arg0);
    if (arg1 == 0) {
        if (DAT_00562580[0] == 0) {
            al = igObject_GetAllocator(arg0);
            al = GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(DAT_005870f8[0]);
            DAT_00562580[0] = ((struct L_1af920 *)FUN_001a51d0(al));
        }
        l = DAT_00562580[0];
        idx = n_of(l);
        if (idx < l->cap) { l->n = l->n + 1; } else { List_Resize((void *)l, idx + 1, 4); }
        l->data[idx] = (int)arg0;
        z = ((struct Z * *)DAT_00586dc8)[0]->f56;
        sp4F = arg0[60];
        FUN_00306e50(z, 7, &DAT_004e4520[0], &sp4F, 0, 0);
        arg0[60] = sp4F;
    }
}

void Gap__Sg__igAttrStackManager__vfunc_10(int arg0) {
    int i;
    AttrStackList *p;
    K key((void *)arg0);
    i = Finder::Find(((AttrStackList * *)DAT_00562580)[0], key);
    if (i >= 0) {
        List_RemoveWordAt(((AttrStackList * *)DAT_00562580)[0], i);
    }
    p = ((AttrStackList * *)DAT_00562580)[0];
    if (p->n == 0) {
        p->rc = p->rc - 1;
        if ((p->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
        ((AttrStackList * *)DAT_00562580)[0] = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

void FUN_001afb00(void) {
    R_1afb00 *p;
    int rc;
    p = DAT_00562578[0];
    if (p != 0) {
        rc = p->f4 - 1;
        p->f4 = rc;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)p);
        }
    }
    DAT_00562578[0] = 0;
}

void FUN_001afb60(char *arg0) {
    int n;
    int i;
    int idx;
    if (FUN_002fe290(arg0, igAttr_GetMetaObject()) != 0 && *(unsigned char *)(arg0 + 26) == 0) {
        if (((RefObj * *)DAT_00562578)[0] == 0) {
            ((RefObj * *)DAT_00562578)[0] = FUN_002c8e10(((void *)Memory_GetAllocatorBySelector(DAT_00587038[0])));
        }
        K key(arg0);
        idx = Finder_1afb60::Find(((RefObj * *)DAT_00562578)[0], key);
        if (idx < 0) {
            ObjectList_AppendRetained(((RefObj * *)DAT_00562578)[0], arg0);
            if (((RefObj * *)DAT_00562580)[0] != 0) {
                n = ((RefObj * *)DAT_00562580)[0]->count;
                for (i = 0; i < n; i++) {
                    FUN_001afc90((AttrManagerRec *)((RefObj * *)DAT_00562580)[0]->data[i], (AttrObj *)arg0);
                }
            }
        }
    }
}

void FUN_001afc90(AttrManagerRec *m, AttrObj *meta) {
    if (m->_defaultManager != 0 && m->_capabilityManager != 0) {
        int units;
        int end;
        int first;
        int i;
        int id;
        id = meta->_id;
        if (id >= m->_attrStackIndexTableSize) {
            m->_attrStackIndexTableSize = id + 4;
            m->_attrStackIndexTable = FUN_00300e50(m, m->_attrStackIndexTable, m->_attrStackIndexTableSize * 4);
        }
        units = FUN_001d8270((int)(meta));
        if (units <= 0) {
            igSmartPointer<AttrObj> def = m->_defaultManager->getDefault(meta, 0);
            units = ((AttrCaps *)def.get())->unitCount((void *)m->_capabilityManager);
            if (units <= 0) {
                units = 1;
            }
        }
        first = m->_numAttrStacks;
        end = first + units;
        ObjectList_ResizeRetained(m->_attrDefaults, end);
        ObjectList_ResizeRetained(m->_attrStacks, end);
        m->_attrStackIndexTable[id] = first;
        m->_numAttrStacks = end;
        for (i = 0; i < units; i++, first++) {
            igSmartPointer<AttrObj> def = m->_defaultManager->getDefault(meta, i);
            igSmartPointer<AttrStackRec> stack((AttrStackRec *)((AttrObj *)FUN_001a5a70(igObject_GetAllocator(m))));
            AttrObj **slot;
            AttrObj *value;
            slot = &stack.p->_default;
            value = def.get();
            attrFieldSet(slot, value);
            stack.p->_popProc = 0;
            {
                AttrObj *d = def.get();
                stack.p->_lastIncrementalFlushedAttr = d;
            }
            {
                igObject *entry = stack.p;
                attrListSet(m->_attrStacks, first, entry);
                entry = def.get();
                attrListSet(m->_attrDefaults, first, entry);
            }
        }
    }
}

void FUN_001b0000(T_1b0000 *arg0, int arg1, Obj_1b0000 *arg2, Obj_1b0000 *arg3)
{
    List *l;
    int n;
    int i;
    Obj_1b0000 *o;
    if (arg2 != 0) {
        arg2->references = arg2->references + 1;
    }
    o = arg0->f56;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f56 = arg2;
    if (arg3 != 0) {
        arg3->references = arg3->references + 1;
    }
    o = arg0->f52;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f52 = arg3;
    arg0->v21();
    l = arg0->f20;
    n = l->count;
    for (i = 0; i < n; i++) {
        o = l->data[i];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m = l->count;
        int j;
        for (j = 0; j < m; j++) {
            l->data[j] = 0;
        }
    }
    l->count = 0;
    l = arg0->f16;
    n = l->count;
    for (i = 0; i < n; i++) {
        o = l->data[i];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m = l->count;
        int j;
        for (j = 0; j < m; j++) {
            l->data[j] = 0;
        }
    }
    l->count = 0;
    arg0->f12 = 0;
    n = ((List * *)DAT_00562578)[0]->count;
    for (i = 0; i < n; i++) {
        FUN_001afc90((AttrManagerRec *)arg0, (AttrObj *)((List * *)DAT_00562578)[0]->data[i]);
    }
}

#define SETCNT(l, n) if ((n) >= 0) { if ((n) <= (l)->cap) (l)->cnt = (n); else List_Resize((l), (n), 4); }
void FUN_001b0250(PendingValueCollector *arg0, PendingIntList *arg1) {
    PendingIntList *ixl;
    int *a2;
    int s1;
    int s5;
    int c;
    int v;
    int s0;
    int *ix;
    TrackedIntStack *o;
    TrackedIntTable *tbl;
    TrackedIntStack **tb;
    int k;
    int s4;
    int *src;
    int i;
    s4 = arg1->cnt;
    s0 = 0;
    s1 = arg0->f24->cnt;
    k = s1 + s4;
    if (arg0->f60 == 0) {
        SETCNT(arg1, k);
        a2 = arg1->data + s4;
    } else {
        s5 = arg0->f44->cnt;
        k = k + s5;
        SETCNT(arg1, k);
        src = arg0->f44->data;
        a2 = arg1->data + s4;
        for (; s0 < s5; s0++) a2[s0] = src[s0];
        arg0->f44->cnt = 0;
    }
    ixl = arg0->f24;
    ix = ixl->data;
    tbl = arg0->f16;
    tb = tbl->data;
    for (i = 0; i < s1; i++) {
        o = tb[ix[i]];
        if (o->f24 >= 0) v = o->data[o->f24];
        else if ((c = o->cnt) != 0) { c = c - 1; v = *(int *)((char *)o->data + c * 4); }
        else v = o->f20;
        o->f32 = 0;
        if (v != o->f36) { a2[s0++] = v; o->f36 = v; }
    }
    k = s0 + s4;
    SETCNT(arg1, k);
    arg0->f24->cnt = 0;
}
#undef SETCNT

void FUN_001b0440(int a0, int a1) {
    *(int *)((char *)a1 + 8) = 0;
    FUN_001b0250((PendingValueCollector *)a0, (PendingIntList *)a1);
}

void FUN_001b0450(A_1b0450 *arg0, Rc_1b0450 *arg1) {
    Rc_1b0450 *a;
    int n, j;
    int *vals;
    int *keys;
    int *out;
    E_1b0450 **ents;
    int i;
    arg1->n = 0;
    n = arg0->f28.p->n;
    a = arg0->f32.p;
    if (n >= 0) {
        if (n <= a->cap) a->n = n; else List_Resize((void *)a, n, 4);
    }
    j = 0;
    if (n >= 0) {
        if (n <= arg1->cap) arg1->n = n; else List_Resize((void *)arg1, n, 4);
    }
    keys = arg0->f28.p->data;
    out = arg0->f32.p->data;
    vals = arg1->data;
    ents = arg0->f16->data;
    for (i = 0; i < n; i++) {
        int v = keys[i];
        E_1b0450 *e = ents[v];
        int x;
        int m;
        if (e->idx >= 0) x = e->data[e->idx];
        else { m = e->n; if (m != 0) { int k = m - 1; x = e->data[k]; } else x = e->def; }
        if (x != e->def) {
            out[j] = v;
            vals[j] = x;
            j++;
        } else {
            e->flag = 0;
        }
    }
    if (j >= 0) {
        if (j <= arg1->cap) arg1->n = j; else List_Resize((void *)arg1, j, 4);
    }
    a = arg0->f32.p;
    if (j >= 0) {
        if (j <= a->cap) a->n = j; else List_Resize((void *)a, j, 4);
    }
    {
        igSmartPointer<Rc_1b0450> swapped(arg0->f32);
        arg0->f32 = arg0->f28;
        arg0->f28 = swapped;
    }
    arg0->f8 = 0;
}

void FUN_001b0dc0(O_1b0dc0 *arg0) {
    int n, i;
    n = arg0->c24->n;
    for (i = 0; i < n; i++) {
        E2 *e = arg0->l->arr[i + arg0->base[DAT_0055f060[0]->idx]]->f14;
        R_1b0dc0 **slot = &e->f10;
        R_1b0dc0 *r = *slot;
        if (r != 0) {
            r->f4 = (int)((int) (r->f4 - 1));
            if (((unsigned long long) ((long long) r->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)r);
            }
        }
        *slot = 0;
    }
    arg0->c24->n = 0;
    arg0->c28->n = 0;
}

void FUN_001b1030(igAttrStackManager *self, igAttr *attr) {
    AttrObjectStack *stack = (AttrObjectStack *)self->_attrStacks;
    int slot = attr->_cachedAttrIndex;
    slot = attr->_cachedUnitID + ((int *)self->_attrStackIndexTable)[slot];
    stack = (AttrObjectStack *)stack->_data[slot];
    stack->append((igObject *)attr);
    FUN_001b1490((struct A_1b1490 *)self, (struct B_1b1490 *)stack, slot);
}

void FUN_001b1100(struct A_1b1100 *arg0, struct B_1b1100 *arg1) {
    int (*temp_a2)(int, int);
    int temp_s1;
    struct Q_1b1100 *temp_s0;
    int x; int n1; int *a;

    temp_s1 = arg0->f68[arg1->idx] + arg1->off;
    temp_s0 = arg0->f16->q[temp_s1];
n1 = temp_s0->n - 1; a = temp_s0->a; x = a[n1];
    temp_a2 = temp_s0->cb;
    if (temp_a2 != 0) {
        temp_a2(x, arg0->f48);
    }
    temp_s0->n = temp_s0->n - 1;
    FUN_001b1490((struct A_1b1490 *)arg0, (struct B_1b1490 *)temp_s0, temp_s1);
}

void FUN_001b11b0(struct A_1b11b0 *arg0, struct B_1b11b0 *arg1) {
    int (*temp_a2)(int, int);
    int temp_s1;
    struct Q_1b11b0 *temp_s0;
    int x; int n1; int *a;

    temp_s1 = arg0->f68[arg1->idx];
    temp_s0 = arg0->f16->q[temp_s1];
n1 = temp_s0->n - 1; a = temp_s0->a; x = a[n1];
    temp_a2 = temp_s0->cb;
    if (temp_a2 != 0) {
        temp_a2(x, arg0->f48);
    }
    temp_s0->n = temp_s0->n - 1;
    FUN_001b1490((struct A_1b1490 *)arg0, (struct B_1b1490 *)temp_s0, temp_s1);
}

void FUN_001b1250(struct A_1b1250 *arg0, struct B_1b1250 *arg1, int arg2) {
    int (*temp_a2)(int, int);
    int temp_s1;
    struct Q_1b1250 *temp_s0;
    int x; int n1; int *a;

    temp_s1 = arg2 + arg0->f68[arg1->idx];
    temp_s0 = arg0->f16->q[temp_s1];
n1 = temp_s0->n - 1; a = temp_s0->a; x = a[n1];
    temp_a2 = temp_s0->cb;
    if (temp_a2 != 0) {
        temp_a2(x, arg0->f48);
    }
    temp_s0->n = temp_s0->n - 1;
    FUN_001b1490((struct A_1b1490 *)arg0, (struct B_1b1490 *)temp_s0, temp_s1);
}

void FUN_001b12f0(igAttrStackManager *self, igAttr *attr) {
    AttrObjectStack *stack = (AttrObjectStack *)self->_attrStacks;
    int slot = attr->_cachedAttrIndex;
    slot = attr->_cachedUnitID + ((int *)self->_attrStackIndexTable)[slot];
    stack = (AttrObjectStack *)stack->_data[slot];
    if (stack->_cachedOverride < 0) {
        stack->_cachedOverride = stack->_count;
    }
    stack->append((igObject *)attr);
    FUN_001b1490((struct A_1b1490 *)self, (struct B_1b1490 *)stack, slot);
}

void FUN_001b13d0(struct A_1b13d0 *arg0, struct B_1b13d0 *arg1) {
    int (*temp_a2)(int, int);
    int temp_s1;
    struct Q_1b13d0 *temp_s0;
    int n1; int *a; int x;

    temp_s1 = arg1->off + arg0->f68[arg1->idx];
    temp_s0 = arg0->f16->q[temp_s1];
    n1 = temp_s0->n - 1; a = temp_s0->a; x = a[n1];
    temp_a2 = temp_s0->cb;
    if ((temp_a2 != 0) && (x == (int)arg1)) {
        temp_a2(x, arg0->f48);
    }
    temp_s0->n = temp_s0->n - 1;
    if (temp_s0->n == temp_s0->f24) {
        temp_s0->f24 = -1;
    }
    FUN_001b1490((struct A_1b1490 *)arg0, (struct B_1b1490 *)temp_s0, temp_s1);
}

void FUN_001b1490(struct A_1b1490 *arg0, struct B_1b1490 *arg1, int arg2) {
    int c1;
    int c2;
    struct L_1b1490 *l1;
    struct L_1b1490 *l2;

    if (arg1->f32 == 0) {
        l1 = arg0->f24;
        c1 = l1->n;
        if (c1 < l1->cap) {
            l1->n = n_of_1b1490(l1) + 1;
        } else {
            List_Resize((void *)l1, c1 + 1, 4);
        }
        l1->arr[c1] = arg2;
        arg1->f32 = 1U;
    }
    if (arg1->f40 == 0) {
        l2 = arg0->f28;
        c2 = l2->n;
        if (c2 < l2->cap) {
            l2->n = n_of_1b1490(l2) + 1;
        } else {
            List_Resize((void *)l2, c2 + 1, 4);
        }
        l2->arr[c2] = arg2;
        arg1->f40 = 1U;
    }
    arg0->f8 = 1;
}

void FUN_001b1cf0(igDataList *arg0) {
    unsigned int temp_a2;
    int *temp_a0;

    temp_a2 = arg0->_count;
    temp_a0 = (int *)arg0->_data;
    switch (temp_a2) {
    case 16:
        temp_a0[15] = -1;
        
    case 15:
        temp_a0[14] = -1;
        
    case 14:
        temp_a0[13] = -1;
        
    case 13:
        temp_a0[12] = -1;
        
    case 12:
        temp_a0[11] = -1;
        
    case 11:
        temp_a0[10] = -1;
        
    case 10:
        temp_a0[9] = -1;
        
    case 9:
        temp_a0[8] = -1;
        
    case 8:
        temp_a0[7] = -1;
        
    case 7:
        temp_a0[6] = -1;
        
    case 6:
        temp_a0[5] = -1;
        
    case 5:
        temp_a0[4] = -1;
        
    case 4:
        temp_a0[3] = -1;
        
    case 3:
        temp_a0[2] = -1;
        
    case 2:
        temp_a0[1] = -1;
        
    case 1:
        temp_a0[0] = -1;
        break;
    case 0:
        break;
    default:
        memset(temp_a0, 0xFF, temp_a2 * 4);
        break;
    }
}

void FUN_001b1dc0(igDataList *arg0) {
    unsigned int temp_a2;
    int *temp_a0;

    temp_a2 = arg0->_count;
    temp_a0 = (int *)(arg0->_data);
    switch (temp_a2) {
    case 16:
        temp_a0[15] = 0;
        
    case 15:
        temp_a0[14] = 0;
        
    case 14:
        temp_a0[13] = 0;
        
    case 13:
        temp_a0[12] = 0;
        
    case 12:
        temp_a0[11] = 0;
        
    case 11:
        temp_a0[10] = 0;
        
    case 10:
        temp_a0[9] = 0;
        
    case 9:
        temp_a0[8] = 0;
        
    case 8:
        temp_a0[7] = 0;
        
    case 7:
        temp_a0[6] = 0;
        
    case 6:
        temp_a0[5] = 0;
        
    case 5:
        temp_a0[4] = 0;
        
    case 4:
        temp_a0[3] = 0;
        
    case 3:
        temp_a0[2] = 0;
        
    case 2:
        temp_a0[1] = 0;
        
    case 1:
        temp_a0[0] = 0;
    case 0:
        break;
    default:
        memset(temp_a0, 0, temp_a2 * 4);
        break;
    }
}

void FUN_001b1e50(void *arg, unsigned int bits) {
    igBitMaskWords *m;
    unsigned int old;
    int partial;
    int i;
    int n;
    m = (igBitMaskWords *)arg;
    old = m->_bitCount;
    if (bits <= old) {
        m->_bitCount = bits;
        m->setCount((bits + 31) >> 5);
    } else {
        i = m->_count;
        partial = old & 31;
        m->_bitCount = bits;
        m->setCount((bits + 31) >> 5);
        if (partial != 0) {
            unsigned int mask = ((1 << partial) - 1) & m->getWord(i - 1);
            m->setWord(i - 1, mask);
        }
        n = m->_count;
        for (; i < n; i++) {
            m->setWord(i, DAT_0048d8d0);
        }
    }
}

