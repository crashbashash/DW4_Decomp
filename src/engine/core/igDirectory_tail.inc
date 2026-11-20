void List_RemoveWordAt(igDataList *l, int i) {
    int n = l->_count; int d;
    if (n <= 0 || i < 0 || i >= n) return;
    if (i != n - 1) { d = l->_data + i * 4; memmove((void *)d, (void *)(d + 4), 4 * (n - (i + 1))); }
    l->_count = l->_count - 1; }

int List_BinarySearchWords(igDataList *list, int key, int (*compare)(int, int)) {
    int lo = 0;
    int hi = list->_count - 1;
    int mid;
    int r;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        r = compare(list->_data + mid * 4, key);
        if (r < 0) {
            lo = mid + 1;
        } else if (r > 0) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (list->_count == 0) {
        return -1;
    }
    if (compare(list->_data + lo * 4, key) == 0) {
        return lo;
    }
    return -1;
}

int List_LowerBound(igDataList *l, void *key, Cmp cmp) {
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

typedef igSmartPointer<igTDataList<igObject *> > igObjectListRef;

/* Index of object in list, or -1. */
static inline int indexOfObject(const igTDataList<igObject *> *list, igObject *object) {
    int i;
    for (i = 0; i < list->_count; i++) {
        if (object == list->_data[i]) {
            return i;
        }
    }
    return -1;
}

/* Inserts object at index, holding a reference to it. */
static inline void insertRetained(igTDataList<igObject *> *list, int index, igObject *object) {
    if (object != 0) {
        object->_refCount++;
    }
    List_InsertWords((igDataList *)list, index, 1, &object);
}

/* Adds object to the list, in front of the first listed object that the order ranks after it. An
 * object the order does not rank goes at the end, and with `unique` set one already listed is left
 * alone. */
void igRendererOrderedList_Append(igDependencyOrderedList *list, igObject *object, int unique) {
    igDependencyOrderedListView *self = (igDependencyOrderedListView *)list;
    int rank = indexOfObject(self->_order, object);
    if (rank < 0) {
        if (unique != 0) {
            ObjectList_AppendUniqueRetained(self->_objectList, object);
        } else {
            ObjectList_AppendRetained((igObjectList *)self->_objectList, object);
        }
        return;
    }
    int j = 0;
    for (int i = 0; i < ((igObjectListRef &)self->_objectList)->count(); i++) {
        igObject *listed = ((igObjectListRef &)self->_objectList)->get(i);
        if (unique != 0 && listed == object) {
            return;
        }
        while (j < rank && listed != self->_order->_data[j]) {
            j++;
        }
        if (!(j < rank)) {
            insertRetained(self->_objectList, i, object);
            return;
        }
    }
    ObjectList_AppendRetained((igObjectList *)((igObjectListRef &)self->_objectList).get(), object);
}

static inline int count_of(const igTDataList<DependencyPair> *list) { return list->_count; }

/* Index of the dependency (k1, k2), or -1. */
static inline int findDependency(igTDataList<DependencyPair> *list, void *k1, void *k2) { int i; for (i = 0; i < list->_count; i++) { DependencyPair *p = &list->_data[i]; int v = (k1 == p->a); if (v) { v = (k2 == p->b); } if (v) { return i; } } return -1; }

void igDependencyOrderedList_AddDependency(igDependencyOrderedList *self, void *dependent, void *dependency) {
    int n; igTDataList<DependencyPair> *pairs; DependencyPair *pair;
    pairs = (igTDataList<DependencyPair> *)self->_dependencies;
    n = pairs->_count;
    if (n < pairs->_capacity) {
        pairs->_count = count_of(pairs) + 1;
    } else {
        List_Resize(pairs, n + 1, 8);
    }
    pair = (DependencyPair *)((char *)pairs->_data + n * 8);
    pair->a = dependent;
    pair->b = dependency;
    igDependencyOrderedList_TopologicalSort(self);
    igDependencyOrderedList_Rebuild((igDependencyOrderedListView *)self);
}

void igDependencyOrderedList_Rebuild(igDependencyOrderedListView *owner) {
    igSmartPointer<igObjectList> copy(((igObjectList *)igObjectList_Create(((int)((Gap::Core::igObject *)owner)->getMemoryPool()))));
    ObjectList_AppendRetainedList((igTDataList<igObject *> *)copy.p, owner->_objectList);
    igTDataList<igObject *> *children = owner->_objectList;
    int count = children->_count;
    int i;
    for (i = 0; i < count; i++) {
        igObject *child = children->_data[i];
        if (child != 0) {
            child->_refCount = child->_refCount - 1;
            if ((child->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(child);
            }
        }
    }
    int end = children->_count;
    int j;
    for (j = 0; j < end; j++) {
        children->_data[j] = 0;
    }
    children->_count = 0;
    for (i = 0; i < copy->_count; i++) {
        igRendererOrderedList_Append((igDependencyOrderedList *)owner, ((igObject **)copy->_data)[i], 0);
    }
}

void igRendererOrderedList_Clear(igDependencyOrderedList *self) {
    igTDataList<igObject *> *list;
    int n;
    int i;
    igObject *object;
    list = (igTDataList<igObject *> *)self->_objectList;
    n = list->_count;
    for (i = 0; i < n; i++) {
        object = list->_data[i];
        if (object != 0) {
            object->_refCount = (int)((int) (object->_refCount - 1));
            if (((unsigned long long) ((long long)(int) object->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    n = list->_count;
    for (i = 0; i < n; i++) {
        list->_data[i] = 0;
    }
    list->_count = 0;
}

igResult igObjectList_RemoveRetained(igDependencyOrderedList *list, igObject *object) {
    return ObjectList_RemoveFirstRetained(((igDependencyOrderedListView *)list)->_objectList, object, 0);
}

igResult igDependencyOrderedList_RemoveDependency(igDependencyOrderedList *list, void *dependent, void *dependency) {
    igDependencyOrderedListView *self = (igDependencyOrderedListView *)list;
    igTDataList<DependencyPair> *pairs = self->_dependencies;
    int idx = findDependency(pairs, dependent, dependency);
    int status;
    if (idx >= 0) {
        List_RemoveAt((igDataList *)pairs, idx, 8);
        status = g_resultSuccess.v;
    } else {
        status = g_resultFailure.v;
    }
    if (self->_hasCircularDependencies != 0) {
        igDependencyOrderedList_TopologicalSort(list);
        igDependencyOrderedList_Rebuild(self);
    }
    return igResult(status);
}

void igDependencyOrderedList_RemoveDependencies(igDependencyOrderedList *self, void *object) {
    int i;
    igTDataList<DependencyPair> *pairs;
    void **pair;
    void *a, *b;

    for (i = ((igTDataList<DependencyPair> *)self->_dependencies)->_count - 1; i >= 0; i--) {
        pairs = (igTDataList<DependencyPair> *)self->_dependencies;
        pair = (void **)&pairs->_data[i];
        b = pair[1];
        a = pair[0];
        if ((a == object) || (b == object)) {
            List_RemoveAt((igDataList *)pairs, i, 8);
        }
    }
    if (self->_hasCircularDependencies != 0) {
        igDependencyOrderedList_TopologicalSort(self);
        igDependencyOrderedList_Rebuild((igDependencyOrderedListView *)self);
    }
}

void igDependencyOrderedList_AddCheckPoint(igDependencyOrderedList *self, const char *name) {
    void *checkPoint;
    int *header;
    int references;
    int pool;
    void *interned;

    if (name == 0) {
        interned = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (void *)(StringPool_Intern((StringPool *)g_stringPool, name));
    }
    checkPoint = (void *)(interned);
    StringList_AppendRetained((igStringRefList *)(((igDependencyOrderedListView *)self)->_checkPoints), (char *const *)&checkPoint);
    if (checkPoint != 0) {
        header = (int *)((char *)checkPoint - 8);
        references = *(int *)((char *)(checkPoint) - 4) - 1;
        *(int *)((char *)(checkPoint) - 4) = references;
        if (references == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
}

