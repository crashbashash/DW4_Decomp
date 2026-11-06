void *FUN_004555c0();
struct N { char pad[24]; struct N *f24; };
struct O { char pad[12]; struct M *f12; };
struct M { char pad[164]; void *f164; };

void *FUN_00456e10(struct O *arg0, struct N *arg1, int arg2) {
    struct N *temp_s0;
    void *var_v0;

    if (arg1 != 0) {
        while (1) {
            temp_s0 = arg1->f24;
            if (temp_s0 == 0) {
                return 0;
            }
            var_v0 = FUN_004555c0(temp_s0, arg1, arg2);
            arg1 = temp_s0;
            if (var_v0 != 0) {
                break;
            }
        }
    } else {
        var_v0 = arg0->f12->f164;
    }
    while (var_v0 != 0) {
        arg1 = (struct N *)var_v0;
        var_v0 = FUN_004555c0(var_v0, 0, arg2);
    }
    return arg1;
}
