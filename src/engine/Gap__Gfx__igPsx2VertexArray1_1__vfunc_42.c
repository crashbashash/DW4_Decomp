typedef struct ColorStreamView { char pad[8]; unsigned int *f8; } ColorStreamView;
typedef struct ColorArrayView { char pad[8]; ColorStreamView *f8; } ColorArrayView;
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_42(ColorArrayView *arg0, int arg1, float *c) {
    float s;
    float a;
    float b;
    float g;
    float r;
    unsigned int v;
    unsigned int ta;
    unsigned int tb;
    unsigned int tg;
    unsigned int tr;
    s = 128.0f;
    a = c[3];
    r = c[0];
    g = c[1];
    b = c[2];
    if (!(a <= 1.0f)) {
        s = 127.9f;
    }
    ta = (unsigned int)(s * a) << 24;
    tb = (unsigned int)(255.0f * b) << 16;
    tg = (unsigned int)(255.0f * g) << 8;
    tr = (unsigned int)(255.0f * r);
    arg0->f8->f8[arg1] = ((ta | tb) | tg) | tr;
}
