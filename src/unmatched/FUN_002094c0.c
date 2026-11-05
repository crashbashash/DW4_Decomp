typedef struct B {
    unsigned short r0 : 2;
    unsigned short m : 3;
    unsigned short f : 1;
    unsigned short c : 3;
    unsigned short r1 : 7;
} B;
typedef struct P { char pad[104]; B b104; char pad2[6]; B b112; } P;
extern int DAT_00569330[4];
extern P *DAT_0056ad80[4];
extern int DAT_00491478[4];
extern long long DAT_0056ae48[4];
void FUN_002094c0(int arg0, int arg1) {
    if (DAT_00569330[0] == 0) {
        DAT_0056ad80[0]->b104.f = arg0;
        DAT_0056ad80[0]->b104.c = arg1;
        if (DAT_0056ad80[0]->b104.c == 1 || DAT_0056ad80[0]->b104.c == 0) {
            DAT_0056ad80[0]->b104.m = 0;
        }
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x2000;
    } else {
        DAT_0056ad80[0]->b112.f = arg0;
        DAT_0056ad80[0]->b112.c = arg1;
        if (DAT_0056ad80[0]->b112.c == 1 || DAT_0056ad80[0]->b112.c == 0) {
            DAT_0056ad80[0]->b112.m = 0;
        }
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x4000;
    }
}
