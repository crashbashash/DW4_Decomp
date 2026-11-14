void igCallStackTable_SetHashCapacity(igCallStackTableView *table, int hashCapacity)
{
    table->_hashCapacity = hashCapacity;
}

void igCallStackTable_ApplyCapacity(igCallStackTableView *table) {
    int capacity;
    igTDataList<unsigned int> *callStacks;

    capacity = table->_capacity;
    callStacks = table->_callStacks;
    if (capacity >= callStacks->_count) {
        List_Reserve((igDataList *)callStacks, capacity, 4);
    }
    table->vfunc_31(table->_hashCapacity);
}

void igCallStackTable_Clear(igCallStackTableView *table) {
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
        List_Reserve((igDataList *)callStacks2, 0, 4);
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
        List_Reserve((igDataList *)hashIndex3, 0, 4);
    }
    }
}

void igCallStackTable_RemoveAllCallStacks(igCallStackTableView *table) {
    igResult discarded;

    discarded = table->vfunc_24(0);
}

int igCallStackTable_GetCallStackCount(igCallStackTableView *table) {
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

void igCallStackTable_TruncateCallStacks(igResult *result, igCallStackTableView *table, int count) {
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

unsigned int *igCallStackTable_GetCallStack(igCallStackTableView *table, int offset) {
unsigned int *r; if (offset < 0 || offset >= table->_callStacks->_count || table->_callStacks->_data == 0) { r = 0; } else { r = table->_callStacks->_data + offset; if (offset > 0 && r[-1] != 0) r = 0; } return r;
}

/* Grows the packed call stacks to twice their capacity once n words no longer fit. */
static inline void reserveCallStackWords(const igTDataList<unsigned int> *words, int n) {
    int grown = words->_capacity * 2;
    if (words->_capacity < n) {
        if (!(grown < words->_count)) {
            List_Reserve((igDataList *)words, grown, 4);
        }
    }
}
/* Number of return addresses before the terminating zero. */
static inline int callStackDepth(const int *stack) {
    int depth = 0;
    while (*stack++ != 0) {
        depth++;
    }
    return depth;
}
/* Appends a zero-terminated call stack to the word list and returns its word offset. */
extern "C" int Gap__Core__igCallStackTable__addCallStack(igCallStackTableView *self, int *stack) {
    int length;
    int offset;
    length = callStackDepth(stack) + 1;
    reserveCallStackWords(self->_callStacks, length + (offset = self->_callStacks->_count));
    List_AppendWords((igDataList *)self->_callStacks, length, stack);
    if (self->_hashIndex != 0 && self->_hashIndex->_count != 0) {
        self->vfunc_30(self->_callStacks->_data + offset, offset);
    }
    return offset;
}

void igCallStackTable_InsertCallStack(igCallStackTableView *table, int *stack) {
    switch (table->findCallStack((unsigned int *)stack)) {
    case -1: table->addCallStack(stack); break;
    default: break;
    }
}

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
extern "C" int Gap__Core__igCallStackTable__findCallStack(igCallStackTableView *self, unsigned int *stack) {
    igTDataList<int> *index;
    int slot;
    int offset;
    int n;
    int tries;
    unsigned int *s;
    unsigned int *end;

    index = self->_hashIndex;
    if (index != 0 && index->_count != 0) {
        slot = self->vfunc_29(stack);
        tries = 0;
        n = self->_hashIndex->_count;
        for (;;) {
            offset = self->_hashIndex->_data[slot];
            if (offset == -1) {
                return -1;
            }
            if (compareCallStacks(self->_callStacks->_data + offset, stack) == 0) {
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
    s = self->_callStacks->_data;
    end = self->_callStacks->_data + self->_callStacks->_count;
    while (s < end) {
        if (compareCallStacks(stack, s) == 0) {
            return s - self->_callStacks->_data;
        }
        s += callStackDepth(s) + 1;
    }
    return -1;
}

unsigned int igCallStackTable_HashCallStack(igCallStackTableView *self, unsigned int *stack) {
    igTDataList<int> *t = self->_hashIndex;
    unsigned int sum = 0;
    unsigned int n;
    unsigned int v;
    unsigned int r;
    if (t != 0) { n = t->_count; } else { n = 0; }
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

int igCallStackTable_InsertHashEntry(igCallStackTableView *self, unsigned int *stack, int offset) {
    int tries = 0;
    int n = self->_hashIndex->_count;
    int half = n / 2;
    int h;
    igTDataList<int> *index;
    if (n != 0) {
        h = self->vfunc_29(stack);
        index = self->_hashIndex;
        do {
            if (index->_data[h] == -1) {
                igIntList_SetChecked((igIntList *)index, h, offset);
                goto ok;
            }
            h++;
            if (h >= n) {
                h = 0;
            }
            tries++;
        } while (tries < half);
        self->vfunc_31(n * 2);
        return 0;
    }
ok:
    return 1;
}

void igCallStackTable_RebuildHashIndex(igCallStackTableView *self, int arg1)
{
    igObject *r;
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

    igCallStackTable_SetHashCapacity(self, arg1);
    if (arg1 != 0) {
        if (self->_hashIndex == 0) {
            temp_s1 = ((int)igObject_GetAllocator((int)self));
            r = (igObject *)self->_hashIndex;
            if (r != 0) {
                ((igRefCountWord *)&r->_refCount)->word = ((igRefCountWord *)&r->_refCount)->word - 1;
                if (((igRefCountWord *)&r->_refCount)->bits.count == 0) igObject_Destroy(r);
            }
            self->_hashIndex = (igTDataList<int> *)igIntListNoClean_Create(temp_s1);
        }
        l = self->_hashIndex;
        if (arg1 >= l->_count) List_Reserve((igDataList *)l, arg1, 4);
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
        r = (igObject *)self->_hashIndex;
        if (r != 0) {
            if (r != 0) {
                ((igRefCountWord *)&r->_refCount)->word = ((igRefCountWord *)&r->_refCount)->word - 1;
                if (((igRefCountWord *)&r->_refCount)->bits.count == 0) igObject_Destroy(r);
            }
            self->_hashIndex = 0;
        }
    }
}

