typedef struct { char c[64]; } Info;
extern int FUN_002a0dd8(void *h);
extern int FUN_002a0bb8(void *h, int code);
int FUN_002adc50(char *h, Info *out) {
    int r = FUN_002a0dd8(h);
    if (r != 0) {
        return FUN_002a0bb8(0, 0xFF000114);
    }
    *out = *(Info *)(h + 2316);
    return r;
}
