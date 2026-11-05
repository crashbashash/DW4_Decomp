typedef struct S { char pad44[44]; unsigned char *f2c; int f30; int f34; int f38; int f3c; } S;
char *Gap__Core__igPsx2File__vfunc_36(S *arg0, char *arg1, int arg2) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_a5;
    int temp_a3;
    int temp_v1;

    if (arg1 == 0) {
        return 0;
    }
    if (arg0->f3c != 0) {
        return 0;
    }
    temp_v1 = arg0->f38;
    temp_a3 = arg0->f34;
    if (temp_a3 >= temp_v1) {
        return 0;
    }
    arg2 = arg2 - 1;
    var_a5 = 0;
    if ((arg2 + temp_a3) >= temp_v1) {
        arg2 = temp_v1 - temp_a3;
    }
    while (var_a5 < arg2) {
        temp_a3 = arg0->f2c[arg0->f34];
        arg1[var_a5] = temp_a3;
        var_a5 += 1;
        arg0->f34 = arg0->f34 + 1;
        if (temp_a3 == 0xA) {
            break;
        }
    }
    arg1[var_a5] = 0;
    return arg1;
}
