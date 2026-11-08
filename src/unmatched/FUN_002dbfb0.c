int strcasecmp();
int strlen();
int strncasecmp();

int FUN_002dbfb0(int dummy0, int arg1, int arg2, int arg3) {
    switch (arg2) {
    case 0:
        return strcasecmp(arg1, arg3) == 0;
    case 1:
        return strncasecmp(arg1, arg3, strlen(arg3)) == 0;
    case 2:
        return strcasecmp(arg1, arg3) != 0;
    default:
        return 0;
    }
}
