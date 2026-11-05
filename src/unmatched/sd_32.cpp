extern "C" {
int beMessenger_SendDelayedNamed(...);
extern int DAT_0058a1c0[4];
void sd_32(int arg0, int arg1, int arg2, int arg3, int arg4);
}
void sd_32(int arg0, int arg1, int arg2, int arg3, int arg4) {
    beMessenger_SendDelayedNamed(DAT_0058a1c0[0], arg0, arg1, arg2, arg3, arg4);
}
