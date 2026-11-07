struct O;
int FUN_001e8850(float, float, float);
extern int DAT_005609d8[4];
struct O { char pad[1312]; float f0; float f4; float f8; float f12; };
struct V { float f0; float f4; float f8; float f12; };
void Gap__Gfx__igPsx2VisualContext__vfunc_247(struct O *arg0, struct V *arg1) {
    int var_v0;
    var_v0 = 1;
    if (arg0->f0 != arg1->f0) {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (arg0->f4 != arg1->f4) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (arg0->f8 != arg1->f8) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (arg0->f12 != arg1->f12) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        DAT_005609d8[0] += 1;
    }
    arg0->f0 = arg1->f0;
    arg0->f4 = arg1->f4;
    arg0->f8 = arg1->f8;
    arg0->f12 = arg1->f12;
    FUN_001e8850(arg1->f0, arg1->f4, arg1->f8);
}
