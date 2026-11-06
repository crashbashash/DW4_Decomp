/* Validates the handle, then calls FUN_002aa538. */
extern int FUN_002a0dd8(void *handle);
extern int FUN_002a0bb8(void *handle, int code);
extern void FUN_002aa538(void *handle);

void FUN_002aa4f0(void *handle) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000143);
        return;
    }
    FUN_002aa538(handle);
}
