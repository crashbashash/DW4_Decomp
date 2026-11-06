/* 0x0027b5f8 — FUN_0027b5f8 (68 bytes). Handle getter: returns the word at +8 of a handle whose +4 word is set, reporting a NULL or invalid handle through FUN_0027b2e0 and returning 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Handle_27b5f8 {
    int pad0;
    int used;   /* 0x04 */
    int value;  /* 0x08 */
} Handle_27b5f8;

extern char E2004090233_NULL_pointer_is_specified[]; /* 'E2004090233 : NULL pointer is specified.' */
extern char E2004090234_Specified_handle_is_invalid[]; /* 'E2004090234 : Specified handle is invalid.' */
int FUN_0027b2e0(const char *message);

int FUN_0027b5f8(Handle_27b5f8 *handle) {
    if (handle == 0) {
        FUN_0027b2e0(E2004090233_NULL_pointer_is_specified);
        return 0;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(E2004090234_Specified_handle_is_invalid);
        return 0;
    }
    return handle->value;
}
