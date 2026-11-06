/* Sets flag 7 through FUN_002b03b8 once stream +8468 reports 1 and flag 7 is not already 1. */
typedef struct SfdHandle {
    char pad0[8468];
    int f8468;              /* +8468 */
} SfdHandle;

extern int FUN_002b03d0(SfdHandle *handle, int flag);
extern int FUN_0029ea88(SfdHandle *handle, int index);
extern int FUN_002b03b8(SfdHandle *handle, int flag, int value);

void FUN_0029d228(SfdHandle *handle) {
    if (FUN_002b03d0(handle, 7) != 1 && FUN_0029ea88(handle, handle->f8468) == 1) {
        FUN_002b03b8(handle, 7, 1);
    }
}
