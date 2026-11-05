typedef struct S_temp_a0_7 { char p0[4]; int f4; } S_temp_a0_7;
typedef struct S_temp_a0_6 { char p0[4]; int f4; } S_temp_a0_6;
typedef struct S_temp_a0_5 { char p0[4]; int f4; } S_temp_a0_5;
typedef struct S_temp_a0_4 { char p0[4]; int f4; } S_temp_a0_4;
typedef struct S_temp_a0_3 { char p0[4]; int f4; } S_temp_a0_3;
typedef struct S_temp_a0_2 { char p0[4]; int f4; } S_temp_a0_2;
typedef struct S_temp_a0 { char p0[4]; int f4; } S_temp_a0;
typedef struct S_arg0 { int f0; char p0[92]; int f96; int f100; int f104; int f108; int f112; int f116; int f120; } S_arg0;
extern "C" {
int FUN_003b2d10(S_arg0 *, int);
int igObject_Destroy(void *);
int thunk_FUN_002ed460__002ff810(S_arg0 *);
extern int DAT_0053daa0[4];
extern int DAT_0053f150[4];
void *FUN_003ba3d0(S_arg0 *arg0, long long arg1);
}
void *FUN_003ba3d0(S_arg0 *arg0, long long arg1) {
    S_temp_a0 *temp_a0;
    S_temp_a0_2 *temp_a0_2;
    S_temp_a0_3 *temp_a0_3;
    S_temp_a0_4 *temp_a0_4;
    S_temp_a0_5 *temp_a0_5;
    S_temp_a0_6 *temp_a0_6;
    S_temp_a0_7 *temp_a0_7;

    if (arg0 != 0) {
        arg0->f0 = (int)(&DAT_0053f150[0]);
        if (((char *)arg0 + 0x78) != 0) {
            temp_a0 = (S_temp_a0 *)(arg0->f120);
            if (temp_a0 != 0) {
                temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
        if (((char *)arg0 + 0x74) != 0) {
            temp_a0_2 = (S_temp_a0_2 *)(arg0->f116);
            if (temp_a0_2 != 0) {
                temp_a0_2->f4 = (int)((int) (temp_a0_2->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_2->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_2);
                }
            }
        }
        if (((char *)arg0 + 0x70) != 0) {
            temp_a0_3 = (S_temp_a0_3 *)(arg0->f112);
            if (temp_a0_3 != 0) {
                temp_a0_3->f4 = (int)((int) (temp_a0_3->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_3->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_3);
                }
            }
        }
        if (((char *)arg0 + 0x6C) != 0) {
            temp_a0_4 = (S_temp_a0_4 *)(arg0->f108);
            if (temp_a0_4 != 0) {
                temp_a0_4->f4 = (int)((int) (temp_a0_4->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_4->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_4);
                }
            }
        }
        if (((char *)arg0 + 0x68) != 0) {
            temp_a0_5 = (S_temp_a0_5 *)(arg0->f104);
            if (temp_a0_5 != 0) {
                temp_a0_5->f4 = (int)((int) (temp_a0_5->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_5->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_5);
                }
            }
        }
        if (((char *)arg0 + 0x64) != 0) {
            temp_a0_6 = (S_temp_a0_6 *)(arg0->f100);
            if (temp_a0_6 != 0) {
                temp_a0_6->f4 = (int)((int) (temp_a0_6->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_6->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_6);
                }
            }
        }
        if (((char *)arg0 + 0x60) != 0) {
            temp_a0_7 = (S_temp_a0_7 *)(arg0->f96);
            if (temp_a0_7 != 0) {
                temp_a0_7->f4 = (int)((int) (temp_a0_7->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_7->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_7);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = (int)(&DAT_0053daa0[0]);
            FUN_003b2d10(arg0, 0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
