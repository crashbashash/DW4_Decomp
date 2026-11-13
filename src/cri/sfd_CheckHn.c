/* Remembers the handle as the current one and returns 0 when it is live (+72 nonzero), else -1. */
typedef struct SfdHandle {
    char pad0[72];
    int f72;                /* +72 */
} SfdHandle;

extern SfdHandle *DAT_004be8d0;

int sfd_CheckHn(SfdHandle *handle) {
    DAT_004be8d0 = handle;
    if (handle == 0) {
        return -1;
    }
    return (handle->f72 != 0) ? 0 : -1;
}
