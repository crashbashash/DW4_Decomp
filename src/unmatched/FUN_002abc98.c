/* 0x002abc98 — FUN_002abc98 (100 bytes). Adds to the counter at +2388 and passes the block at +2384 to the optional callback read from option 37. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdBlock2384 {
    int f0;
    int count;              /* +4 */
} SfdBlock2384;

typedef struct SfdHandle {
    char pad0[2384];
    SfdBlock2384 block;     /* +2384 */
} SfdHandle;

typedef void (*SfdNotify)(SfdHandle *handle, int arg, SfdBlock2384 *block);

extern SfdNotify FUN_002adc40(SfdHandle *handle, int option);

void FUN_002abc98(SfdHandle *handle, int delta, int arg) {
    SfdBlock2384 *block = &handle->block;
    SfdNotify notify;

    block->count += delta;
    notify = FUN_002adc40(handle, 37);
    if (notify != 0) {
        notify(handle, arg, block);
    }
}
