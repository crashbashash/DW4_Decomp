void *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_005610b8[4];

typedef struct V { float x; float y; float z; } V;
typedef struct O { char pad[12]; void *f12; } O;
typedef struct Q { char pad[16]; V *f16; } Q;
typedef struct A { char pad[12]; int f12; } A;

void Gap__Gfx__igVertexArray2Helper__vfunc_32(A *arg0, int arg1, V *arg2) {
    V *temp_v1;
    Q *var_s0;
    Q *t;

    t = (Q *)((O *)igVertexArray2__FindVertexData(arg0->f12, 3, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, DAT_005610b8[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    temp_v1 = var_s0->f16 + arg1;
    arg2->x = temp_v1->x;
    arg2->y = temp_v1->y;
    arg2->z = temp_v1->z;
}
