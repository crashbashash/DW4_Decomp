int igDataList_GetElementSize(void) {
    return -1;
}

void List_Reserve(igDataList *list, int capacity, int elementSize) {
    int sp7C;
    if (capacity == 0) {
        igObject_FreeMemory((int)list, list->_data);
        list->_data = 0;
    } else {
        int s1 = list->_data;
        igMemoryRefMetaField *field = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(((igObjectDispatchView *)list)->getMeta(), DAT_005867a0[0]->_internalIndex);
        unsigned s5 = (unsigned)(capacity * elementSize) / (unsigned)(((igMetaFieldView *)field->_memType)->GetSize() & 0xFFFF);
        igMetaField_AllocateArray(&sp7C, field, (void *)list, s5, (igMemoryPoolView *)(((int)igObject_GetAllocator((int)list))));
        if (s1 != 0) {
            int v = list->_capacity;
            int n = (v < capacity) ? v : capacity;
            memcpy(list->_data, s1, n * elementSize);
            igObject_FreeMemory((int)list, s1);
        }
    }
    list->_capacity = capacity;
}

int List_Resize(void *list, int count, int extra2)
{
    int capacity = ((igDataList *)list)->_capacity > 4 ? ((igDataList *)list)->_capacity : 4;
    while (capacity < count) {
        capacity = capacity < 1024 ? capacity * 2 : capacity + 1024;
    }
    List_Reserve(((igDataList *)list), capacity, extra2);
    ((igDataList *)list)->_count = count;
}

static inline int countOf(const igDataList *list) { return list->_count; }

extern "C" void List_InsertBytes(igDataList *list, int index, int count, int src, int stride) {
    int oldCount;
    int newCount;
    int at;
    int dst;
    int tail;
    if (index < 0 || index > countOf(list)) {
        return;
    }
    if (count >= 0 && count != 0) {
        oldCount = list->_count;
        newCount = oldCount + count;
        if (newCount <= list->_capacity) { list->_count = newCount; } else { List_Resize((void *)list, newCount, stride); }
        at = list->_data + index * stride;
        count *= stride;
        dst = at + count;
        tail = oldCount - index;
        if (tail != 0) {
            memmove(dst, at, tail * stride);
        }
        memcpy(at, src, count);
    }
}

void List_AppendBytes(igDataList *l, int cnt, int src, int sz) {
    int old;
    int nn;
    if (cnt >= 0 && cnt != 0) {
        old = l->_count;
        nn = old + cnt;
        if (nn <= l->_capacity) { l->_count = nn; } else { List_Resize((void *)l, nn, sz); }
        memcpy(l->_data + old * sz, src, cnt * sz);
    }
}

void List_RemoveAt(igDataList *l, int i, int sz) {
    int n = l->_count; int d;
 if (n <= 0 || i < 0 || i >= n) return; if (i != n - 1) { d = l->_data + i * sz; memmove(d, d + sz, sz * (n - (i + 1)), n); } l->_count = l->_count - 1;
}

int List_BinarySearch(igDataList *arg0, int arg1, int (*arg2)(int, int), int arg3) {
    int lo = 0;
    int hi = arg0->_count - 1;
    int mid;
    int r;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        r = arg2(arg0->_data + arg3 * mid, arg1);
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
    if (arg2(arg0->_data + arg3 * lo, arg1) == 0) {
        return lo;
    }
    return -1;
}

