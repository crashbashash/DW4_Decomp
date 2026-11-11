int memset();
int FUN_002eb010();
int List_Resize();
int Gap__Core__igObject__vfunc_10();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
int *StringPool_Intern();
extern int DAT_00586f20[4];

typedef struct StringRefListView { char pad[8]; int count; int cap; int **data; } StringRefListView;

static inline int pool(void) {
    int p;
    if (DAT_00586f20[0] == 0) {
        p = FUN_002eb010(0x10);
        if (p != 0) {
            p = StringPool_Construct(p);
        }
        DAT_00586f20[0] = p;
    }
    return DAT_00586f20[0];
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
        v = StringPool_Intern(pool(), 0);
        old = *slot;
        if (old != 0) {
            hd = old - 2;
            rc = old[-1] - 1;
            old[-1] = rc;
            if (rc == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        *slot = v;
    }
    self->count = 0;
    Gap__Core__igObject__vfunc_10(self);
}

void StringList_Resize(StringRefListView *arg0, int arg1) {
    int *a1;
    int n;
    int pool;
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
            if (DAT_00586f20[0] == 0) {
                pool = FUN_002eb010(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                DAT_00586f20[0] = pool;
            }
            nw = (int *)StringPool_Intern(DAT_00586f20[0], 0);
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
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
