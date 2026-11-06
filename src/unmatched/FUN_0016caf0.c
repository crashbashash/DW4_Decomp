int FUN_001e9740();

int FUN_0016caf0(void *arg0) {
    int temp_a1;
    temp_a1 = *(int *)((char *)(arg0) + 72);
    if (temp_a1 > 0) {
        FUN_001e9740(*(int *)((char *)(arg0) + 84), temp_a1);
    }
    *(int *)((char *)(arg0) + 964) = -1;
    return *(unsigned char *)((char *)(arg0) + 968) == 0;
}
