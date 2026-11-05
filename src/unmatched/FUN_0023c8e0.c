/* 0x0023c8e0 — FUN_0023c8e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern void * DAT_0056de90[4];
void *FUN_0023c8e0(void *arg0, int arg1, int arg2) {
    *(int *)((char *)(arg0) + 0) = arg2;
    *(int *)((char *)(arg0) + 4) = arg1;
    *(int *)((char *)(arg0) + 12) = (int)((int) DAT_0056de90[0]);
    *(int *)((char *)(arg0) + 16) = 0;
    if (DAT_0056de90[0] != 0) {
        *(int *)((char *)(DAT_0056de90[0]) + 16) = (int)(arg0);
    }
    DAT_0056de90[0] = (void *)(arg0);
    return arg0;
}
