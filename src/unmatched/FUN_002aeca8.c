typedef struct { char pad[676]; int f676; } S;
extern int FUN_002a0dd8(void *h);
extern int FUN_002a0bb8(void *h, int code);
int FUN_002aeca8(char *h) {
    S *s;
    int r = FUN_002a0dd8(h);
    if (r != 0) {
        return FUN_002a0bb8(0, 0xFF000122);
    }
    s = (S *)(h + 0xD28);
    s->f676++;
    *(int *)(h + 68) = 1;
    return r;
}
