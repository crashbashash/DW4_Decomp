/* 0x00273fd0 — FUN_00273fd0 (148 bytes). Seeks a memory-file handle: sets the position (+12) from the start (origin 0), the end (+8, origin 2) or the current position (origin 1), clamps it to 0..size, clears +20 and returns it; a NULL handle is reported through FUN_002739b8 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct File_273fd0 {
    char pad0[8];
    int size;       /* 0x08 */
    int position;   /* 0x0c */
    int pad16;
    int pending;    /* 0x14 */
} File_273fd0;

extern char s_E0092912_handl_is_null_004f0348[]; /* 'E0092912:handl is null.' */
void FUN_002739b8(File_273fd0 *file, const char *message);

int FUN_00273fd0(File_273fd0 *file, int offset, int origin) {
    int position;

    if (file == 0) {
        FUN_002739b8(file, s_E0092912_handl_is_null_004f0348);
        return 0;
    }
    if (origin == 0) {
        file->position = offset;
    } else if (origin == 2) {
        file->position = file->size + offset;
    } else if (origin == 1) {
        file->position += offset;
    }
    position = file->position;
    file->pending = 0;
    if (position >= file->size) {
        position = file->size;
    }
    if (position < 0) {
        position = 0;
    }
    file->position = position;
    return position;
}

