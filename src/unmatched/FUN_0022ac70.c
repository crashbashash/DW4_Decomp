int FUN_0022ac60();
int FUN_0022ad00();
int igObject_IsKindOf();
int FUN_0022ac70(int arg0, int arg1) {
    int v;

    v = FUN_0022ad00(arg0);
    while (FUN_0022ac60(arg0) != 0) {
        if (v != 0 && igObject_IsKindOf(v, arg1) != 0) {
            return v;
        }
        v = FUN_0022ad00(arg0);
    }
    return 0;
}
