/* 0x00278498 — FUN_00278498 (56 bytes). Returns the word at +4 of a handle, reporting "E0040301:handl is null." and returning 0 for a
   null handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle278 {
    signed char used;     /* +0 */
    signed char busy;     /* +1 */
    char pad2[2];
    int value4;          /* +4 */
};

extern void FUN_00277de8(int detail, const char *message);
extern const char s_E0040301_handl_is_null_004f0e48[];

int FUN_00278498(struct Handle278 *handle) {
    if (handle == 0) {
        FUN_00277de8(0, s_E0040301_handl_is_null_004f0e48);
        return 0;
    }
    return handle->value4;
}
