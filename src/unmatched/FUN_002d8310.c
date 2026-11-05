/* 0x002d8310 — FUN_002d8310. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int ObjectList_AppendRetained();

void FUN_002d8310(void *arg0, void *arg1) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 28));
    *(int *)((char *)(arg1) + 12) = (int)(arg0);
}
