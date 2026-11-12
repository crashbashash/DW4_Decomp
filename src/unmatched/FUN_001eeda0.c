int FUN_001eed50();
int p2WaitDmaSequence();

void FUN_001eeda0(void *arg0) {
    p2WaitDmaSequence(1, *(long long *)((char *)(arg0) + 0));
    if ((((unsigned long long) *(unsigned char *)((char *)(arg0) + 28) << 62) >> 63) != 0) {
        FUN_001eed50(arg0);
    }
}
