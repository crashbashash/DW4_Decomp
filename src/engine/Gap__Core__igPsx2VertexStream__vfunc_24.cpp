extern "C" {
int FUN_00180020(...);
struct Obj;
Obj *FUN_0015f4a0(int, int, int);
void igObject_Destroy(void *);
}
class Buf { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v23(); int w4; int w8; int w12; int f16; };
struct Obj { int w0; unsigned refs; int w8; Buf *buf; int p16; int p20; int f24; };
struct Ref {
    Obj *p;
    Ref(Obj *o) { p = o; if (p) p->refs++; }
    ~Ref() { Obj *o; if ((o = p) != 0) { --o->refs; if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Dst { int f0; int f4; int f8; int f12; int f16; int f20; int f24; };
struct Src { char pad[20]; int f20; int f24; };
extern "C" void Gap__Core__igPsx2VertexStream__vfunc_24(Src *self, Dst *x) {
    if (self->f24 == 0) FUN_00180020();
    int k = self->f24;
    if (!(k == 2 || k == 3)) {
        Ref r(FUN_0015f4a0(self->f20, x->f0, x->f12));
        int s = r.p->f24;
        int c = r.p->buf->v23();
        int a2 = c * s;
        x->f16 = r.p->buf->f16 + x->f4 * a2;
        x->f20 = a2;
        x->f8 = r.p->buf->w8 - x->f4;
    }
    x->f24 = 1;
}
