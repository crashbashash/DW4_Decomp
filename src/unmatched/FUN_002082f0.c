int FUN_001edcb0();
int FUN_001f0410();
int FUN_00204240();
struct B *FUN_00208210();
int FUN_00209780();
void FUN_001f0470(void);
int FUN_001f0490();
extern int DAT_00490b60[4];
extern int DAT_004e5370[4];
extern int DAT_004e5390[4];
extern int DAT_0056c060[4];
extern int DAT_0056c078[4];
extern int DAT_0056c080[16];
extern int DAT_0056c0c8[4];
extern struct B * DAT_0056c0d0[4];
extern struct B * DAT_0056c0d8[4];
extern int DAT_0056c0e0[17];
extern int DAT_0056c128[4];
struct B { char pad[24]; int f24; int f28; char pad2[24]; int f56; short s60; short s62; short f64; };
void FUN_002082f0(void) {
    unsigned int i;
    unsigned int j;
    struct B *temp_v0_2;

    i = 0;
    DAT_0056c0c8[0] = 0;
    DAT_0056c060[0] = 0x4000;
    do {
        DAT_0056c0e0[i] = 0;
        i += 1;
    } while (i < 0x11U);
    DAT_0056c128[0] = 0;
    FUN_00204240(0xA, &DAT_0056c0c8[0]);
    temp_v0_2 = FUN_00208210();
    DAT_0056c0d0[0] = temp_v0_2;
    temp_v0_2->f24 = 0;
    DAT_0056c0d0[0]->f28 = 0;
    FUN_001edcb0(&temp_v0_2->f56);
    temp_v0_2->f64 = DAT_0056c060[0] - temp_v0_2->f56;
    DAT_0056c0d8[0] = DAT_0056c0d0[0];
    DAT_0056c078[0] = temp_v0_2->f56;
    if (DAT_00490b60[0] != 0) {
        FUN_001f0410(FUN_001f0490, &DAT_004e5370[0]);
        FUN_001f0410(FUN_001f0470, &DAT_004e5390[0]);
    }
    j = 0;
    do {
        DAT_0056c080[j] = 0;
        j += 1;
    } while (j < 0x10U);
    FUN_00209780(0, 0x80, 0);
}
