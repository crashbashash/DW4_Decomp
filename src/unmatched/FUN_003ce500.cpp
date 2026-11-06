extern "C" {
int beMessenger_AppendString(int, int);
int beMessenger_AppendVec3(int, float *);
int beMessenger_DispatchSelected(int, int);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int DAT_00515990[4];

typedef struct A { char pad[12]; int f12; char pad16[4]; int f20; } A;

void FUN_003ce500(A *arg0, int arg1, int arg2, float *arg3, int arg4) {
    float sp50[4];

    beMessenger_SelectReceivers(arg0->f12, &DAT_00515990[0], arg1, arg0->f20);
    if (arg3 != 0) {
        sp50[0] = arg3[0];
        sp50[1] = arg3[1];
        sp50[2] = arg3[2];
        beMessenger_AppendVec3(arg0->f12, &sp50[0]);
    }
    if (arg4 != 0) {
        beMessenger_AppendString(arg0->f12, arg4);
    }
    beMessenger_DispatchSelected(arg0->f12, arg2);
}
}
