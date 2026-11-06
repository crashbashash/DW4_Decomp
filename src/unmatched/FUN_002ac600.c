/* Validates the handle, clears +2408 and posts event (6, 12) with a value through FUN_002b0338. */
typedef struct SfdHandle {
    char pad0[2408];
    int f2408;              /* +2408 */
} SfdHandle;

extern int FUN_002a0dd8(SfdHandle *handle);
extern int FUN_002a0bb8(SfdHandle *handle, int code);
extern int FUN_002b0338(SfdHandle *handle, int group, int event, int a, int b);

void FUN_002ac600(SfdHandle *handle, int value) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000137);
        return;
    }
    handle->f2408 = 0;
    FUN_002b0338(handle, 6, 12, value, 0);
}
