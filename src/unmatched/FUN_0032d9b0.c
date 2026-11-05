extern char DAT_004fb418[];
int FUN_0010e2a8();
int SignalSema();
int WaitSema();
extern int DAT_004fb410[4];
int thunk_iSignalSema();
typedef struct Ob { int w0; int w4; int f8; int w12; int f16; } Ob;
void FUN_0032d9b0(int *arg0, Ob *arg1, int arg2, int arg3) {
    int *var_v1;
    int var_s1;

    WaitSema(arg1->f16);
    if (arg3 != 0) {
        var_s1 = FUN_0010e2a8(arg1->f8, arg2, 2, 0, 0, 0, 0, 0, 0);
        SignalSema(arg1->f16);
    } else {
        var_s1 = FUN_0010e2a8(arg1->f8, arg2, 3, 0, 0, 0, 0, thunk_iSignalSema, arg1->f16);
    }
    if (var_s1 >= 0) {
        var_v1 = (int *)(&DAT_004fb410[0]);
    } else {
        var_v1 = (int *)DAT_004fb418;
    }
    *arg0 = *var_v1;
}
