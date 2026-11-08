extern "C" {
typedef struct S { char pad[52]; int f52; } S;
int sscanf(...);
int strlen(...);
int FUN_002b9500(...);
int FUN_002db480();
int FUN_0030b3c0(...);
int igObject_GetAllocator(...);
extern int DAT_004f96d0[4];
bool FUN_002db540(S *arg0, int *arg1) {
    char sp40[4096];
    bool var_s0;

    var_s0 = 0;
    FUN_002db480();
    if (sscanf(arg0->f52, &DAT_004f96d0[0], sp40) == 1) {
        arg0->f52 = arg0->f52 + strlen(sp40);
        *arg1 = FUN_002b9500(igObject_GetAllocator(arg0));
        FUN_0030b3c0(*arg1, sp40);
        var_s0 = 1;
    }
    return var_s0;
}
}
