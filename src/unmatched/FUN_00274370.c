/* 0x00274370 — FUN_00274370 (76 bytes). Returns the word at +20 of a handle scaled by 2048 while its state
   byte is 1 (0 otherwise), reporting
   "E0092912:handl is null." and returning 0 for a null handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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
extern const char s_E0092912_handl_is_null_004f0348[];

int FUN_00274370(struct Handle274 *handle) {
    if (handle == 0) {
        FUN_002739b8(0, s_E0092912_handl_is_null_004f0348);
        return 0;
    }
    if (handle->state == 1) {
        return handle->value20 << 11;
    }
    return 0;
}
