/* 0x001d8470 — FUN_001d8470. m2c draft with dropped/gap parameters restored; verified
 * byte-identical by tools/verify.py (loop: tools/m2c_loop.py). */
int ObjectList_AppendRetained();

void FUN_001d8470(void *arg0, int dummy1, int arg2, int arg3) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 8));
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 12), arg2);
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 20), arg3);
}
