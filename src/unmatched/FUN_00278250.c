/* Returns the word at +16 of a handle, reporting "E01100306:handl is null." and returning 0 for a
 * null handle. */
struct Handle278 {
    signed char used;     /* +0 */
    signed char busy;     /* +1 */
    char pad2[14];
    int value16;          /* +16 */
};

extern void FUN_00277de8(int detail, const char *message);
extern const char E01100306_handl_is_null[];

int FUN_00278250(struct Handle278 *handle) {
    if (handle == 0) {
        FUN_00277de8(0, E01100306_handl_is_null);
        return 0;
    }
    return handle->value16;
}
