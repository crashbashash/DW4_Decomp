extern "C" {
int FUN_0026ce40(int);
void FUN_00332370(void *arg0) {
    int temp_a0 = *(int *)((char *)(arg0) + 44);
    if (temp_a0 != 0) {
        FUN_0026ce40(temp_a0);
        asm { nop }
    }
}
}
