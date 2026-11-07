typedef struct { char pad[1020]; unsigned char f; } S;
extern long long DAT_005608a8[4];
extern unsigned char GPR_00554b4c;

void Gap__Gfx__igPsx2VisualContext__vfunc_211(S *arg0, int arg1) {
    int var_a1;

    var_a1 = arg1;
    if (GPR_00554b4c != 0) {
        var_a1 = 0;
    }
    if (arg0->f == (var_a1 & 0xFF)) {
        DAT_005608a8[0] += 1;
    }
    arg0->f = var_a1;
}
