void FUN_00182090(void *arg0, void *arg1, void *arg2, float fparg0) {
    float r0;
    float r1;
    float r2;
    float r3;
    r0 = *(float *)((char *)(arg1) + 0) + (*(float *)((char *)(arg2) + 0) * fparg0);
    r3 = *(float *)((char *)(arg1) + 12) + (*(float *)((char *)(arg2) + 12) * fparg0);
    r2 = *(float *)((char *)(arg1) + 8) + (*(float *)((char *)(arg2) + 8) * fparg0);
    r1 = *(float *)((char *)(arg1) + 4) + (*(float *)((char *)(arg2) + 4) * fparg0);
    *(float *)((char *)(arg0) + 0) = r0;
    *(float *)((char *)(arg0) + 4) = r1;
    *(float *)((char *)(arg0) + 8) = r2;
    *(float *)((char *)(arg0) + 12) = r3;
}
