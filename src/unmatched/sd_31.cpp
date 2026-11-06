/* Matches only with the alternate (combat) compiler build. */
extern "C" {
int Lua_sd_OptionalArg(int);
int beMessenger_EnqueueSelected(int, int, int);
int beMessenger_PrepareDelayedSelection(int, int, int, int);
extern int DAT_0058a1c0[4];
void sd_31(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
}

void sd_31(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    beMessenger_PrepareDelayedSelection(DAT_0058a1c0[0], arg0, arg1, arg2);
    if (arg4 != 0) {
        Lua_sd_OptionalArg(arg4);
    }
    beMessenger_EnqueueSelected(DAT_0058a1c0[0], arg3, arg5);
}
