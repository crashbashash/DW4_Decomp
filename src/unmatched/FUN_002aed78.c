int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002ada78();
int FUN_002af060();

int FUN_002aed78(int arg0, int arg1) {
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000123, 4);
    }
    FUN_002af060(arg0, arg1, 4);
    if (arg1 != 0) {
        FUN_002ada78(arg0, 0xF, 4);
    }
    return 0;
}
