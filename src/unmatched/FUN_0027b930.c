/* 0x0027b930 — FUN_0027b930 (140 bytes). Rejects a chunk handed to a handle in an unsupported mode (anything but 0 or 1): a non-empty chunk is cleared and the handle's error callback (+28, object +32) gets code -3. A NULL or unused (+4 clear) handle is reported through FUN_0027b2e0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Chunk_27b930 {
    char *data;     /* 0x00 */
    int length;     /* 0x04 */
} Chunk_27b930;

typedef struct Handle_27b930 {
    int pad0;
    int used;                                   /* 0x04 */
    char pad8[20];
    void (*error)(int object, int code);        /* 0x1c */
    int error_object;                           /* 0x20 */
} Handle_27b930;

extern char s_E2004090243_NULL_pointer_is_specified_004f1c58[];   /* 'E2004090243 : NULL pointer is specified.' */
extern char s_E2004090244_Specified_handle_is_invalid_004f1c88[]; /* 'E2004090244 : Specified handle is invalid.' */
int FUN_0027b2e0(const char *message);

void FUN_0027b930(Handle_27b930 *handle, int mode, Chunk_27b930 *chunk) {
    if (handle == 0) {
        FUN_0027b2e0(s_E2004090243_NULL_pointer_is_specified_004f1c58);
        return;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(s_E2004090244_Specified_handle_is_invalid_004f1c88);
        return;
    }
    if (chunk->length > 0 && chunk->data != 0 && mode != 0 && mode != 1) {
        chunk->length = 0;
        chunk->data = 0;
        if (handle->error != 0) {
            handle->error(handle->error_object, -3);
        }
    }
}

