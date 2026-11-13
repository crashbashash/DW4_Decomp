void FUN_002d38e0(int a0, int a1)
{
    *(int *)((char *)a0 + 12) = a1;
}

void FUN_002d38f0(void *arg0) {
    int temp_a1;
    void *temp_a0;

    temp_a1 = *(int *)((char *)(arg0) + 8);
    temp_a0 = (void *)(*(int *)((char *)(arg0) + 16));
    if (temp_a1 >= *(int *)((char *)(temp_a0) + 8)) {
        List_Reserve((L_2d6680 *)temp_a0, temp_a1, 4);
    }
    ((DW4VC_124_1 *)(((char *)(arg0) + 0)))->vX((int)(*(int *)((char *)(arg0) + 12)));
}

void FUN_002d3950(struct S_2d3950 *arg0) {
    struct L_2d3950 *temp_a0;
    struct L_2d3950 *temp_a0_2;
    struct L_2d3950 *temp_a0_3;
    struct L_2d3950 *temp_a0_4;
    struct L_2d3950 *temp_a0_5;
    temp_a0 = arg0->f16;
    if (!(0 > temp_a0->cap)) {
        temp_a0->cnt = 0;
    } else {
        List_Resize(temp_a0, 0, 4);
    }
    temp_a0_2 = arg0->f16;
    if (!(0 < temp_a0_2->cnt)) {
        List_Reserve((L_2d6680 *)temp_a0_2, 0, 4);
    }
    temp_a0_3 = arg0->f20;
    if (!(0 > temp_a0_3->cap)) {
        temp_a0_3->cnt = 0;
    } else {
        List_Resize(temp_a0_3, 0, 4);
    }
    temp_a0_4 = arg0->f20;
    if (temp_a0_4 != 0) {
    if (!(0 > temp_a0_4->cap)) {
        temp_a0_4->cnt = 0;
    } else {
        List_Resize(temp_a0_4, 0, 4);
    }
    temp_a0_5 = arg0->f20;
    if (!(0 < temp_a0_5->cnt)) {
        List_Reserve((L_2d6680 *)temp_a0_5, 0, 4);
    }
    }
}

void FUN_002d3a20(void **arg0) {
    DW4SR4 sp1C;

    sp1C = ((DW4VCSR_96_1 *)(arg0))->vX((int)(0));
}

int Gap__Core__igCallStackTable__vfunc_23(void *arg0) {
    void *obj;
    int *p;
    int n;
    int i;
    int cnt;

    obj = (void *)(*(int *)((char *)(arg0) + 16));
    cnt = 0;
    p = (int *)(*(int *)((char *)(obj) + 16));
    n = *(int *)((char *)(obj) + 8);
    for (i = 0; i < n; i++) {
        if (*p == 0) {
            cnt++;
        }
        p++;
    }
    return cnt;
}

void Gap__Core__igCallStackTable__vfunc_24(int *arg0, struct S_2d3aa0 *arg1, int arg2) {
    struct L_2d3aa0 *l;
    int i;
    int cnt;
    int *data;
    int n;
    int t;
    l = arg1->f16;
    data = l->data;
    n = l->n;
    cnt = 0;
    if (arg2 == 0) {
        if (0 <= l->cap) { l->n = 0; } else { List_Resize(l, 0, 4); }
        *arg0 = g_resultSuccess.v;
        return;
    }
    for (i = 0; i < n; i++) {
        if (data[0] == 0) {
            cnt = cnt + 1;
            if (cnt == arg2) {
                t = i + 1;
                if (t >= 0) {
                    if (t <= l->cap) { l->n = t; } else { List_Resize(l, t, 4); }
                }
                *arg0 = g_resultSuccess.v;
                return;
            }
        }
    }
    *arg0 = g_resultFailure.v;
}

int *Gap__Core__igCallStackTable__vfunc_25(struct O_2d3b80 *o, int i) {
int *r; if (i < 0 || i >= o->l->count || o->l->data == 0) { r = 0; } else { r = o->l->data + i; if (i > 0 && r[-1] != 0) r = 0; } return r;
}

/* igCallStackTable: words = zero-terminated call stacks packed end to end, index = hash slots.
 * Slot 30 inserts a stack's word offset into the hash index (vfunc_30). */
struct CallStackWordList {
    int vtable; int references; int count; int capacity; int *data;
    void reserveFor(int n) const {
        int grown = capacity * 2;
        if (capacity < n) {
            if (!(grown < count)) {
                List_Reserve((L_2d6680 *)this, grown, 4);
            }
        }
    }
};
class CallStackTableAddView { public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual int insert(int *key, int value);
    int references; int pad8; int pad12; CallStackWordList *words; CallStackIndexList *index;
};
/* Number of return addresses before the terminating zero. */
static inline int callStackDepth(const int *stack) {
    int depth = 0;
    while (*stack++ != 0) {
        depth++;
    }
    return depth;
}
/* Appends a zero-terminated call stack to the word list and returns its word offset. */
extern "C" int Gap__Core__igCallStackTable__addCallStack(CallStackTableAddView *self, int *stack) {
    int length;
    int offset;
    length = callStackDepth(stack) + 1;
    self->words->reserveFor(length + (offset = self->words->count));
    List_AppendWords((WordList *)self->words, length, (int)stack);
    if (self->index != 0 && self->index->count != 0) {
        self->insert(self->words->data + offset, offset);
    }
    return offset;
}

