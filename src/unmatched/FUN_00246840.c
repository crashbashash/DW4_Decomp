/* 0x00246840 — FUN_00246840. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002468a0(int, int, int, int);
int FUN_002468e0();

void FUN_00246840(int arg0) {
    FUN_002468e0();
    FUN_002468a0(arg0, *(int *)0x56DF68, *(int *)0x498720, *(int *)0x498718);
    *(int *)0x56DF60 = (int) (*(int *)0x56DF60 + 1);
}
