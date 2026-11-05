/* 0x002a02d8 — FUN_002a02d8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0340();
int FUN_002b17d8();
int FUN_002b18a0();

void FUN_002a02d8(void *arg0) {
    int temp_v0;

    temp_v0 = FUN_002b17d8((char *)arg0 + 0x94, *(int *)((char *)(arg0) + 144));
    if (temp_v0 != 0) {
        FUN_002a0340(temp_v0, arg0);
        FUN_002b18a0(temp_v0);
    }
}
