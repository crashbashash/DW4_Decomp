void FUN_0017c6e0(int arg0) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_a3;
    void *temp_a2;

    var_a3 = 0;
    do {
        temp_a2 = (void *)(arg0 + (var_a3 * 4));
        var_a3 += 1;
        *(int *)((char *)(temp_a2) + 580) = 1;
        *(int *)((char *)(temp_a2) + 644) = 0;
    } while (var_a3 < 0x10);
}
