extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int thunk_FUN_002ed460__002ff810(struct O *);
extern int DAT_00524950[4];
extern int DAT_00533d60[4];
typedef struct O { int vt; int pad; int f8; } O;
O *FUN_00335700(O *arg0, long long arg1) {
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    if (arg0 != 0) {
        arg0->vt = (int)(&DAT_00533d60[0]);
        if (arg0 != 0) {
            arg0->vt = (int)(&DAT_00524950[0]);
            if (&arg0->f8 != 0) {
                temp_v1 = (void *)(arg0->f8);
                if (temp_v1 != 0) {
                    temp_a1 = (int *)((char *)temp_v1 - 8);
                    temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
                    *(int *)((char *)(temp_v1) - 4) = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                    }
                }
            }
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
}
