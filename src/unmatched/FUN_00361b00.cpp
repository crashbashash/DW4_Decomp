extern "C" {
extern int DAT_00524950[4];
extern int DAT_00535a20[4];
extern int DAT_00541610[4];

typedef struct R { int w0; int refs; } R;
typedef struct O { int *vt; int f4; int *str; int f12; int f16; R *ref20; int f24; R *ref28; R *ref32; } O;


int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(R *);
int thunk_FUN_002ed460__002ff810(O *);
O *FUN_00361b00(O *arg0, short arg1);
}

O *FUN_00361b00(O *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R *temp_a0;
    R *temp_a0_2;
    R *temp_a0_3;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &DAT_00541610[0];
        if (&arg0->ref32 != 0) {
            temp_a0 = arg0->ref32;
            if (temp_a0 != 0) {
                temp_a0->refs = temp_a0->refs - 1;
                if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
        if (&arg0->ref28 != 0) {
            temp_a0_2 = arg0->ref28;
            if (temp_a0_2 != 0) {
                temp_a0_2->refs = temp_a0_2->refs - 1;
                if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_2);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &DAT_00535a20[0];
            if (&arg0->ref20 != 0) {
                temp_a0_3 = arg0->ref20;
                if (temp_a0_3 != 0) {
                    temp_a0_3->refs = temp_a0_3->refs - 1;
                    if (((unsigned long long)((long long)temp_a0_3->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(temp_a0_3);
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
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
