int FUN_0012a110();
int strlen();
int FUN_0012a918();

int FUN_002dbfb0(int dummy0, int arg1, int arg2, int arg3) {
    switch (arg2) {
    case 0:
        return FUN_0012a110(arg1, arg3) == 0;
    case 1:
        return FUN_0012a918(arg1, arg3, strlen(arg3)) == 0;
    case 2:
        return FUN_0012a110(arg1, arg3) != 0;
    default:
        return 0;
    }
}
