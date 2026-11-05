int FUN_00159f80();
int FUN_0015ac10(int x) {
    switch (x) {
    default:
        switch (x) {
        case 2: return 3;
        case 4: return 5;
        case 6: return 7;
        case 8:
        case 12: return 7;
        case 0x10001: return 0x10000;
        }
        break;
    case 10: return 5;
    case 9: return 7;
    case 11: return 7;
    }
    if (FUN_00159f80() != 0) x = -1;
    return x;
}
