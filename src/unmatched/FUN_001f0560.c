typedef struct S { long long v; char pad0[24]; int w32; char pad1[12]; int w48; char pad2[12]; unsigned char b0:1; unsigned char b1:1; unsigned char b2:1; unsigned char b3:1; unsigned char b4:1; unsigned char b5:1; unsigned char b6:1; unsigned char b7:1; } S;
extern S *DAT_00568f04[4];
extern S *DAT_00568f34[4];
long long FUN_001f0560(void) {
    S *p;
    long long r;
    p = DAT_00568f04[0];
    r = p->v;
    if (p->w48 == p->w32) {
        p = DAT_00568f34[0];
        r = p->v;
    }
    p->b2 = 1;
    return r;
}
