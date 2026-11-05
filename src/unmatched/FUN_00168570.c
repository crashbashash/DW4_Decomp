int FUN_00168570(int arg0, unsigned int arg1, int arg2, int *arg3, int *arg4, int *arg5, char *arg6) {
    *arg4 = arg2;
    *arg6 = 0;
    *arg5 = 0x64;
    switch (arg1) {
    case 1:
        *arg3 = 0x10000;
        break;
    case 6:
        *arg3 = 0;
        break;
    case 2:
        *arg3 = 0x10000;
        *arg4 *= 2;
        break;
    case 3:
        *arg3 = 8;
        *arg4 *= 2;
        break;
    case 4:
        *arg3 = 5;
        *arg4 *= 3;
        break;
    case 5:
        *arg3 = 7;
        *arg4 *= 4;
        break;
    case 7:
        *arg3 = 0x10000;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 8:
        *arg3 = 0x10000;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 12:
        *arg3 = 0;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 9:
        *arg3 = 8;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 10:
        *arg3 = 5;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 11:
        *arg3 = 7;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    default:
        *arg3 = -1;
        *arg4 = -1;
        *arg5 = -1;
        break;
    }
    return *arg3;
}
