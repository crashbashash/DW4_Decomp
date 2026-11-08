extern int FUN_002a0dd8(void *handle);
extern int FUN_002a0bb8(void *handle, int code);
extern int FUN_0029ea88(void *handle, int id);
extern void FUN_0029ea68(void *handle, int id, int v);

int FUN_002ac498(void *handle) {
    int id;

    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000135);
    }
    id = *(int *)((char *)handle + 7996);
    if (FUN_0029ea88(handle, id) == 1) {
        return 0;
    }
    FUN_0029ea68(handle, id, 1);
    *(int *)((char *)handle + 68) = 1;
    return 0;
}
