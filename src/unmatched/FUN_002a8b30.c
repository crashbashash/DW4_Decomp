/* 0x002a8b30 — FUN_002a8b30. Matched with tools/dispatcher/regalloc.py: retail loads arg0's field
 * first (`lw v1,56(a0); lw v0,56(a1); slt v0,v0,v1`), so the comparison is written
 * `arg0->x > arg1->x`, not the m2c draft's `arg1->x < arg0->x`. */
int FUN_002a8b30(void *arg0, void *arg1) {
    int var_v0;

    var_v0 = 1;
    if (arg0 != 0) {
        var_v0 = *(int *)((char *)(arg0) + 56) > *(int *)((char *)(arg1) + 56);
    }
    return var_v0;
}
