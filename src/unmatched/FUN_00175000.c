typedef struct S { char pad0[1292]; int f1292; } S;
int FUN_001f7470();
extern int DAT_005609c4[4];
void FUN_00175000(S *arg0, int arg1) {
    if (arg0->f1292 == arg1) {
        DAT_005609c4[0] += 1;
    }
    arg0->f1292 = arg1;
    if (arg1 == 0) {
        FUN_001f7470(2);
    } else if (arg1 == 1) {
        FUN_001f7470(1);
    } else if (arg1 == 2) {
        FUN_001f7470(0);
    }
}
