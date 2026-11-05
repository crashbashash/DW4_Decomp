int FUN_0010e2a8();
int SignalSema();
int WaitSema();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
int thunk_iSignalSema();
typedef struct Ob { int w0; int w4; int f8; int w12; int f16; } Ob;
void FUN_0032d6d0(int *arg0, Ob *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    int *var_v1_2;
    int var_s0;

    if (arg3 & 0xF) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    if (arg4 & 0xF) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    if (arg5 & 0xF) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    if (arg6 & 0xF) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    WaitSema(arg1->f16);
    if ((arg5 == 0) && (arg7 == 0)) {
        var_s0 = FUN_0010e2a8(arg1->f8, arg2, 1, arg3, arg4, 0, 0, thunk_iSignalSema, arg1->f16);
    } else {
        var_s0 = FUN_0010e2a8(arg1->f8, arg2, 0, arg3, arg4, arg5, arg6, 0, 0);
        SignalSema(arg1->f16);
    }
    if (var_s0 >= 0) {
        var_v1_2 = (int *)(&DAT_004fb410[0]);
    } else {
        var_v1_2 = (int *)(&DAT_004fb418[0]);
    }
    *arg0 = *var_v1_2;
}
