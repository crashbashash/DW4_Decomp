int FUN_0022b910();
int FUN_0022bac0();
int igObject_IsKindOf();
extern int DAT_005615e0[4];
extern int DAT_00562220[4];
int FUN_0022b820(int arg0, int arg1) {
    if (igObject_IsKindOf(arg1, DAT_005615e0[0]) != 0) {
        return FUN_0022bac0(arg1, arg0);
    }
    if (igObject_IsKindOf(arg1, DAT_00562220[0]) != 0) {
        return FUN_0022b910(arg1, arg0);
    }
    return 0;
}
