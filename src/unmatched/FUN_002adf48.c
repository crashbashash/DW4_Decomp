/* 0x002adf48 — FUN_002adf48 (48 bytes). Reads the word behind the pointer of 0x44-byte entry `index` (at ctx+7984 + index*0x44) into *out, or 0 when that pointer is null. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* View of one 0x44-byte entry as indexed from ctx (see also FUN_002ad828, which indexes the same table from ctx+7976). */
struct Entry44At1F30 {
    char pad[7984];
    int *f7984;
};

void FUN_002adf48(char *ctx, int index, int *out) {
    int *value = ((struct Entry44At1F30 *)(ctx + index * 0x44))->f7984;

    if (value == 0) {
        *out = 0;
        return;
    }
    *out = *value;
}
