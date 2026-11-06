/* Validates the handle, then posts event (0, 9) with a value through FUN_002b0338. */
extern int FUN_002a0dd8(void *handle);
extern int FUN_002a0bb8(void *handle, int code);
extern int FUN_002b0338(void *handle, int group, int event, int a, int b);

void FUN_002ac3a8(void *handle, int value) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000134);
        return;
    }
    FUN_002b0338(handle, 0, 9, value, 0);
}
