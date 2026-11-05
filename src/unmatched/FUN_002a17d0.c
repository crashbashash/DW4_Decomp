/* 0x002a17d0 — FUN_002a17d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_002a17d0(void *arg0) {
    return (char *)arg0 + (*(int *)((char *)(arg0) + 8060) * 0x74) + 0x1318;
}
