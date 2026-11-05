struct B { char pad[8]; float f8; float f12; float f16; float f20; float f24; float f28; };
int FUN_0018b050(struct B *arg0, struct B *arg1) {
    int var_v0;

    var_v0 = arg1->f8 <= arg0->f20;
    if (var_v0 != 0) {
        var_v0 = arg0->f8 <= arg1->f20;
    }
    if (var_v0 != 0) {
        var_v0 = arg1->f12 <= arg0->f24;
    }
    if (var_v0 != 0) {
        var_v0 = arg0->f12 <= arg1->f24;
    }
    if (var_v0 != 0) {
        var_v0 = arg1->f16 <= arg0->f28;
    }
    if (var_v0 != 0) {
        var_v0 = arg0->f16 <= arg1->f28;
    }
    return var_v0;
}