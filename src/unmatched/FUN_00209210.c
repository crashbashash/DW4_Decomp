typedef struct R { unsigned char a : 2; unsigned char b : 2; unsigned short c : 10; unsigned long long d : 10; unsigned long long e : 10; unsigned short f : 10; } R;
typedef struct P { char pad[52]; unsigned char x0 : 2; unsigned char fl : 1; unsigned char r : 5; char pad2[7]; unsigned char y0 : 2; unsigned char fl2 : 1; unsigned char r2 : 5; char pad3[3]; R r64; R r72; } P;
int FUN_001fcb00();
extern int DAT_00491478[4];
extern int DAT_00569330[4];
extern P *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_00209210(int arg0, int arg1, int arg2, long long arg3, long long arg4, int arg5, int arg6) {
    int temp_a2;
    R *q;
    long long temp_a1;
    if (DAT_00569330[0] == 0) {
        DAT_0056ad80[0]->fl = arg6;
        DAT_0056ad80[0]->r64.a = arg0;
        DAT_0056ad80[0]->r64.b = arg1;
        DAT_0056ad80[0]->r64.c = arg2;
        q = &DAT_0056ad80[0]->r64;
        q->d = (int)arg3;
        q->e = (int)arg4;
        q->f = arg5;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x140;
    } else {
        DAT_0056ad80[0]->fl2 = arg6;
        DAT_0056ad80[0]->r72.a = arg0;
        DAT_0056ad80[0]->r72.b = arg1;
        DAT_0056ad80[0]->r72.c = arg2;
        q = &DAT_0056ad80[0]->r72;
        q->d = (int)arg3;
        q->e = (int)arg4;
        q->f = arg5;
        temp_a2 = DAT_00491478[0] | 0x40;
        temp_a1 = DAT_0056ae48[0] | 0x280;
        DAT_00491478[0] = temp_a2;
        DAT_0056ae48[0] = temp_a1;
        if (DAT_00569330[0] == 1) {
            FUN_001fcb00();
        }
    }
}
