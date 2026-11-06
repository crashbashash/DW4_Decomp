/* Returns the word at +4 of a handle, reporting "E0040301:handl is null." and returning 0 for a
 * null handle. */
struct Handle278 {
    signed char used;     /* +0 */
    signed char busy;     /* +1 */
    char pad2[2];
    int value4;          /* +4 */
};

extern void FUN_00277de8(int detail, const char *message);
extern const char E0040301_handl_is_null[];

int FUN_00278498(struct Handle278 *handle) {
    if (handle == 0) {
        FUN_00277de8(0, E0040301_handl_is_null);
        return 0;
    }
    return handle->value4;
}
