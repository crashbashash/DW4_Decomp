extern "C" {
struct S { char pad[8]; int f8; int f12; int pad2; int f20; int f24; int f28; int f32; unsigned char f36; };
extern int igObject_GetAllocator(struct S *);
extern int FUN_002ed2b0(int, int, int);
int FUN_00331fb0(struct S *s, int a, int b, int c, int d) {
    if (s->f36 == 0) {
        int t, q, w;
        s->f20 = a;
        s->f24 = b;
        s->f28 = c;
        s->f32 = d;
        t = s->f32 / 1000 * (s->f20 * 25000) / 44;
        q = ((s->f28 + 1) * t + 0x800) / 0x800;
        w = (q << 11) + 0x24;
        { int m = s->f20 * 0x40C0; s->f12 = m + w + 0x40; }
        s->f8 = FUN_002ed2b0(s->f12, 16, igObject_GetAllocator(s));
        if (s->f8 == 0) return 0;
        s->f36 = 1;
    }
    return 1;
}
}
