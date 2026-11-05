extern "C" {
int beMessenger_GetBool(...);
int beMessenger_GetBoolCount(...);
int beMessenger_SendNamed(...);
extern int DAT_0050daf0[4];
extern int DAT_0050db10[4];
extern int DAT_0058a1c0[4];
}
extern "C" bool MDLisLive(int arg0, int arg1);
bool MDLisLive(int arg0, int arg1) {
    int n;
    bool r;
    int i;
    beMessenger_SendNamed(DAT_0058a1c0[0], DAT_0050db10, arg0, arg1, DAT_0050daf0);
    n = beMessenger_GetBoolCount(DAT_0058a1c0[0]);
    r = false;
    for (i = 0; i < n; i++) {
        if (beMessenger_GetBool(DAT_0058a1c0[0], i)) {
            r = true;
            break;
        }
    }
    return r;
}
