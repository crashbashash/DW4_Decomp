static inline int getStringPool(void) {
    int p;
    if (g_stringPool == 0) {
        p = ((int)StringPool_Allocate(0x10));
        if (p != 0) {
            p = ((int)StringPool_Construct((StringPool *)p));
        }
        g_stringPool = (StringPool *)p;
    }
    return (int)g_stringPool;
}

void igStringRefList_ReleaseDefaults(void *self0) {
    igTDataList<char *> *self;
    int n;
    int i;
    char **slot;
    int *interned;
    int *old;
    int *hd;
    int rc;

    self = (igTDataList<char *> *)self0;
    n = self->_count;
    for (i = 0; i < n; i++) {
        slot = &self->_data[i];
        interned = ((int *)StringPool_Intern((StringPool *)(getStringPool()), (const char *)0));
        old = (int *)*slot;
        if (old != 0) {
            hd = old - 2;
            rc = old[-1] - 1;
            old[-1] = rc;
            if (rc == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
            }
        }
        *slot = (char *)interned;
    }
    self->_count = 0;
    igObject_ReleaseDefaults((igObject *)self);
}

void StringList_Resize(igTDataList<char *> *list, int count) {
    int *a1;
    int n;
    int pool;
    int i;
    char **slot;
    int *nw;
    int v1;
    int *old;

    n = list->_count;
    if (count > n) {
        goto grow;
    }
    {
        for (i = count; i < n; i++) {
            slot = &list->_data[i];
            if (g_stringPool == 0) {
                pool = ((int)StringPool_Allocate(0x10));
                if (pool != 0) {
                    pool = ((int)StringPool_Construct((StringPool *)pool));
                }
                g_stringPool = (StringPool *)pool;
            }
            nw = (int *)((int *)StringPool_Intern((StringPool *)g_stringPool, (const char *)0));
            old = (int *)*slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
                }
            }
            *slot = (char *)nw;
        }
        list->_count = count;
        return;
    }
grow:
    if (count >= 0) {
        if (count <= list->_capacity) {
            list->_count = count;
        } else {
            List_Resize(list, count, 4);
        }
    }
    memset(list->_data + n, 0, (count - n) * 4);
}

