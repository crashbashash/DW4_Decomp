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
    table->RebuildHashIndex(table->_hashCapacity);
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

    discarded = table->TruncateCallStacks(0);
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
        self->InsertHashEntry(self->_callStacks->_data + offset, offset);
    }
    return offset;
}

void igCallStackTable_InsertCallStack(igCallStackTableView *table, int *stack) {
    switch (table->FindCallStack((unsigned int *)stack)) {
    case -1: table->AddCallStack(stack); break;
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
        slot = self->HashCallStack(stack);
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
        h = self->HashCallStack(stack);
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
        self->RebuildHashIndex(n * 2);
        return 0;
    }
ok:
    return 1;
}

int g_igCallStackTable_emptyHashSlot[] = { -1 };

void igCallStackTable_RebuildHashIndex(igCallStackTableView *self, int hashCapacity)
{
    igObject *r;
    int cnt;
    igTDataList<int> *l;
    unsigned *cursor;
    unsigned *data;
    int length;
    igTDataList<int> *hashIndex;
    unsigned *stacks;
    int i;
    unsigned *stacksEnd;
    unsigned *stack;
    int allocator;

    igCallStackTable_SetHashCapacity(self, hashCapacity);
    if (hashCapacity != 0) {
        if (self->_hashIndex == 0) {
            allocator = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
            r = (igObject *)self->_hashIndex;
            if (r != 0) {
                ((igRefCountWord *)&r->_refCount)->word = ((igRefCountWord *)&r->_refCount)->word - 1;
                if (((igRefCountWord *)&r->_refCount)->bits.count == 0) igObject_Destroy(r);
            }
            self->_hashIndex = (igTDataList<int> *)igIntListNoClean_Create(allocator);
        }
        l = self->_hashIndex;
        if (hashCapacity >= l->_count) List_Reserve((igDataList *)l, hashCapacity, 4);
        l = self->_hashIndex;
        if (hashCapacity >= 0) {
            if (hashCapacity <= l->_capacity) l->_count = hashCapacity;
            else List_Resize(l, hashCapacity, 4);
        }
        hashIndex = self->_hashIndex;
        cnt = hashIndex->_count;
        data = (unsigned *)hashIndex->_data;
        for (i = 0; i < cnt; i++) data[i] = *(unsigned *)g_igCallStackTable_emptyHashSlot;
        stacks = self->_callStacks->_data;
        stack = stacks;
        stacksEnd = stacks + self->_callStacks->_count;
        while (stack < stacksEnd) {
            if (!self->InsertHashEntry(stack, stack - stacks)) return;
            cursor = stack;
            length = 0;
            while (*cursor++ != 0) length++;
            stack += length + 1;
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

