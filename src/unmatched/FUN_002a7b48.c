extern void FUN_002a0bb8(int a, int code);
void FUN_002a7b48(int a, int code) {
    if (code < -3 || (code >= -1 && code != 0)) {
        FUN_002a0bb8(a, code);
    }
}
