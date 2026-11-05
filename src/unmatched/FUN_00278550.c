/* 0x00278550 — FUN_00278550 (56 bytes). Returns the word at +20 of a handle, reporting "E0092912:handl is null." and returning 0 for a
   null handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle278 {
    signed char used;     /* +0 */
    signed char busy;     /* +1 */
    char pad2[18];
    int value20;          /* +20 */
};

extern void FUN_00277de8(int detail, const char *message);
extern const char s_E0092912_handl_is_null_004f0e30[];

int FUN_00278550(struct Handle278 *handle) {
    if (handle == 0) {
        FUN_00277de8(0, s_E0092912_handl_is_null_004f0e30);
        return 0;
    }
    return handle->value20;
}
