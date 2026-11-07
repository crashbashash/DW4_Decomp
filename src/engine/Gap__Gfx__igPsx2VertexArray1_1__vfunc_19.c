struct VertexColorBuffer { char p[8]; unsigned int *data; };
struct VertexArrayColorView { char p0[8]; struct VertexColorBuffer *b; unsigned int count; unsigned int f16_pad; int f20; int pad24; int f28; char pad32[32]; long long f64; };
int FUN_0017d2b0();
int FUN_001f05a0(int, long long);

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_19(struct VertexArrayColorView *s) {
    unsigned int i;
    unsigned int *p;
    unsigned int x;
    unsigned int hi;
    if (s->f20 & 4) {
        FUN_001f05a0(1, s->f64);
    }
    FUN_0017d2b0(s);
    if (s->f28 & 4) {
        p = s->b->data;
        for (i = 0; i < s->count; i++) {
            x = *p;
            hi = (x & 0x80000000) >> 7;
            *p = (x & 0xffffff) | (hi + (((x & 0xff000000) - hi) * 2));
            p++;
        }
    }
}
