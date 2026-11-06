/* Forwards the handle and its word at +8128 to FUN_0029ea88. */
typedef struct SfdHandle {
    char pad0[8128];
    int f8128;
} SfdHandle;

extern int FUN_0029ea88(SfdHandle *handle, int index);

void FUN_002a4bb0(SfdHandle *handle) {
    FUN_0029ea88(handle, handle->f8128);
}
