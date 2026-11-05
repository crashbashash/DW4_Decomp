/* 0x00149030 — FUN_00149030. m2c draft with dropped/gap parameters restored; verified
 * byte-identical by tools/verify.py (loop: tools/m2c_loop.py; transform:
 * tools/restore_dropped_args.py). */
int FUN_00149030(void *arg0, int dummy1, int arg2, int arg3, int arg4) {
    *(int *)((char *)(arg0) + 8) = arg2;
    *(int *)((char *)(arg0) + 12) = arg3;
    *(int *)((char *)(arg0) + 44) = arg4;
    return 1;
}
