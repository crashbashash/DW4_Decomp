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

void ObjectList_ResizeRetained(igTDataList<igObject *> *self, int count) {
    int n;
    int j;
    int k;
    igObject *t;
    n = self->_count;
    if (count <= n) {
        for (j = count; j < n; j++) {
            t = self->_data[j];
            if (t != 0) {
                t->_refCount = t->_refCount - 1;
                if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        for (k = count; k < n; k++) {
            self->_data[k] = 0;
        }
        self->_count = count;
        return;
    }
    if (count >= 0) {
        if (count <= self->_capacity) {
            self->_count = count;
        } else {
            List_Resize(self, count, 4);
        }
    }
    memset((char *)self->_data + n * 4, 0, (count - n) * 4);
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

int igProperty_FindByName(igObjectList *list, igMetaField *field, int name) {
    int text;
    int i;
    int count;
    int item;
    if ((field == 0) || (name == 0)) {
        return 0;
    }
    count = list->_count;
    for (i = 0; i < count; i++) {
        item = ((int *)list->_data)[i];
        text = *(int *)(item + field->_offset);
        if ((text != 0) && (strcmp(text, name) == 0)) {
            return item;
        }
    }
    return 0;
}

int igProperty_FindByPointer(void *listObject, void *fieldObject, int key) {
    igObjectList *list = (igObjectList *)listObject;
    igMetaField *field = (igMetaField *)fieldObject;
    int item;
    int i;
    int n;

    n = list->_count;
    if (field == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        item = *(int *)(list->_data + (i * 4));
        if (item != 0) {
            int value = *(int *)(item + field->_offset);
            if (value == key) {
                return item;
            }
        }
    }
    return 0;
}

int igProperty_FindBySortedKey(void *listObject, void *fieldObject, int key) {
    igObjectList *list = (igObjectList *)listObject;
    igMetaField *field = (igMetaField *)fieldObject;
    int index;
    int item;
    int value;
    if (field == 0) {
        return 0;
    }
    index = igProperty_FindInsertionIndex((void *)list, (void *)field, (unsigned int)key);
    if (index >= list->_count) {
        return 0;
    }
    item = *(int *)(list->_data + (index * 4));
    value = *(int *)(item + field->_offset);
    if (value != key) {
        return 0;
    }
    return item;
}

int igProperty_FindInsertionIndex(void *listObject, void *fieldObject, unsigned int target) {
    igObjectList *list = (igObjectList *)listObject;
    igMetaField *field = (igMetaField *)fieldObject;
    int n;
    int lo;
    int hi;
    int mid;
    unsigned int key;
    int item;
    if (field == 0) {
        return -1;
    }
    n = list->_count;
    if (n <= 0) {
        return 0;
    }
    hi = n - 1;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        item = *(int *)(list->_data + (mid * 4));
        key = *(unsigned int *)(item + field->_offset);
        if (key < target) {
            lo = mid + 1;
        } else if (target < key) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    item = *(int *)(list->_data + (lo * 4));
    if (*(unsigned int *)(item + field->_offset) < target) {
        return lo + 1;
    }
    return lo;
}

static inline void sortRetain(igObject *o) { if (o != 0) { o->_refCount = (int)o->_refCount + 1; } }

static inline void sortRelease(igObject *o) {
    IG_OBJECT_RELEASE(o);
}

static inline void sortSetAt(igTDataList<igObject *> *l, int i, igObject *v, int off) {
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
                sortRetain(a);
                sortRelease(*(igObject **)((char *)self->_data + off));
                sortSetAt(self, i, a, off);
                sortRetain(b);
                sortRelease(*(igObject **)((char *)self->_data + off - 4));
                setPrev(self, i - 1, b, off);
                swapped = 1;
            } 
            prev = cur;
        }
    }
}

