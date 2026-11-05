extern int DAT_00491478[4];
extern int DAT_00569330[4];
typedef struct Obj {
    char pad[104];
    unsigned char a104 : 1; unsigned char r104 : 7;
    char pad105;
    unsigned char x106 : 3; unsigned char c106 : 2; unsigned char r106 : 3;
    char pad107;
    unsigned short d108 : 12; unsigned short r108 : 4;
    char pad110[2];
    unsigned char a112 : 1; unsigned char r112 : 7;
    char pad113;
    unsigned char x114 : 3; unsigned char c114 : 2; unsigned char r114 : 3;
    char pad115;
    unsigned short d116 : 12; unsigned short r116 : 4;
} Obj;
extern Obj *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_00209650(int arg0, int arg1, int arg2) {
    if (DAT_00569330[0] == 0) {
        DAT_0056ad80[0]->a104 = arg0;
        DAT_0056ad80[0]->c106 = arg1;
        DAT_0056ad80[0]->d108 = arg2;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x2000;
    } else {
        DAT_0056ad80[0]->a112 = arg0;
        DAT_0056ad80[0]->c114 = arg1;
        DAT_0056ad80[0]->d116 = arg2;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x4000;
    }
}
