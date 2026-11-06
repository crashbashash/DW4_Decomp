/* Passes two values to FUN_002a0d00 on the handle's error block (+2544), or the global one without
 * a handle; returns 0. */
typedef struct SfdHandle {
    char pad0[2544];
    char errorBlock[4];     /* +2544 */
} SfdHandle;

extern char DAT_004bea74[];
extern void FUN_002a0d00(void *errorBlock, int a, int b);
extern int FUN_002a0dd8(SfdHandle *handle);
extern int FUN_002a0bb8(SfdHandle *handle, int code);

int FUN_002a0c68(SfdHandle *handle, int a, int b) {
    if (handle == 0) {
        FUN_002a0d00(DAT_004bea74, a, b);
    } else {
        if (FUN_002a0dd8(handle) != 0) {
            return FUN_002a0bb8(0, 0xFF000101);
        }
        FUN_002a0d00(handle->errorBlock, a, b);
    }
    return 0;
}
