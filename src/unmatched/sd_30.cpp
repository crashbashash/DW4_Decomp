extern "C" {
int beMessenger_SendNamed(...);
extern int DAT_0058a1c0[4];
void sd_30(int arg0, int arg1, int arg2, int arg3);
}
void sd_30(int arg0, int arg1, int arg2, int arg3) {
    beMessenger_SendNamed(DAT_0058a1c0[0], arg0, arg1, arg2, arg3);
}
