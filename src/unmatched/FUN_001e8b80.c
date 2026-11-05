struct S { char p[304]; unsigned char b0 : 1; unsigned char b1 : 7; };
extern int DAT_00491478[4];
extern struct S *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_001e8b80(int arg0) {
    DAT_0056ad80[0]->b0 = arg0;
    DAT_00491478[0] |= 0x40;
    DAT_0056ae48[0] |= 0x4000000000LL;
}
