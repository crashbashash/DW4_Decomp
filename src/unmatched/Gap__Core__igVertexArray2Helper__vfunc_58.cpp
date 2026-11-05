extern "C" {
struct Q { char pad[12]; void *f12; };
Q *igVertexArray2__FindVertexData(void *, int, int);
int igObject_IsKindOf(void *, int);
extern int DAT_00586808[4];
}
class H { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(); virtual int v100(); int pad4[2]; void *f12; };
extern "C" void Gap__Core__igVertexArray2Helper__vfunc_58(H *arg0, unsigned int *arg1);
void Gap__Core__igVertexArray2Helper__vfunc_58(H *arg0, unsigned int *arg1) {
    Q *s3, *s2, *s1, *s6, *s7, *s8, *spAC, *s0;
    void *x;
    void *y;
    unsigned int v;
    int n;
    unsigned char sel;
    s3 = igVertexArray2__FindVertexData(arg0->f12, 1, 0);
    s2 = igVertexArray2__FindVertexData(arg0->f12, 3, 0);
    s1 = igVertexArray2__FindVertexData(arg0->f12, 2, 0);
    s6 = igVertexArray2__FindVertexData(arg0->f12, 5, 0);
    s7 = igVertexArray2__FindVertexData(arg0->f12, 6, 0);
    s8 = igVertexArray2__FindVertexData(arg0->f12, 8, 0);
    spAC = igVertexArray2__FindVertexData(arg0->f12, 7, 0);
    s0 = igVertexArray2__FindVertexData(arg0->f12, 9, 0);
    if (s3 != 0) {
        *arg1 |= 1;
    }
    if (s2 != 0) {
        *arg1 |= 2;
    }
    if (s1 != 0) {
        *arg1 |= 4;
    }
    if (s6 != 0) {
        v = arg0->v96() & 0xFF;
        *arg1 &= ~0xF0;
        *arg1 |= v << 4;
    }
    if (s7 != 0) {
        v = arg0->v100() & 0xFF;
        *arg1 &= ~0xF00;
        *arg1 |= v << 8;
    }
    if (s8 != 0) {
        *arg1 |= 0x800000;
    }
    if (spAC != 0) {
        *arg1 |= 0x400000;
    }
    if (s0 != 0) {
        x = s0->f12;
        if (x != 0 && igObject_IsKindOf(x, DAT_00586808[0]) != 0) {
            y = x;
        } else {
            y = 0;
        }
        if (((y != 0) ? 1 : 2) & 0xFF) {
            *arg1 &= 0xFFCFFFFF;
            *arg1 = *arg1 | ((((y != 0) ? 1 : 2) & 0xFF) << 0x14);
        } else {
            *arg1 = *arg1 & 0xFFCFFFFF;
        }
    }
    n = 0;
    while (igVertexArray2__FindVertexData(arg0->f12, 4, n) != 0) {
        n += 1;
    }
    *arg1 &= 0xFFF0FFFF;
    *arg1 |= (n & 0xFF) << 0x10;
}
