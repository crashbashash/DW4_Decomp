/* Returns the word at +20 of a handle scaled by 2048 while its state byte is 1 (0 otherwise),
 * reporting "E0092912:handl is null." and returning 0 for a null handle. */
struct Handle274 {
    signed char f0;
    signed char f1;
    signed char state;   /* +2 */
    char pad3[9];
    int value12;         /* +12 */
    int pad16;
    int value20;         /* +20 */
};

extern void FUN_002739b8(int detail, const char *message);
extern const char E0092912_handl_is_null[];

int FUN_00274370(struct Handle274 *handle) {
    if (handle == 0) {
        FUN_002739b8(0, E0092912_handl_is_null);
        return 0;
    }
    if (handle->state == 1) {
        return handle->value20 << 11;
    }
    return 0;
}
