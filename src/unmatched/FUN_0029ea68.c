/* 0x0029ea68 — FUN_0029ea68 (32 bytes). Stores a value in the first word of stream slot \`index\` (116-byte slots at +4884). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdStreamSlot {
    int f0;
    char pad4[112];
} SfdStreamSlot;

typedef struct SfdHandle {
    char pad0[4884];
    SfdStreamSlot slots[1]; /* +4884, 116 bytes each */
} SfdHandle;

void FUN_0029ea68(SfdHandle *handle, int index, int value) {
    SfdStreamSlot *slot = &handle->slots[index];

    slot->f0 = value;
}
