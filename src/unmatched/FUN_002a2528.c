/* 0x002a2528 — FUN_002a2528. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0029ea48();
int FUN_002a25b0();
int FUN_002a2620();
int FUN_002a2680();

void FUN_002a2528(void *arg0) {
    int temp_s0;

    if (FUN_002a25b0() != 1) {
        temp_s0 = *(int *)((char *)(arg0) + 8060);
        if ((FUN_0029ea48(arg0, temp_s0) == 1) && (FUN_002a2680(arg0, temp_s0) != 0)) {
            FUN_002a2620(arg0, 1);
        }
    }
}
