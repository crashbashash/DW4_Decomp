extern int D_004be8d8[];
extern void FUN_002ada08(int a, int b);
extern int FUN_002a0dd8(void *h);
extern int FUN_002a0bb8(void *h, int code);
extern void FUN_002ada78(void *h, int a, int b);
extern void FUN_002adac8(void *h, int a, int b);
int FUN_002ad950(void *h, int a, int b) {
    if (h == 0) {
        FUN_002ada08(a, b);
        D_004be8d8[a] = b;
    } else {
        if (FUN_002a0dd8(h) != 0) {
            return FUN_002a0bb8(0, 0xFF000112);
        }
        FUN_002ada78(h, a, b);
        FUN_002adac8(h, a, b);
    }
    return 0;
}
