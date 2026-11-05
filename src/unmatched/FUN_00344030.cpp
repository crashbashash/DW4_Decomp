extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int thunk_FUN_002ed460__002ff810(struct W *);
extern int DAT_00524950[4];
extern int DAT_00539350[4];
struct W { int *vt; int pad; int *name; };
struct W *FUN_00344030(struct W *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &DAT_00539350[0];
        if (arg0 != 0) {
            arg0->vt = &DAT_00524950[0];
            if (&arg0->name != 0) {
                temp_v1 = arg0->name;
                if (temp_v1 != 0) {
                    temp_a1 = temp_v1 - 2;
                    temp_v0 = temp_v1[-1] - 1;
                    temp_v1[-1] = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
}
