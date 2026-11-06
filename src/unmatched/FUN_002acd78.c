int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002aa538();
int FUN_002ada78();

void FUN_002acd78(int arg0) {
    if (FUN_002a0dd8() != 0) {
        FUN_002a0bb8(0, 0xFF000153, 1);
        return;
    }
    FUN_002ada78(arg0, 0x2F, 1);
    FUN_002aa538(arg0);
}
