/* 0x00275bf0 — FUN_00275bf0 (148 bytes). Seeks a memory-file handle: sets the position (+28) from the start (origin 0), the end (+16, origin 2) or the current position (origin 1), clamps it to 0..size, clears +40 and returns it; a NULL handle is reported through FUN_002753d8 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct File_275bf0 {
    char pad0[16];
    int size;       /* 0x10 */
    int pad20[2];
    int position;   /* 0x1c */
    int pad32[2];
    int pending;    /* 0x28 */
} File_275bf0;

extern char E0092712_handl_is_null[]; /* 'E0092712:handl is null.' */
void FUN_002753d8(File_275bf0 *file, const char *message);

int FUN_00275bf0(File_275bf0 *file, int offset, int origin) {
    int position;

    if (file == 0) {
        FUN_002753d8(file, E0092712_handl_is_null);
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


