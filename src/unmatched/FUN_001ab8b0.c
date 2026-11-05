/* 0x001ab8b0 — FUN_001ab8b0. m2c draft (build/m2c/FUN_001ab8b0.c), dropped leading call arguments restored; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_001ab770();
int FUN_001ab920();

int FUN_001ab8b0(int arg0, int arg1, void **arg2) {
    void *sp4C;

    sp4C = 0;
    FUN_001ab920(arg0, arg1, &sp4C);
    if (sp4C != 0) {
        *arg2 = sp4C;
        return *(int *)((char *)sp4C + 16);
    }
    return FUN_001ab770(arg0, arg1, arg2);
}
