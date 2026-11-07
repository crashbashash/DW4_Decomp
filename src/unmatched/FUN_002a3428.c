int FUN_0028f098();
int FUN_002a0bb8();
int FUN_002a0dd8();

int FUN_002a3428(void *arg0, int arg1, int arg2, int arg3, int arg4) {
    if (FUN_002a0dd8() != 0) {
        return FUN_002a0bb8(0, 0xFF000184, arg2, arg3, arg4);
    }
    FUN_0028f098(**(int **)((char *)(arg0) + 8120), arg1, arg2, arg3, arg4);
    return 0;
}
