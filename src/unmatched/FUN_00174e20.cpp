struct S { char p[1260]; int f1260; char q[24]; int f1288; };
extern "C" {
int FUN_001e74b0(int);
int FUN_001e7500(int);
extern int DAT_005609b8[4];
void FUN_00174e20(S *arg0, int arg1);
}
void FUN_00174e20(S *arg0, int arg1) {
    if (arg0->f1260 == ((unsigned char)arg1)) {
        DAT_005609b8[0] += 1;
    }
    arg0->f1260 = ((unsigned char)arg1);
    if ((arg1 != 0) && (arg0->f1288 != 7)) {
        FUN_001e74b0(4);
    } else {
        FUN_001e7500(4);
    }
}
