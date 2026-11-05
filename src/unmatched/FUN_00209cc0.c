int FUN_00209cc0(int a) {
    int n;
    for (n = 0; (a >>= 1) != 0; n++) {}
    return n;
}
