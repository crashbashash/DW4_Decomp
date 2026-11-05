int FUN_00147430();

int FUN_00147ff0(void *arg0, unsigned int arg1) {
    int var_a1;

    switch (arg1) {
    case 0:
        var_a1 = 5;
        break;
    case 1:
        var_a1 = 7;
        break;
    case 2:
        var_a1 = 4;
        break;
    case 3:
        var_a1 = 6;
        break;
    case 4:
        var_a1 = 0xC;
        break;
    case 5:
        var_a1 = 0xD;
        break;
    case 6:
        var_a1 = 0xE;
        break;
    case 7:
        var_a1 = 0xF;
        break;
    case 8:
        var_a1 = 0xA;
        break;
    case 9:
        var_a1 = 0xB;
        break;
    case 10:
        var_a1 = 8;
        break;
    default:
        var_a1 = 9;
        break;
    }
    if (*(unsigned char *)((char *)(arg0) + 12) != 0) {
        return FUN_00147430(arg0, var_a1);
    }
    return var_a1;
}
