int FUN_00267228();
int FUN_0026c468();

void FUN_0026dd08(void *arg0) {
    if (FUN_00267228(*(int *)((char *)(arg0) + 4)) == 1) {
        FUN_0026c468(arg0, 0, *(short *)((char *)(arg0) + 66));
        return;
    }
    FUN_0026c468(arg0, 0, *(short *)((char *)(arg0) + 66));
    FUN_0026c468(arg0, 1, *(short *)((char *)(arg0) + 68));
}
