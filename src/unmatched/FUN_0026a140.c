int FUN_0026a140(void *arg0, int arg1) {
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 20);
    *(int *)((char *)(arg0) + 88) = arg1;
    if (temp_v0 < arg1) {
        *(int *)((char *)(arg0) + 88) = temp_v0;
    }
    return *(int *)((char *)(arg0) + 88);
}
