/* Forwards the handle and its word at +8200 to FUN_0029ea88. */
typedef struct SfdHandle {
    char pad0[8200];
    int f8200;
} SfdHandle;

extern int FUN_0029ea88(SfdHandle *handle, int index);

void FUN_0029c380(SfdHandle *handle) {
    FUN_0029ea88(handle, handle->f8200);
}
