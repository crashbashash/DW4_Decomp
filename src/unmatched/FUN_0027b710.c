/* Rewinds a handle: copies the start value (+24) into the current position (+12) and clears +16;
 * reports "E2004090237 : NULL pointer is specified." for a null handle and "E2004090238 :
 * Specified handle is invalid." when the handle is not in use (+4 is 0). */
struct Handle27b {
    int f0;
    int used;      /* +4 */
    int f8;
    int position;  /* +12 */
    int f16;       /* +16 */
    int f20;
    int start;     /* +24 */
};

extern void SJERR_CallErr(const char *message);
extern const char E2004090237_NULL_pointer_is_specified[];
extern const char E2004090238_Specified_handle_is_invalid[];

void FUN_0027b710(struct Handle27b *handle) {
    if (handle == 0) {
        SJERR_CallErr(E2004090237_NULL_pointer_is_specified);
        return;
    }
    if (handle->used == 0) {
        SJERR_CallErr(E2004090238_Specified_handle_is_invalid);
        return;
    }
    handle->position = handle->start;
    handle->f16 = 0;
}
