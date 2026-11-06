void FUN_00267dd8(void *arg0, short arg1, short arg2) {
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    *(short *)((char *)(arg0) + 4) = arg1;
    *(short *)((char *)(arg0) + 6) = arg2;
}
