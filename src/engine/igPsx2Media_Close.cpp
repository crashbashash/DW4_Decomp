struct R { int v; R() {} R(const R &o) : v(o.v) {} };
struct VC {
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
 virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
 virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
 virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual R vY();
 virtual void d30();
 virtual R vX(int);
};
struct A { int p0; int p4; int p8; int f0c; VC *obj; int p14; int p18; char *tbl; };
struct T { int p0; int p4; int p8; char *rows; };
extern "C" {
R igPsx2IopRpcConnection_CallWithData(int, int, int, int *, int);
void igPsx2Media_Close(A *arg0, int arg1);
}
void igPsx2Media_Close(A *arg0, int arg1) {
    int q;
    R r1 = arg0->obj->vX(1);
    R r2 = igPsx2IopRpcConnection_CallWithData(arg0->f0c, 3, *(int *)(((T *)arg0->tbl)->rows + arg1 * 12 + 8), &q, 1);
    R r3 = arg0->obj->vY();
}
