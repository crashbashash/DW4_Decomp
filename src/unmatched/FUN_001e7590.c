struct S {
    char pad0[314];
    unsigned char a0 : 1; unsigned char a1 : 2; unsigned char a2 : 5;
    char pad1[7];
    unsigned char b0 : 1; unsigned char b1 : 2; unsigned char b2 : 5;
    char pad2[49];
    unsigned char c0 : 1; unsigned char c1 : 7;
    char pad3[7];
    unsigned char d0 : 1; unsigned char d1 : 7;
};
extern int DAT_00491478[4];
extern char DAT_00562cd0[16];
extern char DAT_00562cd1[16];
extern char DAT_00562ce0[16];
extern char DAT_00562ce1[16];
extern char DAT_00562cf0[16];
extern char DAT_00562cf1[16];
extern int DAT_00569330[4];
extern struct S *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056b058[4];
void FUN_001e7590(void) {
    if (DAT_00569330[0] == 0) {
        if (DAT_00562cd0[0] != 0) {
            DAT_0056ad80[0]->a0 = 1;
            DAT_0056ad80[0]->a1 = DAT_00562ce0[0];
            DAT_0056ad80[0]->c0 = DAT_00562cf0[0];
        } else {
            DAT_0056ad80[0]->a0 = 1;
            DAT_0056ad80[0]->a1 = 1;
            DAT_0056ad80[0]->c0 = 1;
        }
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x4080LL << 0x20;
        if (DAT_0056b058[0] != 0) {
            DAT_0056ad80[0]->b0 = DAT_0056ad80[0]->a0;
            DAT_0056ad80[0]->b1 = DAT_0056ad80[0]->a1;
            DAT_0056ad80[0]->d0 = DAT_0056ad80[0]->c0;
            DAT_00491478[0] |= 0x40;
            DAT_0056ae48[0] |= 0x8100LL << 0x20;
        }
    } else {
        if (DAT_00562cd1[0] != 0) {
            DAT_0056ad80[0]->b0 = 1;
            DAT_0056ad80[0]->b1 = DAT_00562ce1[0];
            DAT_0056ad80[0]->d0 = DAT_00562cf1[0];
        } else {
            DAT_0056ad80[0]->b0 = 1;
            DAT_0056ad80[0]->b1 = 1;
            DAT_0056ad80[0]->d0 = 1;
        }
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x8100LL << 0x20;
    }
}
