void *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_005610b8[4];

typedef struct V { float x; float y; float z; } V;
typedef struct O { char pad[12]; void *f12; } O;
typedef struct Q { char pad[16]; V *f16; } Q;
typedef struct A { char pad[12]; int f12; } A;

V *Gap__Core__igVertexArray2Helper__vfunc_39(A *arg0, int arg1) {
    Q *var_s0;
    Q *t;

    t = (Q *)((O *)igVertexArray2__FindVertexData(arg0->f12, 8, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_005610b8[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16 + arg1;
}
