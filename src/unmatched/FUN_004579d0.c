/* 0x004579d0 — FUN_004579d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00457e90();
int Gap__Core__igObject__vfunc_11();

void FUN_004579d0(void *arg0) {
    Gap__Core__igObject__vfunc_11();
    *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 12) = (int)(arg0);
    FUN_00457e90(*(int *)((char *)(arg0) + 12), *(int *)((char *)(arg0) + 8));
}
