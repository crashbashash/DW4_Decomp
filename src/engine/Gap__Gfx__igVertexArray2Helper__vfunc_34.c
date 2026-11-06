void *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_005610b8[4];

typedef struct V { float x; float y; float z; } V;
typedef struct O { char pad[12]; void *f12; } O;
typedef struct Q { char pad[8]; int f8; char pad2[4]; V *f16; } Q;
typedef struct A { char pad[12]; int f12; } A;

void Gap__Gfx__igVertexArray2Helper__vfunc_34(A *arg0, int arg1, V *arg2) {
    Q *var_s1;
    Q *t;
    int n;
    V *p;

    t = (Q *)((O *)igVertexArray2__FindVertexData(arg0->f12, 7, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_005610b8[0]) != 0)) {
        var_s1 = t;
    } else {
        var_s1 = 0;
    }
    n = var_s1->f8;
    if ((n != 0) && (arg1 >= 0) && (arg1 < n)) {
        p = var_s1->f16 + arg1;
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
    }
}
