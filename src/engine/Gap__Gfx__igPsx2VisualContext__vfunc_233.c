struct S { char pad[1277]; unsigned char f; };
int FUN_00174db0();
int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_005609ac[4];
extern unsigned char GPR_00554b5c;
void Gap__Gfx__igPsx2VisualContext__vfunc_233(struct S *s, int v) {
    int m;
    if (GPR_00554b5c != 0) {
        v = 0;
    }
    m = v & 0xFF;
    if (s->f == m) {
        DAT_005609ac[0] += 1;
    }
    if (s->f != m) {
        s->f = v;
        if (v != 0) {
            FUN_001e74b0(0);
            FUN_00174db0(s);
            return;
        }
        FUN_001e7500(0);
    }
}
