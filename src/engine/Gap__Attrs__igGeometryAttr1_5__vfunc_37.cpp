struct VertexFormat { int flags;
  bool has() const { return (flags & 0x800000) != 0; }
  void set() { flags |= 0x800000; }
};
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual VertexFormat *v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v152(int, void *); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual int v240(VertexFormat *, int, int, int); int pad[2]; unsigned f12; int pad2[1]; int f20; };
class A { public: int pad[3]; Obj *f12; };
class B { public: int pad[2]; unsigned f8; int pad1; char *f16; };
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Attrs__igGeometryAttr1_5__vfunc_37(int *arg0, A *arg1, B *arg2) {
    unsigned n;
    unsigned i;
    VertexFormat fl;
    Obj *o;
    o = arg1->f12;
    n = arg2->f8;
    if (o->f12 < n) {
        *arg0 = DAT_004fb418[0];
    } else {
        fl = *o->v100();
        if (!fl.has()) {
            fl.set();
            o = arg1->f12;
            o->v240(&fl, o->f12, o->f20, 0);
        }
        for (i = 0; i < n; i++) {
            o = arg1->f12;
            o->v152(i, arg2->f16 + i * 12);
        }
        *arg0 = DAT_004fb410[0];
    }
}
}
