struct A { int a,b,c,d; };
struct B { int a,b,c,d,e; };
struct A *igVertexArray2__FindVertexData(int, int, int);
int igObject_IsKindOf(void *, int);
extern int DAT_005610b8[4];
int Gap__Core__igVertexArray2Helper__vfunc_30(struct A *arg0, int arg1) {
    struct B *p = (struct B *)igVertexArray2__FindVertexData(arg0->d, 1, 0)->d;
    if (p != 0 && igObject_IsKindOf(p, DAT_005610b8[0]) != 0) {
        p = (struct B *)p;
    } else {
        p = 0;
    }
    return p->e + arg1 * 12;
}
