/* 0x0027caa8 — FUN_0027caa8 (68 bytes). Handle getter: returns the word at +8 of a handle whose +4 byte is set, reporting a NULL or invalid handle through FUN_0027b2e0 and returning 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Handle_27caa8 {
    int pad0;
    char used;  /* 0x04 */
    int value;  /* 0x08 */
} Handle_27caa8;

extern char s_E2004090263_NULL_pointer_is_specified_004f20a8[]; /* 'E2004090263 : NULL pointer is specified.' */
extern char s_E2004090264_Specified_handle_is_invalid_004f20d8[]; /* 'E2004090264 : Specified handle is invalid.' */
int FUN_0027b2e0(const char *message);

int FUN_0027caa8(Handle_27caa8 *handle) {
    if (handle == 0) {
        FUN_0027b2e0(s_E2004090263_NULL_pointer_is_specified_004f20a8);
        return 0;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(s_E2004090264_Specified_handle_is_invalid_004f20d8);
        return 0;
    }
    return handle->value;
}
