typedef struct V3 { float x, y, z; } V3;
extern "C" {
int FUN_003a63b0(int, V3 *, int);
int FUN_003a64d0(int, V3 *, int);
int Matrix44_Copy(void *, int);
int Matrix44_GetTranslation(int, V3 *);
int igStrCmp(int, char *);
extern char DAT_0050ffd0[];
extern char DAT_0050ffe8[];
extern char DAT_00510008[];
extern int DAT_0058a570[4];
extern float DAT_0058a580[4];
extern float DAT_0058a584[4];
extern float DAT_0058a588[4];
extern int DAT_0058a590[4];
extern char DAT_0058a5a0[];
int FUN_003a65f0(int arg0, int arg1, int arg2);
}
int FUN_003a65f0(int arg0, int arg1, int arg2) {
    V3 p;
    V3 q1;
    V3 q2;
    int e;
    Matrix44_Copy(DAT_0058a5a0, arg0);
    Matrix44_GetTranslation(arg0, &p);
    DAT_0058a580[0] = p.x;
    DAT_0058a584[0] = p.y;
    DAT_0058a588[0] = p.z;
    DAT_0058a590[0] = 0xC2C80000;
    e = igStrCmp(arg2, DAT_00510008) == 0;
    if (igStrCmp(arg1, DAT_0050ffd0) == 0) {
        q1.x = p.x; q1.y = p.y; q1.z = p.z;
        return FUN_003a63b0(DAT_0058a570[0], &q1, e);
    }
    if (igStrCmp(arg1, DAT_0050ffe8) == 0) {
        q2.x = p.x; q2.y = p.y; q2.z = p.z;
        return FUN_003a64d0(DAT_0058a570[0], &q2, e);
    }
    return 0;
}
