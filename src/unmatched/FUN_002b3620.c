/* 0x002b3620 — FUN_002b3620. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b3098();

void FUN_002b3620(void *arg0, void *arg1) {
    FUN_002b3098(*(int *)((char *)(arg0) + 52), *(int *)((char *)(arg1) + 76), *(int *)((char *)(arg0) + 64));
}
