void FUN_0026efe0(void *arg0, short arg1, short arg2, short arg3) {
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    *(short *)((char *)(arg0) + 52) = arg1;
    *(short *)((char *)(arg0) + 54) = arg2;
    *(short *)((char *)(arg0) + 56) = arg3;
}
