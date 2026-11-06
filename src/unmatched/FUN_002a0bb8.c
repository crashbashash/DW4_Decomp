/* Records an error code: on the handle's error block (+2544, and makes +72 non-positive) or on the
 * global one without a handle; returns the code. */
typedef struct SfdHandle {
    char pad0[72];
    int f72;                /* +72 */
    char pad76[2468];
    char errorBlock[4];     /* +2544 */
} SfdHandle;

extern char DAT_004bea74[];
extern void FUN_002a0c28(void *errorBlock, int code);

int FUN_002a0bb8(SfdHandle *handle, int code) {
    int result = 0;

    if (code != 0) {
        if (handle == 0) {
            FUN_002a0c28(DAT_004bea74, code);
        } else {
            FUN_002a0c28(handle->errorBlock, code);
            if (handle->f72 > 0) {
                handle->f72 = -handle->f72;
            }
        }
        result = code;
    }
    return result;
}
