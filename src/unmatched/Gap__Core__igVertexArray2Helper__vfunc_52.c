void *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_00586808[4];

typedef struct O { char pad[12]; void *f12; } O;
typedef struct Q { char pad[16]; float *f16; } Q;
typedef struct A { char pad[12]; int f12; } A;

float Gap__Core__igVertexArray2Helper__vfunc_52(A *arg0, int arg1) {
    Q *var_s0;
    Q *t;

    t = (Q *)((O *)igVertexArray2__FindVertexData(arg0->f12, 9, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_00586808[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16[arg1];
}