void Gap__Core__igCallStackTable__vfunc_27(O_2d3cd0 *o, int x) { switch (o->v26()) { case -1: o->v24(x); break; default: break; } }

/* igCallStackTable: words = zero-terminated call stacks packed end to end, index = hash slots
 * holding word offsets (-1 = empty). Slot 29 (vfunc_29) hashes a stack. */
class CallStackTableFindView { public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual int hash(unsigned int *stack);
    int references; int pad8; int pad12; CallStackIndexCells *words; CallStackIndexList *index;
};
static inline int callStackDepth(const unsigned int *stack) {
    int depth = 0;
    while (*stack++ != 0) {
        depth++;
    }
    return depth;
}
/* strcmp over zero-terminated return-address arrays. */
static inline int compareCallStacks(const unsigned int *a, const unsigned int *b) {
    /* matching construct: manual variant search — (bool) test gives retail's sltu/xori end-of-stack check */
    while ((bool)*a && *b != 0 && *a == *b) {
        a++;
        b++;
    }
    if (*a < *b) {
        return 1;
    }
    if (*b < *a) {
        return -1;
    }
    return 0;
}
/* Returns the word offset of an identical stored call stack, or -1. */
extern "C" int Gap__Core__igCallStackTable__findCallStack(CallStackTableFindView *self, unsigned int *stack) {
    CallStackIndexList *index;
    int slot;
    int offset;
    int n;
    int tries;
    unsigned int *s;
    unsigned int *end;

    index = self->index;
    if (index != 0 && index->count != 0) {
        slot = self->hash(stack);
        tries = 0;
        n = self->index->count;
        for (;;) {
            offset = self->index->data[slot];
            if (offset == -1) {
                return -1;
            }
            if (compareCallStacks(self->words->data + offset, stack) == 0) {
                return offset;
            }
            slot += 1;
            if (slot >= n) {
                slot = 0;
            }
            tries += 1;
            if (tries >= n) {
                return -1;
            }
        }
    }
    /* matching construct: manual variant search — end computed before the cursor; colours the base register */
    end = self->words->data + self->words->count;
    s = self->words->data;
    while (s < end) {
        if (compareCallStacks(stack, s) == 0) {
            return s - self->words->data;
        }
        s += callStackDepth(s) + 1;
    }
    return -1;
}

unsigned int Gap__Core__igCallStackTable__vfunc_29(CallStackTableView *self, unsigned int *stack) {
    CallStackHashTable *t = self->table;
    unsigned int sum = 0;
    unsigned int n;
    unsigned int v;
    unsigned int r;
    if (t != 0) { n = t->count; } else { n = 0; }
    if (stack != 0 && t != 0) {
        r = 0;
        if (n != 0) {
            v = *stack;
            while (v != 0) { sum += v; stack++; v = *stack; }
            r = sum % n;
        }
    } else {
        r = 0;
    }
    return r;
}

static inline void setAt(CallStackIndexCells *l, int i, int v) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = v;
    }
}

int Gap__Core__igCallStackTable__vfunc_30(CallStackTableHashView *self, int *key, int value) {
    int tries = 0;
    int n = self->index->count;
    int half = n / 2;
    int h;
    CallStackIndexList *index;
    if (n != 0) {
        h = self->Hash(key);
        index = self->index;
        do {
            if (index->data[h] == -1) {
                setAt((CallStackIndexCells *)index, h, value);
                goto ok;
            }
            h++;
            if (h >= n) {
                h = 0;
            }
            tries++;
        } while (tries < half);
        self->Rehash(n * 2);
        return 0;
    }
ok:
    return 1;
}

void Gap__Core__igCallStackTable__vfunc_31(T_2d40f0 *self, int arg1)
{
    Ref *r;
    int cnt;
    IList *l;
    unsigned *var_a1_2;
    unsigned *data;
    int var_a0;
    IList *v;
    unsigned *temp_s2;
    int var_a1;
    unsigned *temp_s1_2;
    unsigned *var_s0;
    int temp_s1;

    FUN_002d38e0((int)self, arg1);
    if (arg1 != 0) {
        if (self->list == 0) {
            temp_s1 = ((int)igObject_GetAllocator((int)self));
            r = (Ref *)self->list;
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->list = (IList *)FUN_002ca8b0(temp_s1);
        }
        l = self->list;
        if (arg1 >= l->count) List_Reserve((L_2d6680 *)l, arg1, 4);
        l = self->list;
        if (arg1 >= 0) {
            if (arg1 <= l->cap) l->count = arg1;
            else List_Resize(l, arg1, 4);
        }
        v = self->list;
        cnt = v->count;
        data = v->data;
        for (var_a1 = 0; var_a1 < cnt; var_a1++) data[var_a1] = *(unsigned *)DAT_004c1e98;
        temp_s2 = self->tab->data;
        var_s0 = temp_s2;
        temp_s1_2 = temp_s2 + self->tab->count;
        while (var_s0 < temp_s1_2) {
            if (!self->v28(var_s0, var_s0 - temp_s2)) return;
            var_a1_2 = var_s0;
            var_a0 = 0;
            while (*var_a1_2++ != 0) var_a0++;
            var_s0 += var_a0 + 1;
        }
    } else {
        r = (Ref *)self->list;
        if (r != 0) {
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->list = 0;
        }
    }
}

