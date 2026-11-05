int FUN_001e81f0();
extern int DAT_0048ac00[4];
struct E { int a, b, c, d, e; };
void FUN_00174640(int arg0, int arg1) {
    struct E *tab;
    int var_a0 = 2, var_a1 = 2, var_a2 = 2, var_a3 = 0, var_a4 = -1;
    int base = (arg1 << 2) + arg0;
    int *temp_a5 = (int *)base;
    struct E *ent;

    tab = (struct E *)DAT_0048ac00[temp_a5[259]];
    if (tab != 0) {
        ent = tab + temp_a5[275];
        var_a4 = ent->e;
        var_a0 = ent->a;
        var_a1 = ent->b;
        var_a2 = ent->c;
        var_a3 = ent->d;
        if (var_a4 == -2) {
            var_a4 = temp_a5[291];
        }
    }
    if (var_a4 == -1) {
        var_a0 = 2;
        var_a3 = 0;
        var_a1 = 2;
        var_a2 = 2;
        var_a4 = 0x80;
    }
    FUN_001e81f0(var_a0, var_a1, var_a2, var_a3, var_a4, temp_a5, tab);
}
