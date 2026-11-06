void FUN_002671a8(void *arg0, int arg1, int arg2) {
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    *(int *)((char *)arg0 + 80) = arg1;
    *(int *)((char *)arg0 + 84) = arg2;
}
