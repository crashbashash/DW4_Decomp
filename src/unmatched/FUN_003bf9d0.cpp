extern "C" {
int StringChunk_ReleaseHeader(int, void *);
int igObject_Destroy(void *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00524950[4];
extern int DAT_0052cf80[4];
extern int DAT_0053a0d0[4];
extern int DAT_0053adb0[4];
extern int DAT_00540580[4];

typedef struct R { int w0; int refs; } R;
typedef struct O { int *vt; int f4; int *str; int f12; int f16; int f20; R *ref; } O;

O *FUN_003bf9d0(O *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R *temp_a0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &DAT_00540580[0];
        if (arg0 != 0) {
            arg0->vt = &DAT_0053adb0[0];
            if (arg0 != 0) {
                arg0->vt = &DAT_0053a0d0[0];
                if (&arg0->ref != 0) {
                    temp_a0 = arg0->ref;
                    if (temp_a0 != 0) {
                        temp_a0->refs = temp_a0->refs - 1;
                        if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(temp_a0);
                        }
                    }
                }
                if (arg0 != 0) {
                    arg0->vt = &DAT_0052cf80[0];
                    if (arg0 != 0) {
                        arg0->vt = &DAT_00524950[0];
                        if (&arg0->str != 0) {
                            temp_v1 = arg0->str;
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
