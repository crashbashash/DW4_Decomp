typedef struct { char pad[688]; int f688; int f692; int f696; } S;
extern int FUN_002a0dd8(void *h);
extern int FUN_002a0bb8(void *h, int code);
int FUN_002af6f8(char *h, int a, int b) {
    S *s;
    int r = FUN_002a0dd8(h);
    if (r != 0) {
        return FUN_002a0bb8(0, 0xFF000125);
    }
    s = (S *)(h + 0xD28);
    s->f696 = b;
    s->f692 = a;
    s->f688++;
    *(int *)(h + 68) = 1;
    return r;
}
