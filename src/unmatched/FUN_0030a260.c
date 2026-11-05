typedef struct S1 { char pad4[4]; int f4; char pad8[42]; unsigned char f32; } S1;
typedef struct Z { char pad40[40]; unsigned char f28; } Z;
int FUN_003087a0();
int FUN_00309c90();
int FUN_00309fe0();
int igObject_Destroy();
extern int DAT_004fb3b8[4];
extern int DAT_004fb400[4];
void FUN_0030a260(Z *arg0, int arg1) {
    S1 *sp2C;
    S1 *temp_s0;

    if (arg0->f28 != 0) {
        FUN_003087a0(&sp2C, arg0, arg1);
        temp_s0 = sp2C;
        if (temp_s0 != 0) {
            temp_s0->f4 = (int)((int) (temp_s0->f4 - 1));
            if (((unsigned long long) ((long long) sp2C->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sp2C);
            }
        }
        if (temp_s0 != 0) {
            FUN_00309c90(temp_s0, &DAT_004fb400[0], &DAT_004fb3b8[0]);
            FUN_00309fe0(temp_s0);
            temp_s0->f32 = 1;
        }
    }
}
