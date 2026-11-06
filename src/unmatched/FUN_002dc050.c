int FUN_002dc050(int dummy0, int arg1, int arg2, int arg3) {
    switch (arg2) {
    case 0:
        return arg1 == arg3;
    case 1:
        return arg1 >= arg3;
    case 2:
        return arg1 != arg3;
    default:
        return 0;
    }
}
