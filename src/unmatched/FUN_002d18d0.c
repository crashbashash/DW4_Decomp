/* 0x002d18d0 — FUN_002d18d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00308320();
extern int DAT_004f9300[4];
extern unsigned char GPR_00554bf8;

void FUN_002d18d0(void *arg0, int arg1) {
    int temp_v0;

    if ((arg1 != 0xC80) && (*(unsigned char *)((char *)(arg0) + 121) == 1) && (GPR_00554bf8 == 0)) {
        temp_v0 = FUN_00308320(&DAT_004f9300[0], 0xC80, arg1);
        if ((temp_v0 != 1) && (temp_v0 == 2)) {
            GPR_00554bf8 = 1;
        }
    }
}
