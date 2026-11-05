int FUN_0010b7d8();
int FUN_0010e2a8();
int SignalSema();
int WaitSema();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
int thunk_iSignalSema();
typedef struct Ob { int w0; int w4; int f8; char *f12; int f16; } Ob;
void FUN_0032d850(int *arg0, Ob *arg1, int arg2, int arg3, int *arg4, int arg5) {
    int *var_v1;
    int var_s0;
    char *p;
    char *q;

    WaitSema(arg1->f16);
    *(int *)arg1->f12 = arg3;
    if (arg4 == 0) {
        p = arg1->f12;
        FUN_0010b7d8(p, p + 0xF);
        if (arg5 != 0) {
            var_s0 = FUN_0010e2a8(arg1->f8, arg2, 2, arg1->f12, 0x10, 0, 0, 0, 0);
            SignalSema(arg1->f16);
        } else {
            var_s0 = FUN_0010e2a8(arg1->f8, arg2, 3, arg1->f12, 0x10, 0, 0, thunk_iSignalSema, arg1->f16);
        }
    } else {
        p = arg1->f12;
        q = p + 0x10;
        var_s0 = FUN_0010e2a8(arg1->f8, arg2, 0, p, 0x10, q, 0x10, 0, 0);
        *arg4 = *(int *)q;
        SignalSema(arg1->f16);
    }
    if (var_s0 >= 0) {
        var_v1 = (int *)(&DAT_004fb410[0]);
    } else {
        var_v1 = (int *)(&DAT_004fb418[0]);
    }
    *arg0 = *var_v1;
}
