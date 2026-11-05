/* 0x00278190 — FUN_00278190 (188 bytes). Seeks a handle inside the FUN_00277da0/FUN_00277db8 lock: sets the position (+16) from the start (origin 0), the end (+12, origin 2) or the current position (origin 1), clamped to 0..size, and returns it; a NULL handle is reported through FUN_00277de8 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct File_278190 {
    char pad0[12];
    int size;       /* 0x0c */
    int position;   /* 0x10 */
} File_278190;

extern char s_E01100305_handl_is_null_004f0d88[]; /* 'E01100305:handl is null.' */
void FUN_00277de8(File_278190 *file, const char *message);
void FUN_00277da0(void);
void FUN_00277db8(void);

int FUN_00278190(File_278190 *file, int offset, int origin) {
    int position;

    if (file == 0) {
        FUN_00277de8(file, s_E01100305_handl_is_null_004f0d88);
        return 0;
    }
    FUN_00277da0();
    if (origin == 0) {
        file->position = offset;
    } else if (origin == 2) {
        file->position = file->size + offset;
    } else if (origin == 1) {
        file->position += offset;
    }
    position = file->position;
    if (position >= file->size) {
        position = file->size;
    }
    if (position < 0) {
        position = 0;
    }
    file->position = position;
    FUN_00277db8();
    return file->position;
}

