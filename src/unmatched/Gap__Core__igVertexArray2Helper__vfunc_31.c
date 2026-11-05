struct A { char pad[12]; int f12; };
struct M { char pad[8]; int cnt; char p2[4]; char *data; };
struct H { char pad[12]; struct A *a; };
struct A *igVertexArray2__FindVertexData(struct A *, int, int);
int igObject_IsKindOf(struct M *, int);
extern int DAT_005610b8[4];
void Gap__Core__igVertexArray2Helper__vfunc_31(struct H *arg0, int arg1, float *arg2) {
    struct M *m = (struct M *)igVertexArray2__FindVertexData(arg0->a, 3, 0)->f12;
    int n;
    float *p;
    if (m != 0 && igObject_IsKindOf(m, DAT_005610b8[0]) != 0) { m = (struct M*)m; } else { m = 0; }
    n = m->cnt;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        p = (float *)(m->data + arg1 * 12);
        p[0] = arg2[0];
        p[1] = arg2[1];
        p[2] = arg2[2];
    }
}
