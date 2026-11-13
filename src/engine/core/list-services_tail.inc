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

void ObjectList_ResizeRetained(L_301ee0 *arg0, int arg1) {
    int n;
    int j;
    int k;
    R_301ee0 *t;
    n = arg0->cnt;
    if (arg1 <= n) {
        for (j = arg1; j < n; j++) {
            t = arg0->data[j];
            if (t != 0) {
                t->f4 = t->f4 - 1;
                if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        for (k = arg1; k < n; k++) {
            arg0->data[k] = 0;
        }
        arg0->cnt = arg1;
        return;
    }
    if (arg1 >= 0) {
        if (arg1 <= arg0->cap) {
            arg0->cnt = arg1;
        } else {
            List_Resize(arg0, arg1, 4);
        }
    }
    memset((char *)arg0->data + n * 4, 0, (arg1 - n) * 4);
}

static inline int find(ObjectListView *l, ObjectListItem **vp, int i) {
    int n = l->count;
    ObjectListItem *v = *vp;
    for (; i < n; i++) {
        if (v == l->data[i]) {
            return i;
        }
    }
    return -1;
}

static inline void release_302000(ObjectListItem *o) { if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } } }

igResult ObjectList_RemoveFirstRetained(ObjectListView *self, ObjectListItem *value, int start, int extra3) {
    ObjectListItem *v;
    int i;
    *(ObjectListItem **)&v = value;
    i = find(self, &v, start);
    if (i >= 0) {
        ObjectListItem *o = self->data[i];
        unsigned int k = i;
        if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } }
        List_RemoveWordAt((L_2d6cf0 *)self, k);
        self->data[self->count] = 0;
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
        List_RemoveWordAt((L_2d6cf0 *)list, i);
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

int igProperty_FindByName(struct L_3022c0 *arg0, struct P_3022c0 *arg1, int arg2) {
    int temp_a0;
    int var_s2;
    int temp_s1;
    int temp_s0;
    if ((arg1 == 0) || (arg2 == 0)) {
        return 0;
    }
    temp_s1 = arg0->n;
    for (var_s2 = 0; var_s2 < temp_s1; var_s2++) {
        temp_s0 = arg0->arr[var_s2];
        temp_a0 = *(int *)(temp_s0 + arg1->off);
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

static inline void retain_302540(Obj_302540 *o) { if (o != 0) { o->_refCount = o->_refCount + 1; } }

static inline void release_302540(Obj_302540 *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
}

static inline void setAt_302540(L_302540 *l, int i, Obj_302540 *v, int off) {
    int n = l->count;
    if (n != 0 && i >= 0 && i < n) {
        *(Obj_302540 **)((char *)l->data + off) = v;
    }
}

static inline void setPrev(L_302540 *l, int i, Obj_302540 *v, int off) {
    int n = l->count;
    if (n != 0 && i >= 0 && i < n) {
        ((Obj_302540 **)((char *)l->data + off))[-1] = v;
    }
}

void FUN_00302540(L_302540 *self, Field *field) {
int i; int n; Obj_302540 *a; Obj_302540 *b; int off; int swapped; unsigned int prev; unsigned int cur; Obj_302540 **p;

    if (field == 0) {
        return;
    }
    n = self->count;
    swapped = 1;
    if (n < 2) { return; }
    while (swapped > 0) {
        swapped = 0;
        prev = *(unsigned int *)((char *)self->data[0] + field->_offset);
        for (i = 1; i < n; i++) {
            off = i * 4;
            p = (Obj_302540 **)((char *)self->data + off);
            b = p[0];
            cur = *(unsigned int *)((char *)b + field->_offset);
            if (cur < prev) {
                a = p[-1];
                retain_302540(a);
                release_302540(*(Obj_302540 **)((char *)self->data + off));
                setAt_302540(self, i, a, off);
                retain_302540(b);
                release_302540(*(Obj_302540 **)((char *)self->data + off - 4));
                setPrev(self, i - 1, b, off);
                swapped = 1;
            } 
            prev = cur;
        }
    }
}

