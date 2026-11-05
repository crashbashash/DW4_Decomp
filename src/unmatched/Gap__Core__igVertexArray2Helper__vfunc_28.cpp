extern "C" {
struct Q { char pad[12]; void *f12; };
Q *igVertexArray2__FindVertexData(void *, int, int);
int igObject_IsKindOf(void *, int);
extern int DAT_005610b8[4];
}
struct V { float x, y, z; };
struct A {
    char pad[8]; int f8; char pad2[4]; V *f16;
    static inline A *Cast(A *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_005610b8[0]) != 0) {
            return p;
        }
        return 0;
    }
};
struct H { char pad[12]; void *f12; };
extern "C" void Gap__Core__igVertexArray2Helper__vfunc_28(H *arg0, int arg1, V *arg2) {
    A *a = A::Cast((A *)igVertexArray2__FindVertexData(arg0->f12, 1, 0)->f12);
    int n = a->f8;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        V *p = &a->f16[arg1];
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
    }
}
