typedef struct { char pad[12]; int f12; char pad2[16]; int f32; } S;
extern int FUN_002a96e0(void *h);
int FUN_002aa280(void *h) {
    S *s;
    if (FUN_002a96e0(h) == 0) {
        return 1;
    }
    s = (S *)(*(char **)((char *)h + 8120) + 0x10A8);
    if (s->f32 == 1) {
        return 1;
    }
    if (s->f12 < 3) return 0;
    return 1;
}
