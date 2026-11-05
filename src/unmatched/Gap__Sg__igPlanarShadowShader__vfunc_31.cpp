extern "C" int igObject_Destroy(...);
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct Rel { static inline void go(RO *o) { RO *t = o; if (t != 0) { t->u.w = t->u.w - 1; if (t->u.b.cnt == 0) igObject_Destroy(t); } } };
struct List {
    char pad[8]; int n; char pad2[4]; RO **data;
    void clear() {
        int cnt = n;
        int i;
        for (i = 0; i < cnt; i++) {
            Rel::go(data[i]);
        }
        int cnt2 = n;
        int j;
        for (j = 0; j < cnt2; j++) data[j] = 0;
        n = 0;
    }
};
struct Shader { char pad[80]; List *f80; List *f84; List *f88; RO *f92; RO *f96; };
extern "C" void Gap__Sg__igPlanarShadowShader__vfunc_31(Shader *arg0) {
    arg0->f80->clear();
    arg0->f84->clear();
    arg0->f88->clear();
    Rel::go(arg0->f92);
    arg0->f92 = 0;
    Rel::go(arg0->f96);
    arg0->f96 = 0;
}
