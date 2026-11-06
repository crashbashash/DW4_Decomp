/* Forwards the handle and its word at +8132 to FUN_0029ea88. */
typedef struct SfdHandle {
    char pad0[8132];
    int f8132;
} SfdHandle;

extern int FUN_0029ea88(SfdHandle *handle, int index);

void FUN_002a38f0(SfdHandle *handle) {
    FUN_0029ea88(handle, handle->f8132);
}
