struct S {
    char p[216];
    char f216;
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
    char p2[2];
    char f220;
};
extern int DAT_00491478[4];
extern struct S * DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_00209780(char arg0, char arg1, int arg2) {
    DAT_0056ad80[0]->f216 = arg0;
    DAT_0056ad80[0]->f220 = arg1;
    DAT_0056ad80[0]->b7 = arg2;
    DAT_00491478[0] |= 0x40;
    DAT_0056ae48[0] |= 0x08000000;
}
