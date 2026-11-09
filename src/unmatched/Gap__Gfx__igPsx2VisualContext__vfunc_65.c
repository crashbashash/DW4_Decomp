typedef struct VisualContextView { char pad956[956]; int f3bc; } VisualContextView;
int FUN_001f7250();
unsigned int FUN_001931b0(void *color, int scale);
extern long long DAT_005608a0[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_65(VisualContextView *arg0, void *color) {
    unsigned int value = FUN_001931b0(color, 1);
    unsigned int hi;
    unsigned int lo;
    int c;
    hi = ((value >> 1) & 0x7F000000) + (value & 0x01000000);
    lo = value & 0xFFFFFF;
    c = (arg0->f3bc == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    arg0->f3bc = lo | hi;
    FUN_001f7250(arg0->f3bc);
}
