extern "C" {
int sscanf(...);
int strlen(...);
int FUN_002b9500(...);
int FUN_002db480(...);
int FUN_002db4e0(...);
int FUN_0030b3c0(...);
int igObject_GetAllocator(...);
extern int DAT_004f9718[4];
bool FUN_002db5e0(char *arg0, int *arg1);
}
bool FUN_002db5e0(char *arg0, int *arg1) {
    char buf[4096];
    bool var_s0;

    var_s0 = false;
    FUN_002db480();
    if (sscanf(*(int *)(arg0 + 52), &DAT_004f9718[0], buf) == 1) {
        *(int *)(arg0 + 52) = *(int *)(arg0 + 52) + strlen(buf);
        FUN_002db4e0(arg0, buf);
        *arg1 = FUN_002b9500(igObject_GetAllocator(arg0));
        FUN_0030b3c0(*arg1, buf);
        var_s0 = true;
    }
    return var_s0;
}
