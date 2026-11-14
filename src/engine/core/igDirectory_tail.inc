void List_RemoveWordAt(igDataList *l, int i) {
    int n = l->_count; int d;
    if (n <= 0 || i < 0 || i >= n) return;
    if (i != n - 1) { d = l->_data + i * 4; memmove(d, d + 4, 4 * (n - (i + 1))); }
    l->_count = l->_count - 1; }

int List_BinarySearchWords(igDataList *arg0, int arg1, int (*arg2)(int, int)) {
    int lo = 0;
    int hi = arg0->_count - 1;
    int mid;
    int r;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        r = arg2(arg0->_data + mid * 4, arg1);
        if (r < 0) {
            lo = mid + 1;
        } else if (r > 0) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (arg0->_count == 0) {
        return -1;
    }
    if (arg2(arg0->_data + lo * 4, arg1) == 0) {
        return lo;
    }
    return -1;
}

int FUN_002d6e60(igDataList *l, void *key, Cmp cmp) {
    int lo = 0; int hi = l->_count - 1; int mid; int r;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        r = cmp((int *)l->_data + mid, key);
        if (r < 0) lo = mid + 1; else if (r > 0) hi = mid - 1; else return mid;
    }
    if (l->_count == 0) return 0;
    if (cmp((int *)l->_data + lo, key) < 0) lo++;
    return lo;
}

static inline int count_of(const igDependencyListView *list) { return list->_count; }

void FUN_002d7090(igDependencyOrderedListView *arg0, int arg1, int arg2) {
    int n; igDependencyListView *q; DependencyPair *it;
    q = arg0->_dependencies;
    n = q->_count;
    if (n < q->_capacity) {
        q->_count = count_of(q) + 1;
    } else {
        List_Resize(q, n + 1, 8);
    }
    it = (DependencyPair *)((char *)q->_data + n * 8);
    it->a = arg1;
    it->b = arg2;
    FUN_002d7280(arg0);
    FUN_002d7130(arg0);
}

void FUN_002d7130(igDependencyOrderedListView *owner) {
    igSmartPointer<ObjectList> copy(((ObjectList *)FUN_002bd680(((int)igObject_GetAllocator((int)owner)))));
    ObjectList_AppendRetainedList((int)copy.p, (igTDataList<igObject *> *)owner->_objectList);
    ObjectList *children = owner->_objectList;
    int count = children->count;
    int i;
    for (i = 0; i < count; i++) {
        igObject *child = children->data[i];
        if (child != 0) {
            child->_refCount = child->_refCount - 1;
            if ((child->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(child);
            }
        }
    }
    int end = children->count;
    int j;
    for (j = 0; j < end; j++) {
        children->data[j] = 0;
    }
    children->count = 0;
    for (i = 0; i < copy->count; i++) {
        igRendererOrderedList_Append(owner, copy->data[i], 0);
    }
}

void igRendererOrderedList_Clear(char *arg0) {
    ObjectList *l;
    int n;
    int i;
    igObject *t;
    l = *(ObjectList **)(arg0 + 8);
    n = l->count;
    for (i = 0; i < n; i++) {
        t = l->data[i];
        if (t != 0) {
            t->_refCount = (int)((int) (t->_refCount - 1));
            if (((unsigned long long) ((long long)(int) t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
}

void FUN_002d7760(int *arg0, igDependencyOrderedListView *arg1, int arg2, int arg3) {
    igDependencyListView *temp_a0 = arg1->_dependencies;
    int idx = temp_a0->Find(arg2, arg3);
    int var_s2;
    if (idx >= 0) {
        List_RemoveAt((igDataList *)temp_a0, idx, 8);
        var_s2 = g_resultSuccess.v;
    } else {
        var_s2 = g_resultFailure.v;
    }
    if (arg1->_hasCircularDependencies != 0) {
        FUN_002d7280(arg1);
        FUN_002d7130(arg1);
    }
    *arg0 = var_s2;
}

void FUN_002d7840(igDependencyOrderedListView *arg0, int arg1) {
    int var_s0;
    igDependencyListView *temp_a0;
    int *temp_v1;
    int a, b;

    for (var_s0 = arg0->_dependencies->_count - 1; var_s0 >= 0; var_s0--) {
        temp_a0 = arg0->_dependencies;
        temp_v1 = (int *)&temp_a0->_data[var_s0];
        b = temp_v1[1];
        a = temp_v1[0];
        if ((a == arg1) || (b == arg1)) {
            List_RemoveAt((igDataList *)temp_a0, var_s0, 8);
        }
    }
    if (arg0->_hasCircularDependencies != 0) {
        FUN_002d7280(arg0);
        FUN_002d7130(arg0);
    }
}

void FUN_002d78e0(void *arg0, int arg1) {
    void *sp3C;
    int *temp_a1;
    int temp_v1;
    int var_v0_2;
    void *var_v0;

    if (arg1 == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = ((int)StringPool_Allocate(0x10));
            if (var_v0_2 != 0) {
                var_v0_2 = ((int)StringPool_Construct((StringPool *)var_v0_2));
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1));
    }
    sp3C = (void *)(var_v0);
    StringList_AppendRetained(*(int *)((char *)(arg0) + 20), &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v1 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
}

