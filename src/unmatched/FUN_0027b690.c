/* Stores a pair of words into +28 / +32 of a handle; reports "E2004090235 : NULL pointer is
 * specified." for a null handle and "E2004090236 : Specified handle is invalid." when the handle
 * is not in use (+4 is 0). */
struct Handle27b {
    int f0;
    int used;      /* +4 */
    char pad8[20];
    int first;     /* +28 */
    int second;    /* +32 */
};

extern void FUN_0027b2e0(const char *message);
extern const char E2004090235_NULL_pointer_is_specified[];
extern const char E2004090236_Specified_handle_is_invalid[];

void FUN_0027b690(struct Handle27b *handle, int first, int second) {
    if (handle == 0) {
        FUN_0027b2e0(E2004090235_NULL_pointer_is_specified);
        return;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(E2004090236_Specified_handle_is_invalid);
        return;
    }
    handle->first = first;
    handle->second = second;
}
