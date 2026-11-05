/* 0x0015d050 — FUN_0015d050. m2c draft with dropped/gap parameters restored; verified
 * byte-identical by tools/verify.py (loop: tools/m2c_loop.py). */
void FUN_0015d050(void *arg0, int dummy1, void *arg2) {
    float temp_f0;

    temp_f0 = 0.5f * *(float *)((char *)(arg0) + 28);
    *(float *)((char *)(arg2) + 0) = temp_f0;
    *(float *)((char *)(arg2) + 4) = temp_f0;
}
