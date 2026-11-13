int Gap__Core__igDataList__vfunc_23(void) {
    return -1;
}

void List_Reserve(L_2d6680 *arg0, int arg1, int arg2) {
    int sp7C;
    if (arg1 == 0) {
        FUN_00300f50((int)arg0, arg0->f10);
        arg0->f10 = 0;
    } else {
        int s1 = arg0->f10;
        Fld_2d6680 *fld = (Fld_2d6680 *)igMetaObject_GetFieldAt((igMetaObject *)(arg0->v88()), DAT_005867a0[0]->f18);
        unsigned s5 = (unsigned)(arg1 * arg2) / (unsigned)(fld->f60->v100() & 0xFFFF);
        igMetaField_AllocateArray(&sp7C, (igMemoryRefMetaField *)fld, (void *)arg0, s5, (AlignedAllocatorView *)(((int)igObject_GetAllocator((int)arg0))));
        if (s1 != 0) {
            int v = arg0->fc;
            int n = (v < arg1) ? v : arg1;
            memcpy(arg0->f10, s1, n * arg2);
            FUN_00300f50((int)arg0, s1);
        }
    }
    arg0->fc = arg1;
}

int List_Resize(void *list, int count, int extra2)
{
    int capacity = ((igDataList *)list)->_capacity > 4 ? ((igDataList *)list)->_capacity : 4;
    while (capacity < count) {
        capacity = capacity < 1024 ? capacity * 2 : capacity + 1024;
    }
    List_Reserve((L_2d6680 *)((igDataList *)list), capacity, extra2);
    ((igDataList *)list)->_count = count;
}

static inline int countOf(const L_2d6900 *list) { return list->n; }

extern "C" void List_InsertBytes(L_2d6900 *list, int index, int count, int src, int stride) {
    int oldCount;
    int newCount;
    int at;
    int dst;
    int tail;
    if (index < 0 || index > countOf(list)) {
        return;
    }
    if (count >= 0 && count != 0) {
        oldCount = list->n;
        newCount = oldCount + count;
        if (newCount <= list->cap) { list->n = newCount; } else { List_Resize((void *)list, newCount, stride); }
        at = list->data + index * stride;
        count *= stride;
        dst = at + count;
        tail = oldCount - index;
        if (tail != 0) {
            memmove(dst, at, tail * stride);
        }
        memcpy(at, src, count);
    }
}

void List_AppendBytes(L_2d6900 *l, int cnt, int src, int sz) {
    int old;
    int nn;
    if (cnt >= 0 && cnt != 0) {
        old = l->n;
        nn = old + cnt;
        if (nn <= l->cap) { l->n = nn; } else { List_Resize((void *)l, nn, sz); }
        memcpy(l->data + old * sz, src, cnt * sz);
    }
}

void List_RemoveAt(L_2d69a0 *l, int i, int sz) {
    int n = l->n; int d;
 if (n <= 0 || i < 0 || i >= n) return; if (i != n - 1) { d = l->data + i * sz; memmove(d, d + sz, sz * (n - (i + 1)), n); } l->n = l->n - 1;
}

int List_BinarySearch(struct LL *arg0, int arg1, int (*arg2)(int, int), int arg3) {
    int lo = 0;
    int hi = arg0->count - 1;
    int mid;
    int r;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        r = arg2(arg0->data + arg3 * mid, arg1);
        if (r < 0) {
            lo = mid + 1;
        } else if (r > 0) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (arg0->count == 0) {
        return -1;
    }
    if (arg2(arg0->data + arg3 * lo, arg1) == 0) {
        return lo;
    }
    return -1;
}

