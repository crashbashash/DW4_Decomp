typedef struct {
    short interlace;
    short pad;
    int x4;
    int x8;
} GsState;
GsState *FUN_00102b88(void);
void VSync(void);
long long VSync2(void);
int sceGsSyncV(void) {
    GsState *s = FUN_00102b88();
    long long f;
    if (s->x8 == 0) {
        VSync();
        if (s->interlace != 1) return 1;
        return (*(volatile unsigned long long *)0x12001000 >> 13) & 1;
    }
    f = (VSync2() >> 13) & 1;
    if (s->interlace != 1) return 1;
    return f;
}
