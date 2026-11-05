int FUN_001fcb00();
int FUN_00208f20();
extern int DAT_00491478[4];
extern int DAT_00569330[4];
typedef struct Obj { char pad[52]; unsigned char a52 : 2; unsigned char b52 : 1; unsigned char c52 : 2; unsigned char r52 : 3; char pad2[7]; unsigned char a60 : 2; unsigned char b60 : 1; unsigned char c60 : 2; unsigned char r60 : 3; } Obj;
extern Obj *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056c080[4];
void FUN_00209090(int arg0, int arg1) {
    FUN_00208f20();
    if (DAT_00569330[0] == 0) {
        *(int *)((char *)DAT_0056c080 + DAT_00569330[0] * 4) = arg0;
        DAT_0056ad80[0]->c52 = arg0;
        DAT_0056ad80[0]->b52 = arg1;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x40;
    } else {
        *(int *)((char *)DAT_0056c080 + DAT_00569330[0] * 4) = arg0;
        DAT_0056ad80[0]->c60 = arg0;
        DAT_0056ad80[0]->b60 = arg1;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x80;
        if (DAT_00569330[0] == 1) {
            FUN_001fcb00();
        }
    }
    DAT_00491478[0] |= 0x11;
}
