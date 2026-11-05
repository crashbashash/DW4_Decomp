/* 0x002e2250 — FUN_002e2250. m2c draft, hybrid; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_002e2350();

void *FUN_002e2250(void *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8) {
    FUN_002e2350();
    *(int *)((char *)arg0 + 0) = 0xD;
    *(int *)((char *)arg0 + 20) = arg1;
    *(int *)((char *)arg0 + 24) = arg2;
    *(int *)((char *)arg0 + 28) = arg3;
    *(int *)((char *)arg0 + 44) = arg4;
    *(int *)((char *)arg0 + 48) = arg5;
    *(int *)((char *)arg0 + 52) = arg6;
    *(int *)((char *)arg0 + 56) = arg7;
    *(int *)((char *)arg0 + 68) = arg_sp0;
    *(int *)((char *)arg0 + 72) = arg_sp8;
    return arg0;
}
