/* 0x00305d00 — FUN_00305d00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int ObjectList_ResizeRetained(int, int);
int Gap__Core__igObject__vfunc_09();

void FUN_00305d00(void *arg0) {
    Gap__Core__igObject__vfunc_09();
    ObjectList_ResizeRetained(*(int *)((char *)arg0 + 8), 0x100);
}
