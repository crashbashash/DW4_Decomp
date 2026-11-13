/* Handle getter: returns the word at +8 of a handle whose +4 byte is set, reporting a NULL or
 * invalid handle through SJERR_CallErr and returning 0. */
typedef struct Handle_27caa8 {
    int pad0;
    char used;  /* 0x04 */
    int value;  /* 0x08 */
} Handle_27caa8;

extern char E2004090263_NULL_pointer_is_specified[]; /* 'E2004090263 : NULL pointer is specified.' */
extern char E2004090264_Specified_handle_is_invalid[]; /* 'E2004090264 : Specified handle is invalid.' */
int SJERR_CallErr(const char *message);

int FUN_0027caa8(Handle_27caa8 *handle) {
    if (handle == 0) {
        SJERR_CallErr(E2004090263_NULL_pointer_is_specified);
        return 0;
    }
    if (handle->used == 0) {
        SJERR_CallErr(E2004090264_Specified_handle_is_invalid);
        return 0;
    }
    return handle->value;
}
