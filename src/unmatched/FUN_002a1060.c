/* 0x002a1060 — FUN_002a1060 (24 bytes). Returns word +56 of the handle's record at +8052, or -1 without a handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdRecord8052 {
    char pad0[56];
    int f56;
} SfdRecord8052;

typedef struct SfdHandle {
    char pad0[8052];
    SfdRecord8052 *record;  /* +8052 */
} SfdHandle;

int FUN_002a1060(SfdHandle *handle) {
    if (handle == 0) {
        return -1;
    }
    return handle->record->f56;
}
