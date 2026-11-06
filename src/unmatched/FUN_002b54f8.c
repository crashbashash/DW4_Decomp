unsigned int FUN_002b52d8();
int FUN_002b56f8();

int FUN_002b54f8(int arg0, int arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    if (FUN_002b52d8() >= 2U) {
        return FUN_002b56f8(arg0, arg1, 0x17);
    }
    return 0;
}
