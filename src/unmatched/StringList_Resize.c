int memset();
int FUN_002eb010();
int List_Resize();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
char *StringPool_Intern();
extern int DAT_00586f20[4];
struct L { char pad[8]; int n; int cap; int **arr; };
void StringList_Resize(struct L *arg0, int arg1) {
    int *a1;
    int v1;
    int pool;
    int *nw;
    int **slot;
    int *old;
    int i;
    int n;

    n = arg0->n;
    if (arg1 > n) {
        goto grow;
    }
    {
        for (i = arg1; i < n; i++) {
            slot = &arg0->arr[i];
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
        arg0->n = arg1;
        return;
    }
grow:
    if (arg1 >= 0) {
        if (arg1 <= arg0->cap) {
            arg0->n = arg1;
        } else {
            List_Resize(arg0, arg1, 4);
        }
    }
    memset(arg0->arr + n, 0, (arg1 - n) * 4);
}
