/* 0x00278250 — FUN_00278250 (56 bytes). Returns the word at +16 of a handle, reporting
   "E01100306:handl is null." and returning 0 for a null handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle278 {
    signed char used;     /* +0 */
    signed char busy;     /* +1 */
    char pad2[14];
    int value16;          /* +16 */
};

extern void FUN_00277de8(int detail, const char *message);
extern const char s_E01100306_handl_is_null_004f0da8[];

int FUN_00278250(struct Handle278 *handle) {
    if (handle == 0) {
        FUN_00277de8(0, s_E01100306_handl_is_null_004f0da8);
        return 0;
    }
    return handle->value16;
}
