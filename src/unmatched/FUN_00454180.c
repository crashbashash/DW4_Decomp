int FUN_00453be0();

void FUN_00454180(void *arg0) {
    int *t;
    int i;
    i = 0;
    while (t = *(int **)((char *)arg0 + 40), i < t[2]) {
        FUN_00453be0(*(int *)(t[4] + (i * 4)), *(int *)((char *)(arg0) + 8) + 0x10);
        i += 1;
    }
}
