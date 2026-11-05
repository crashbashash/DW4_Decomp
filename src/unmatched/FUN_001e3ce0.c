/* 0x001e3ce0 — FUN_001e3ce0. m2c draft (build/m2c/FUN_001e3ce0.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int List_Reserve();

void FUN_001e3ce0(void *arg0) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg0 + 8);
    if (temp_a1 < *(int *)((char *)arg0 + 12)) {
        List_Reserve(arg0, temp_a1, 4);
    }
}
