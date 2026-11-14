/* not-found status */

igResult igMetaEnum_GetValueByName(igMetaEnum *meta, const char *name, int *value)
{
    int index;
    int match;
    int count;
    int retained;
    int *header;

    if ((igTDataList<char *> *)meta->_names) {
        count = ((igTDataList<char *> *)meta->_names)->_count;
        for (index = 0; index < count; ++index) {
            StringList_CopyRetained(&retained, (void *)meta->_names, index);
            match = strcmp((const char *)retained, name) == 0;
            if (retained) {
                header = (int *)(retained - 8);
                if (--*(int *)(retained - 4) == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
                }
            }
            if (match) {
                *value = ((igTDataList<int> *)meta->_values)->_data[index];
                return g_resultSuccess;
            }
        }
    }
    return g_resultFailure;
}

void igMetaEnum_GetNameByValue(int *arg0, const igMetaEnum *arg1, int arg2) {
    int i;
    int n;
    int a4;
    a4 = arg1->_names;
    if (a4 != 0) {
        n = ((igIntList *)arg1->_values)->_count;
        i = 0;
        goto test;
body:
        if (arg2 == ((int *)((igIntList *)arg1->_values)->_data)[i]) {
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
        if (p != 0) { p = ((int)StringPool_Construct((StringPool *)p)); }
        (*(int *)g_stringPool) = p;
    }
    return (*(int *)g_stringPool);
}

static inline void dropNames_2fbc70(igTDataList<char *> *o) {
    IG_OBJECT_RELEASE(o);
}

static inline void dropValues(igTDataList<int> *o) {
    IG_OBJECT_RELEASE(o);
}

static inline void setValue(igTDataList<int> *l, int i, int *v) { if (l->_count != 0 && i >= 0 && i < l->_count) { l->_data[i] = *v; } }

MetaEnumView *igMetaEnum_Create(char *name, char **names, int *values, int count) {
    MetaEnumView *e;
    int i;
    char *v;
    char *entry;
    char *held;
    char *old;
    igTDataList<char *> *nl;
    igTDataList<int> *vl;
    int a;
    char **slot;
    e = ((MetaEnumView *)igMetaEnum_CreateInstance(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
    v = ((char *)StringPool_Intern((StringPool *)(pool_2fbc70()), (const char *)name));
    old = e->name;
    releaseString(old);
    e->name = v;
    a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    dropNames_2fbc70(e->names);
    e->names = ((igTDataList<char *> *)igStringRefList_Create(a));
    StringList_Resize(e->names, count);
    a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    dropValues(e->values);
    e->values = ((igTDataList<int> *)igIntList_Create(a));
    vl = e->values;
    if (count >= 0) {
        if (!(count > vl->_capacity)) {
            vl->_count = count;
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
        if (nl->_count != 0 && i >= 0 && i < nl->_count) {
            slot = &nl->_data[i];
            if (held != 0) { ((int *)held)[-1] = ((int *)held)[-1] + 1; }
            old = *slot;
            releaseString(old);
            *slot = held;
        }
        releaseString(held);
        setValue(e->values, i, &values[i]);
    }
    igObjectSystem_AppendMetaEnum((int *)((*(int *)g_objectSystem)), (int)e);
    e->_refCount = e->_refCount - 1;
    if (((unsigned long long)((long long)e->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(e); }
    return e;
}

