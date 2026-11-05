typedef struct P { char pad[52]; unsigned char b0:3; unsigned char mode:2; unsigned char b5:3; char pad2[7]; unsigned char c0:3; unsigned char cmode:2; unsigned char c5:3; } P;
int FUN_001fcb00();
int FUN_00208f20();
extern int DAT_00491478[4];
extern int DAT_00569330[4];
extern P *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056c080[4];
void FUN_00208f70(int arg0) {
    int temp_a2;
    long long temp_a1;

    FUN_00208f20();
    if (DAT_00569330[0] == 0) {
        DAT_0056c080[DAT_00569330[0]] = arg0;
        DAT_0056ad80[0]->mode = arg0;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x40;
    } else {
        DAT_0056c080[DAT_00569330[0]] = arg0;
        DAT_0056ad80[0]->cmode = arg0;
        temp_a2 = DAT_00491478[0] | 0x40;
        temp_a1 = DAT_0056ae48[0] | 0x80;
        DAT_00491478[0] = temp_a2;
        DAT_0056ae48[0] = temp_a1;
        if (DAT_00569330[0] == 1) {
            FUN_001fcb00();
        }
    }
    DAT_00491478[0] |= 0x11;
}
