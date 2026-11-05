extern "C" {
int beMessenger_AppendString(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBool(int, int);
int beMessenger_GetBoolCount(int);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int DAT_0050db10[4];
extern int DAT_0050dd48[4];
extern int DAT_0058a1c0[4];
int MDLisStatus(int arg0, int arg1, int arg2);
}

int MDLisStatus(int arg0, int arg1, int arg2) {
    beMessenger_SelectReceivers(DAT_0058a1c0[0], &DAT_0050db10[0], arg0, arg1);
    beMessenger_AppendString(DAT_0058a1c0[0], arg2);
    beMessenger_DispatchSelected(DAT_0058a1c0[0], &DAT_0050dd48[0]);
    if (beMessenger_GetBoolCount(DAT_0058a1c0[0]) == 1) {
        return beMessenger_GetBool(DAT_0058a1c0[0], 0);
    }
    return 0;
}
