extern "C" {
int Lua_sd_OptionalArg(int);
int beMessenger_DispatchSelected(int, int);
int beMessenger_SelectReceivers(int, int, int, int);
extern int DAT_0058a1c0[4];
void sd_29(int arg0, int arg1, int arg2, int arg3, int arg4);
}

void sd_29(int arg0, int arg1, int arg2, int arg3, int arg4) {
    beMessenger_SelectReceivers(DAT_0058a1c0[0], arg0, arg1, arg2);
    if (arg4 != 0) {
        Lua_sd_OptionalArg(arg4);
    }
    beMessenger_DispatchSelected(DAT_0058a1c0[0], arg3);
}
