/* 0x002a3b48 — FUN_002a3b48 (36 bytes). Sets the flag at +3648 unless the limit at +3684 is unset (0x7FFFFFFF). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdBlock3648 {
    int flag;               /* +0 */
    char pad4[32];
    int limit;              /* +36 */
} SfdBlock3648;

typedef struct SfdHandle {
    char pad0[3648];
    SfdBlock3648 block;     /* +3648 */
} SfdHandle;

void FUN_002a3b48(SfdHandle *handle) {
    SfdBlock3648 *block = &handle->block;

    if (block->limit != 0x7FFFFFFF) {
        block->flag = 1;
    }
}
