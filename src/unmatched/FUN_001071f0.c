unsigned int FUN_00106c88(char *d, int n);
void FUN_001071f0(char *d) {
    *(int *)(d + 380) = FUN_00106c88(d, 4);
    *(int *)(d + 384) = FUN_00106c88(d, 4);
    *(int *)(d + 388) = FUN_00106c88(d, 4);
    *(int *)(d + 392) = FUN_00106c88(d, 4);
    *(volatile unsigned int *)0x10002010 = (*(volatile unsigned int *)0x10002010 & ~0x30000) | (FUN_00106c88(d, 2) << 16);
    *(int *)(d + 396) = FUN_00106c88(d, 2);
    if (*(int *)(d + 236) == 0) {
        *(int *)(d + 236) = *(int *)(d + 396);
    }
    *(int *)(d + 400) = FUN_00106c88(d, 1);
    *(int *)(d + 404) = FUN_00106c88(d, 1);
    *(int *)(d + 408) = FUN_00106c88(d, 1);
    *(volatile unsigned int *)0x10002010 = (*(unsigned int *)0x10002010 & ~0x400000) | (FUN_00106c88(d, 1) << 22);
    *(volatile unsigned int *)0x10002010 = (*(unsigned int *)0x10002010 & ~0x200000) | (FUN_00106c88(d, 1) << 21);
    *(volatile unsigned int *)0x10002010 = (*(unsigned int *)0x10002010 & ~0x100000) | (FUN_00106c88(d, 1) << 20);
    *(int *)(d + 412) = FUN_00106c88(d, 1);
    FUN_00106c88(d, 1);
    *(int *)(d + 416) = FUN_00106c88(d, 1);
    if (FUN_00106c88(d, 1)) {
        FUN_00106c88(d, 1);
        FUN_00106c88(d, 3);
        FUN_00106c88(d, 1);
        FUN_00106c88(d, 7);
        FUN_00106c88(d, 8);
    }
}
