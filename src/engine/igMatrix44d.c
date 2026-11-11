void FUN_00190250(long long *arg0) {
    long long temp_v1;
    temp_v1 = 0x3FF00000LL << 0x20;
    arg0[0] = temp_v1;
    arg0[1] = 0;
    arg0[2] = 0;
    arg0[3] = 0;
    arg0[4] = 0;
    arg0[5] = temp_v1;
    arg0[6] = 0;
    arg0[7] = 0;
    arg0[8] = 0;
    arg0[9] = 0;
    arg0[10] = temp_v1;
    arg0[11] = 0;
    arg0[12] = 0;
    arg0[13] = 0;
    arg0[14] = 0;
    arg0[15] = temp_v1;
}

void FUN_001902a0(void *arg0, void *arg1) {
    *(long long *)((char *)(arg0) + 0) = (long long) *(long long *)((char *)(arg1) + 0);
    *(long long *)((char *)(arg0) + 8) = (long long) *(long long *)((char *)(arg1) + 8);
    *(long long *)((char *)(arg0) + 16) = (long long) *(long long *)((char *)(arg1) + 16);
    *(long long *)((char *)(arg0) + 24) = (long long) *(long long *)((char *)(arg1) + 24);
    *(long long *)((char *)(arg0) + 32) = (long long) *(long long *)((char *)(arg1) + 32);
    *(long long *)((char *)(arg0) + 40) = (long long) *(long long *)((char *)(arg1) + 40);
    *(long long *)((char *)(arg0) + 48) = (long long) *(long long *)((char *)(arg1) + 48);
    *(long long *)((char *)(arg0) + 56) = (long long) *(long long *)((char *)(arg1) + 56);
    *(long long *)((char *)(arg0) + 64) = (long long) *(long long *)((char *)(arg1) + 64);
    *(long long *)((char *)(arg0) + 72) = (long long) *(long long *)((char *)(arg1) + 72);
    *(long long *)((char *)(arg0) + 80) = (long long) *(long long *)((char *)(arg1) + 80);
    *(long long *)((char *)(arg0) + 88) = (long long) *(long long *)((char *)(arg1) + 88);
    *(long long *)((char *)(arg0) + 96) = (long long) *(long long *)((char *)(arg1) + 96);
    *(long long *)((char *)(arg0) + 104) = (long long) *(long long *)((char *)(arg1) + 104);
    *(long long *)((char *)(arg0) + 112) = (long long) *(long long *)((char *)(arg1) + 112);
    *(long long *)((char *)(arg0) + 120) = (long long) *(long long *)((char *)(arg1) + 120);
}

int FUN_00190330(int arg0, int arg1) {
    if (arg1 != arg0) {
        FUN_001902a0((void *)arg0, (void *)arg1);
    }
    return arg0;
}

void FUN_00190370(void)
{
}
