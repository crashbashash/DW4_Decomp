/* Retains the object (reference count +1), then appends it. Appends directly while capacity
 * remains, otherwise falls back to the generic word append. */
int ObjectList_AppendRetained(igObjectList *list, igObject *object) {
    int count;

    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    count = list->_count;
    if (count < list->_capacity) {
        list->_count = count + 1;
        (*(int **)&list->_data)[count] = (int)(object);
        return;
    }
    return List_AppendWord((igDataList *)list, (int)object);
}

/* Append every object of `source`, taking a reference on each. */
void ObjectList_AppendRetainedList(igTDataList<igObject *> *self, igTDataList<igObject *> *source) {
    igObject **data = source->_data;
    int count = source->_count;
    int i;
    igObject *object;
    for (i = 0; i < count; i++) {
        object = data[i];
        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
    }
    List_AppendWords((igDataList *)self, source->_count, (const int *)source->_data);
}

void ObjectList_ResizeRetained(igTDataList<igObject *> *arg0, int arg1) {
    int n;
    int j;
    int k;
    igObject *t;
    n = arg0->_count;
    if (arg1 <= n) {
        for (j = arg1; j < n; j++) {
            t = arg0->_data[j];
            if (t != 0) {
                t->_refCount = t->_refCount - 1;
                if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        for (k = arg1; k < n; k++) {
            arg0->_data[k] = 0;
        }
        arg0->_count = arg1;
        return;
    }
    if (arg1 >= 0) {
        if (arg1 <= arg0->_capacity) {
            arg0->_count = arg1;
        } else {
            List_Resize(arg0, arg1, 4);
        }
    }
    memset((char *)arg0->_data + n * 4, 0, (arg1 - n) * 4);
}

static inline int find(igTDataList<igObject *> *l, igObject **vp, int i) {
    int n = l->_count;
    igObject *v = *vp;
    for (; i < n; i++) {
        if (v == l->_data[i]) {
            return i;
        }
    }
    return -1;
}

igResult ObjectList_RemoveFirstRetained(igTDataList<igObject *> *self, igObject *value, int start) {
    igObject *v;
    int i;
    *(igObject **)&v = value;
    i = find(self, &v, start);
    if (i >= 0) {
        igObject *o = self->_data[i];
        unsigned int k = i;
        IG_OBJECT_RELEASE(o);
        List_RemoveWordAt((igDataList *)self, k);
        self->_data[self->_count] = 0;
        return g_resultSuccess;
    }
    return g_resultFailure;
}

int ObjectList_RemoveAllRetained(igTDataList<igObject *> *list, igObject *object, int start) {
    int removed = 0;
    int i = list->find(object, start);
    while (i >= 0) {
        igObject *element = list->_data[i];
        if (element != 0) {
            element->_refCount = element->_refCount - 1;
            if ((element->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(element);
            }
        }
        List_RemoveWordAt((igDataList *)list, i);
        list->_data[list->_count] = 0;
        removed++;
        i = list->find(object, i);
    }
    return removed;
}

int ObjectList_AppendUniqueRetained(igTDataList<igObject *> *list, igObject *object) {
    int index = list->find(object);
    if (index == -1) {
        index = list->count();
        ObjectList_AppendRetained((igObjectList *)list, object);
    }
    return index;
}

int igProperty_FindByName(igObjectList *arg0, igMetaField *arg1, int arg2) {
    int temp_a0;
    int var_s2;
    int temp_s1;
    int temp_s0;
    if ((arg1 == 0) || (arg2 == 0)) {
        return 0;
    }
    temp_s1 = arg0->_count;
    for (var_s2 = 0; var_s2 < temp_s1; var_s2++) {
        temp_s0 = ((int *)arg0->_data)[var_s2];
        temp_a0 = *(int *)(temp_s0 + arg1->_offset);
        if ((temp_a0 != 0) && (strcmp(temp_a0, arg2) == 0)) {
            return temp_s0;
        }
    }
    return 0;
}

int igProperty_FindByPointer(void *arg0, void *arg1, int arg2) {
    int temp_v0;
    int i;
    int n;

    n = *(int *)((char *)(arg0) + 8);
    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        temp_v0 = *(int *)(*(int *)((char *)(arg0) + 16) + (i * 4));
        if (temp_v0 != 0) {
            int w = *(int *)(temp_v0 + *(int *)((char *)(arg1) + 8));
            if (w == arg2) {
                return temp_v0;
            }
        }
    }
    return 0;
}

int igProperty_FindBySortedKey(void *arg0, void *arg1, int arg2) {
    int idx;
    int v;
    int t;
    if (arg1 == 0) {
        return 0;
    }
    idx = igProperty_FindInsertionIndex((void *)arg0, (void *)arg1, (unsigned int)arg2);
    if (idx >= *(int *)((char *)(arg0) + 8)) {
        return 0;
    }
    v = *(int *)(*(int *)((char *)(arg0) + 16) + (idx * 4));
    t = *(int *)(v + *(int *)((char *)(arg1) + 8));
    if (t != arg2) {
        return 0;
    }
    return v;
}

int igProperty_FindInsertionIndex(void *arg0, void *arg1, unsigned int arg2) {
    int n;
    int lo;
    int hi;
    int mid;
    unsigned int key;
    int e;
    if (arg1 == 0) {
        return -1;
    }
    n = *(int *)((char *)(arg0) + 8);
    if (n <= 0) {
        return 0;
    }
    hi = n - 1;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        e = *(int *)(*(int *)((char *)(arg0) + 16) + (mid * 4));
        key = *(unsigned int *)(e + *(int *)((char *)(arg1) + 8));
        if (key < arg2) {
            lo = mid + 1;
        } else if (arg2 < key) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    e = *(int *)(*(int *)((char *)(arg0) + 16) + (lo * 4));
    if (*(unsigned int *)(e + *(int *)((char *)(arg1) + 8)) < arg2) {
        return lo + 1;
    }
    return lo;
}

static inline void retain_302540(igObject *o) { if (o != 0) { o->_refCount = (int)o->_refCount + 1; } }

static inline void release_302540(igObject *o) {
    IG_OBJECT_RELEASE(o);
}

static inline void setAt_302540(igTDataList<igObject *> *l, int i, igObject *v, int off) {
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) {
        *(igObject **)((char *)l->_data + off) = v;
    }
}

static inline void setPrev(igTDataList<igObject *> *l, int i, igObject *v, int off) {
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) {
        ((igObject **)((char *)l->_data + off))[-1] = v;
    }
}

void igObjectList_SortByField(igTDataList<igObject *> *self, igMetaField *field) {
int i; int n; igObject *a; igObject *b; int off; int swapped; unsigned int prev; unsigned int cur; igObject **p;

    if (field == 0) {
        return;
    }
    n = self->_count;
    swapped = 1;
    if (n < 2) { return; }
    while (swapped > 0) {
        swapped = 0;
        prev = *(unsigned int *)((char *)self->_data[0] + field->_offset);
        for (i = 1; i < n; i++) {
            off = i * 4;
            p = (igObject **)((char *)self->_data + off);
            b = p[0];
            cur = *(unsigned int *)((char *)b + field->_offset);
            if (cur < prev) {
                a = p[-1];
                retain_302540(a);
                release_302540(*(igObject **)((char *)self->_data + off));
                setAt_302540(self, i, a, off);
                retain_302540(b);
                release_302540(*(igObject **)((char *)self->_data + off - 4));
                setPrev(self, i - 1, b, off);
                swapped = 1;
            } 
            prev = cur;
        }
    }
}

