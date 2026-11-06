int FUN_00299558();
int FUN_0029b178();

void FUN_0029a8e0(void *arg0) {
    int temp_a0;
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 68);
    if ((temp_v0 != 0) && (FUN_0029b178(temp_v0) != 0)) {
        *(int *)((char *)(arg0) + 8) = 4;
    }
    temp_a0 = *(int *)((char *)(arg0) + 76);
    if ((temp_a0 != 0) && (FUN_00299558(temp_a0) == 1)) {
        *(int *)((char *)(arg0) + 8) = 4;
    }
}
