extern "C" {
extern int DAT_00524950[4];
extern int DAT_00535a20[4];

typedef struct R { int w0; int refs; } R;
typedef struct O { int *vt; int f4; int *str; int f12; int f16; R *ref; } O;


int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(R *);
int thunk_FUN_002ed460__002ff810(O *);
O *FUN_00361a20(O *arg0, short arg1);
}

O *FUN_00361a20(O *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R *temp_a0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &DAT_00535a20[0];
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
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
