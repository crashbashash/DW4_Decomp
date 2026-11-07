int FUN_00172330();
extern int DAT_00560900[4];
struct T { char pad[48]; float v[4]; };
struct S { char pad[1344]; struct T *f1344; };
void Gap__Gfx__igPsx2VisualContext__vfunc_104(struct S *arg0, float *arg1) {
    float *temp_a2;
    struct T *temp_v1;
    int var_v0;
    struct T *temp_v0;

    temp_v1 = arg0->f1344;
    var_v0 = 1;
    temp_a2 = temp_v1->v;
    if (temp_v1->v[0] != arg1[0]) {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[1] != arg1[1]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[2] != arg1[2]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[3] != arg1[3]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        DAT_00560900[0] += 1;
    }
    temp_v0 = arg0->f1344;
    temp_v0->v[0] = arg1[0];
    temp_v0->v[1] = arg1[1];
    temp_v0->v[2] = arg1[2];
    temp_v0->v[3] = arg1[3];
    FUN_00172330(arg0, arg0->f1344);
}
