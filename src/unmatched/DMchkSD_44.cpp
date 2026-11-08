/* Dispatches a name to one of two modes (two accepted spellings each). */
extern "C" {
int FUN_0037e3a0(int, int, int, int, int, int, int, int);
int strcmp(int *, int);
extern int DAT_0050dac8[4];
extern int DAT_0050dad0[4];
extern int DAT_0050dad8[4];
extern int DAT_0050dae0[4];
extern int DAT_0058a1d0[4];
void DMchkSD_44(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
}

void DMchkSD_44(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    if (strcmp(&DAT_0050dac8[0], arg5) == 0 || strcmp(&DAT_0050dad0[0], arg5) == 0) {
        FUN_0037e3a0(DAT_0058a1d0[0], 2, arg0, arg1, arg2, arg3, arg4, 0);
    } else if (strcmp(&DAT_0050dad8[0], arg5) == 0 || strcmp(&DAT_0050dae0[0], arg5) == 0) {
        FUN_0037e3a0(DAT_0058a1d0[0], 1, arg0, arg1, arg2, arg3, arg4, 0);
    }
}
