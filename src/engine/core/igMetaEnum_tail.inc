/* not-found status */

int igMetaEnum_GetValueByName(int *status, igMetaEnum *meta, const char *name, int *value)
{
    int index;
    int match;
    int count;
    int retained;
    int *header;

    if ((NameList *)meta->_names) {
        count = ((NameList *)meta->_names)->count;
        for (index = 0; index < count; ++index) {
            StringList_CopyRetained(&retained, (void *)meta->_names, index);
            match = strcmp((const char *)retained, name) == 0;
            if (retained) {
                header = (int *)(retained - 8);
                if (--*(int *)(retained - 4) == 0) {
                    StringChunk_ReleaseHeader((StringChunkOwnerView *)(*header), (int)header);
                }
            }
            if (match) {
                *value = ((NameList *)meta->_values)->data[index];
                *status = g_resultSuccess.v;
                return;
            }
        }
    }
    *status = g_resultFailure.v;
}

void igMetaEnum_GetNameByValue(int *arg0, const struct E_2fbb40 *arg1, int arg2) {
    int i;
    int n;
    int a4;
    a4 = arg1->f12;
    if (a4 != 0) {
        n = arg1->f16->cnt;
        i = 0;
        goto test;
body:
        if (arg2 == arg1->f16->data[i]) {
            StringList_CopyRetained(arg0, a4, i);
            return;
        }
        i++;
test:
        if (i < n) goto body;
    }
    *arg0 = 0;
}

/* Number of names in the enum: the `_count` of its `_names` list (a list with the igDataList
 * header: _count +8, _capacity +12, _data +16). */

int igMetaEnum_GetNameCount(igMetaEnum *self) {
    return ((igDataList *)self->_names)->_count;
}

void igMetaEnum_GetNameAt(int *arg0, void *arg1, int arg2) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(arg1) + 12));
    if ((temp_a1 != 0) && (arg2 >= 0) && (arg2 < *(int *)((char *)(temp_a1) + 8))) {
        StringList_CopyRetained(arg0, temp_a1);
        return;
    }
    *arg0 = 0;
}

int igMetaEnum_GetValueAt(void *arg0, int arg1)
{
  int *new_var;
  void *temp_a0;
  temp_a0 = (void *) (*((int *) (((char *) arg0) + 16)));
  if (temp_a0 != 0)
  {
    if ((arg1 >= 0) && (arg1 < (*((int *) (((char *) temp_a0) + 8)))))
    {
      return *(new_var = (int *) ((*((int *) (((char *) temp_a0) + 16))) + (arg1 * 4)));
    }
  }
  return 0;
  return 0;
}

static inline int pool_2fbc70(void) {
    if ((*(int *)g_stringPool) == 0) {
        int p = ((int)StringPool_Allocate(0x10));
        if (p != 0) { p = ((int)StringPool_Construct((struct S_2eadf0 *)p)); }
        (*(int *)g_stringPool) = p;
    }
    return (*(int *)g_stringPool);
}

static inline void dropString(char *s) {
    if (s != 0) {
        int *hd = (int *)(s - 8);
        int rc = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = rc;
        if (rc == 0) { StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd), (int)hd); }
    }
}

static inline void dropNames_2fbc70(MetaEnumNameList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

static inline void dropValues(MetaEnumValueList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

static inline void setValue(MetaEnumValueList *l, int i, int *v) { if (l->count != 0 && i >= 0 && i < l->count) { l->data[i] = *v; } }

MetaEnumView *igMetaEnum_Create(char *name, char **names, int *values, int count) {
    MetaEnumView *e;
    int i;
    char *v;
    char *entry;
    char *held;
    char *old;
    MetaEnumNameList *nl;
    MetaEnumValueList *vl;
    int a;
    char **slot;
    e = ((MetaEnumView *)FUN_002befe0(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData))));
    v = ((char *)StringPool_Intern((StringPool *)(pool_2fbc70()), (const char *)name));
    old = e->name;
    dropString(old);
    e->name = v;
    a = ((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData));
    dropNames_2fbc70(e->names);
    e->names = ((MetaEnumNameList *)igStringRefList_Create(a));
    StringList_Resize((StringRefListView *)e->names, count);
    a = ((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData));
    dropValues(e->values);
    e->values = ((MetaEnumValueList *)igIntList_Create(a));
    vl = e->values;
    if (count >= 0) {
        if (!(count > vl->capacity)) {
            vl->count = count;
        } else {
            List_Resize((void *)vl, count, 4);
        }
    }
    for (i = 0; i < count; i++) {
        entry = names[i];
        if (entry == 0) {
            v = 0;
        } else {
            v = ((char *)StringPool_Intern((StringPool *)(pool_2fbc70()), (const char *)entry));
        }
        *(char **)&held = v;
        nl = e->names;
        if (nl->count != 0 && i >= 0 && i < nl->count) {
            slot = &nl->data[i];
            if (held != 0) { ((int *)held)[-1] = ((int *)held)[-1] + 1; }
            old = *slot;
            dropString(old);
            *slot = held;
        }
        dropString(held);
        setValue(e->values, i, &values[i]);
    }
    FUN_002d30b0((int *)((*(int *)g_objectSystem)), (int)e);
    e->_refCount = e->_refCount - 1;
    if (((unsigned long long)((long long)e->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(e); }
    return e;
}

