/* 0x002a6768 — FUN_002a6768 (24 bytes). Reads the two words at +2732/+2736 of a handle into caller variables. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdBlock2564 {
    char pad0[168];
    int f168;               /* handle +2732 */
    int f172;               /* handle +2736 */
} SfdBlock2564;

typedef struct SfdHandle {
    char pad0[2564];
    SfdBlock2564 block;     /* +2564 */
} SfdHandle;

void FUN_002a6768(SfdHandle *handle, int unused, int *first, int *second) {
    SfdBlock2564 *block = &handle->block;

    *second = block->f172;
    *first = block->f168;
}
