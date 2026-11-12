static inline int pool_30cd10(void) {
    int p;
    if (g_stringPool[0] == 0) {
        p = ((int)FUN_002eb010(0x10));
        if (p != 0) {
            p = ((int)StringPool_Construct((S_2eadf0 *)p));
        }
        g_stringPool[0] = p;
    }
    return g_stringPool[0];
}

void Gap__Core__igStringRefList__vfunc_12(void *self0) {
    StringRefListView *self;
    int n;
    int i;
    int **slot;
    int *v;
    int *old;
    int *hd;
    int rc;

    self = (StringRefListView *)self0;
    n = self->count;
    for (i = 0; i < n; i++) {
        slot = &self->data[i];
        v = ((int *)StringPool_Intern((StringPool *)(pool_30cd10()), (const char *)0));
        old = *slot;
        if (old != 0) {
            hd = old - 2;
            rc = old[-1] - 1;
            old[-1] = rc;
            if (rc == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd), (int)hd);
            }
        }
        *slot = v;
    }
    self->count = 0;
    Gap__Core__igObject__vfunc_10((int)self);
}

void StringList_Resize(StringRefListView *arg0, int arg1) {
    int *a1;
    int n;
    int pool_30cd10;
    int i;
    int **slot;
    int *nw;
    int v1;
    int *old;

    n = arg0->count;
    if (arg1 > n) {
        goto grow;
    }
    {
        for (i = arg1; i < n; i++) {
            slot = &arg0->data[i];
            if (g_stringPool[0] == 0) {
                pool_30cd10 = ((int)FUN_002eb010(0x10));
                if (pool_30cd10 != 0) {
                    pool_30cd10 = ((int)StringPool_Construct((S_2eadf0 *)pool_30cd10));
                }
                g_stringPool[0] = pool_30cd10;
            }
            nw = (int *)((int *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0));
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
                }
            }
            *slot = nw;
        }
        arg0->count = arg1;
        return;
    }
grow:
    if (arg1 >= 0) {
        if (arg1 <= arg0->cap) {
            arg0->count = arg1;
        } else {
            List_Resize(arg0, arg1, 4);
        }
    }
    memset(arg0->data + n, 0, (arg1 - n) * 4);
}

