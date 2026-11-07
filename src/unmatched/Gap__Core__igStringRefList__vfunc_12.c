int FUN_002eb010();
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
