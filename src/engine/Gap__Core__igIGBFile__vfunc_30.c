struct S { char pad0[20]; int f20; char pad1[8]; int f32; char pad2[243]; unsigned char f279; };
int FUN_002e9560();
int FUN_0030a260();
extern int DAT_004fb410[4];

void Gap__Core__igIGBFile__vfunc_30(int *arg0, struct S *arg1) {
    int sp3C;

    if (arg1->f279 == 0) {
        FUN_002e9560(&sp3C);
        if (arg1->f32 != 0) {
            FUN_0030a260(arg1->f32, arg1->f20);
        }
        arg1->f279 = 1;
        *arg0 = sp3C;
    } else {
        *arg0 = DAT_004fb410[0];
    }
}
