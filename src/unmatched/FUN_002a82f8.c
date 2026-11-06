int FUN_002a0bb8();
int FUN_002a0dd8();
void *FUN_002a8440();

void FUN_002a82f8(void *arg0, int arg1) {
    void *temp_v0;

    if (FUN_002a0dd8() != 0) {
        FUN_002a0bb8(0, 0xFF000188);
        return;
    }
    temp_v0 = (void *)(FUN_002a8440(arg0, arg1));
    if (temp_v0 == 0) {
        FUN_002a0bb8(arg0, 0xFF000F30);
    } else {
        *(int *)((char *)(temp_v0) + 4) = (int)((int) (*(int *)((char *)(temp_v0) + 4) + 1));
    }
    *(int *)((char *)(arg0) + 2428) = (int)((int) (*(int *)((char *)(arg0) + 2428) + 1));
}
