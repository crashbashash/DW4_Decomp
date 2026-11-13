/* Passes two values to FUN_002a0d00 on the handle's error block (+2544), or the global one without
 * a handle; returns 0. */
typedef struct SfdHandle {
    char pad0[2544];
    char errorBlock[4];     /* +2544 */
} SfdHandle;

extern char DAT_004bea74[];
extern void FUN_002a0d00(void *errorBlock, int a, int b);
extern int sfd_CheckHn(SfdHandle *handle);
extern int sfd_ReportError(SfdHandle *handle, int code);

int FUN_002a0c68(SfdHandle *handle, int a, int b) {
    if (handle == 0) {
        FUN_002a0d00(DAT_004bea74, a, b);
    } else {
        if (sfd_CheckHn(handle) != 0) {
            return sfd_ReportError(0, 0xFF000101);
        }
        FUN_002a0d00(handle->errorBlock, a, b);
    }
    return 0;
}
