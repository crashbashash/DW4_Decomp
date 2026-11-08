typedef struct {
    short interlace;
    short pad;
    int x4;
    int x8;
} GsState;
GsState *FUN_00102b88(void);
void FUN_0010b370(void);
long long FUN_0010b400(void);
int FUN_00102c00(void) {
    GsState *s = FUN_00102b88();
    long long f;
    if (s->x8 == 0) {
        FUN_0010b370();
        if (s->interlace != 1) return 1;
        return (*(volatile unsigned long long *)0x12001000 >> 13) & 1;
    }
    f = (FUN_0010b400() >> 13) & 1;
    if (s->interlace != 1) return 1;
    return f;
}
