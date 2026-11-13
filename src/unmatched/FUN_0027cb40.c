/* Stores a pair of words into +40 / +44 of a handle; reports "E2004090265 : NULL pointer is
 * specified." for a null handle and "E2004090266 : Specified handle is invalid." when the handle
 * is not in use (byte +4 is 0). */
struct Handle27c {
    int f0;
    signed char used;   /* +4 */
    char pad5[35];
    int first;          /* +40 */
    int second;         /* +44 */
};

extern void SJERR_CallErr(const char *message);
extern const char E2004090265_NULL_pointer_is_specified[];
extern const char E2004090266_Specified_handle_is_invalid[];

void FUN_0027cb40(struct Handle27c *handle, int first, int second) {
    if (handle == 0) {
        SJERR_CallErr(E2004090265_NULL_pointer_is_specified);
        return;
    }
    if (handle->used == 0) {
        SJERR_CallErr(E2004090266_Specified_handle_is_invalid);
        return;
    }
    handle->first = first;
    handle->second = second;
}
