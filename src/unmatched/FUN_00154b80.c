int FUN_00154b80(int arg0, int arg1, int *arg2, int *arg3) {
    switch (arg0) {
    case 0x0: *arg3 = 1; break;
    case 0x1: *arg3 = 1; break;
    case 0x2: *arg3 = 1; break;
    case 0x3: *arg3 = 2; break;
    case 0x4: *arg3 = 1; break;
    case 0x5: *arg3 = 3; break;
    case 0x6: *arg3 = 1; break;
    case 0x7: *arg3 = 4; break;
    case 0x8: *arg3 = 2; break;
    case 0x10000: *arg3 = 1; break;
    case 0x10001: *arg3 = 1; break;
    default:
        *arg2 = -2;
        *arg3 = -2;
        return *arg2;
    }
    *arg2 = arg1 * *arg3;
    return *arg2;
}
