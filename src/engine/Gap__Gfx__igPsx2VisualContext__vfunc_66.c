typedef struct S { char pad956[956]; int f3bc; } S;
int FUN_001f7250();
extern long long DAT_005608a0[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_66(S *arg0, unsigned int arg1) {
    unsigned long long lo;
    unsigned int hi;
    int c;

    hi = ((arg1 >> 1) & 0x7F000000) + (arg1 & 0x01000000);
    lo = arg1 & 0xFFFFFF;
    c = (arg0->f3bc == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    arg0->f3bc = lo | hi;
    FUN_001f7250(arg0->f3bc);
}
