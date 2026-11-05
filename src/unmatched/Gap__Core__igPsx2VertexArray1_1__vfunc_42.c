extern float DAT_005548e0;
typedef struct B { char pad[8]; unsigned int *f8; } B;
typedef struct A { char pad[8]; B *f8; } A;
void Gap__Core__igPsx2VertexArray1_1__vfunc_42(A *arg0, int arg1, float *c) {
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
        s = DAT_005548e0;
    }
    ta = (unsigned int)(s * a) << 24;
    tb = (unsigned int)(255.0f * b) << 16;
    tg = (unsigned int)(255.0f * g) << 8;
    tr = (unsigned int)(255.0f * r);
    arg0->f8->f8[arg1] = ((ta | tb) | tg) | tr;
}
