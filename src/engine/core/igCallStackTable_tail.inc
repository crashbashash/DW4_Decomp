void FUN_002d38e0(igCallStackTableView *table, int hashCapacity)
{
    table->_hashCapacity = hashCapacity;
}

void FUN_002d38f0(igCallStackTableView *table) {
    int capacity;
    igTDataList<unsigned int> *callStacks;

    capacity = table->_capacity;
    callStacks = table->_callStacks;
    if (capacity >= callStacks->_count) {
        List_Reserve((L_2d6680 *)callStacks, capacity, 4);
    }
    table->vfunc_31(table->_hashCapacity);
}

void FUN_002d3950(igCallStackTableView *table) {
    igTDataList<unsigned int> *callStacks;
    igTDataList<unsigned int> *callStacks2;
    igTDataList<int> *hashIndex;
    igTDataList<int> *hashIndex2;
    igTDataList<int> *hashIndex3;
    callStacks = table->_callStacks;
    if (!(0 > callStacks->_capacity)) {
        callStacks->_count = 0;
    } else {
        List_Resize(callStacks, 0, 4);
    }
    callStacks2 = table->_callStacks;
    if (!(0 < callStacks2->_count)) {
        List_Reserve((L_2d6680 *)callStacks2, 0, 4);
    }
    hashIndex = table->_hashIndex;
    if (!(0 > hashIndex->_capacity)) {
        hashIndex->_count = 0;
    } else {
        List_Resize(hashIndex, 0, 4);
    }
    hashIndex2 = table->_hashIndex;
    if (hashIndex2 != 0) {
    if (!(0 > hashIndex2->_capacity)) {
        hashIndex2->_count = 0;
    } else {
        List_Resize(hashIndex2, 0, 4);
    }
    hashIndex3 = table->_hashIndex;
    if (!(0 < hashIndex3->_count)) {
        List_Reserve((L_2d6680 *)hashIndex3, 0, 4);
    }
    }
}

void FUN_002d3a20(igCallStackTableView *table) {
    igResult discarded;

    discarded = table->vfunc_24(0);
}

int Gap__Core__igCallStackTable__vfunc_23(igCallStackTableView *table) {
    igTDataList<unsigned int> *callStacks;
    unsigned int *p;
    int n;
    int i;
    int cnt;

    callStacks = table->_callStacks;
    cnt = 0;
    p = callStacks->_data;
    n = callStacks->_count;
    for (i = 0; i < n; i++) {
        if (*p == 0) {
            cnt++;
        }
        p++;
    }
    return cnt;
}

void Gap__Core__igCallStackTable__vfunc_24(igResult *result, igCallStackTableView *table, int count) {
    igTDataList<unsigned int> *l;
    int i;
    int cnt;
    unsigned int *data;
    int n;
    int t;
    l = table->_callStacks;
    data = l->_data;
    n = l->_count;
    cnt = 0;
    if (count == 0) {
        if (0 <= l->_capacity) { l->_count = 0; } else { List_Resize(l, 0, 4); }
        result->v = g_resultSuccess.v;
        return;
    }
    for (i = 0; i < n; i++) {
        if (data[0] == 0) {
            cnt = cnt + 1;
            if (cnt == count) {
                t = i + 1;
                if (t >= 0) {
                    if (t <= l->_capacity) { l->_count = t; } else { List_Resize(l, t, 4); }
                }
                result->v = g_resultSuccess.v;
                return;
            }
        }
    }
    result->v = g_resultFailure.v;
}

unsigned int *Gap__Core__igCallStackTable__vfunc_25(igCallStackTableView *table, int offset) {
unsigned int *r; if (offset < 0 || offset >= table->_callStacks->_count || table->_callStacks->_data == 0) { r = 0; } else { r = table->_callStacks->_data + offset; if (offset > 0 && r[-1] != 0) r = 0; } return r;
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

void Gap__Core__igCallStackTable__vfunc_27(igCallStackTableView *table, int *stack) {
    switch (table->findCallStack((unsigned int *)stack)) {
    case -1: table->addCallStack(stack); break;
    default: break;
    }
}

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
    while (*a && *b && *a == *b) {
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
    s = self->words->data;
    end = self->words->data + self->words->count;
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

void Gap__Core__igCallStackTable__vfunc_31(igCallStackTableView *self, int arg1)
{
    Ref *r;
    int cnt;
    igTDataList<int> *l;
    unsigned *var_a1_2;
    unsigned *data;
    int var_a0;
    igTDataList<int> *v;
    unsigned *temp_s2;
    int var_a1;
    unsigned *temp_s1_2;
    unsigned *var_s0;
    int temp_s1;

    FUN_002d38e0(self, arg1);
    if (arg1 != 0) {
        if (self->_hashIndex == 0) {
            temp_s1 = ((int)igObject_GetAllocator((int)self));
            r = (Ref *)self->_hashIndex;
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->_hashIndex = (igTDataList<int> *)FUN_002ca8b0(temp_s1);
        }
        l = self->_hashIndex;
        if (arg1 >= l->_count) List_Reserve((L_2d6680 *)l, arg1, 4);
        l = self->_hashIndex;
        if (arg1 >= 0) {
            if (arg1 <= l->_capacity) l->_count = arg1;
            else List_Resize(l, arg1, 4);
        }
        v = self->_hashIndex;
        cnt = v->_count;
        data = (unsigned *)v->_data;
        for (var_a1 = 0; var_a1 < cnt; var_a1++) data[var_a1] = *(unsigned *)DAT_004c1e98;
        temp_s2 = self->_callStacks->_data;
        var_s0 = temp_s2;
        temp_s1_2 = temp_s2 + self->_callStacks->_count;
        while (var_s0 < temp_s1_2) {
            if (!self->vfunc_30(var_s0, var_s0 - temp_s2)) return;
            var_a1_2 = var_s0;
            var_a0 = 0;
            while (*var_a1_2++ != 0) var_a0++;
            var_s0 += var_a0 + 1;
        }
    } else {
        r = (Ref *)self->_hashIndex;
        if (r != 0) {
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->_hashIndex = 0;
        }
    }
}

