/* 0x0027cb40 — FUN_0027cb40 (80 bytes). Stores a pair of words into +40 / +44 of a handle; reports
   "E2004090265 : NULL pointer is specified." for a null handle and "E2004090266 : Specified handle is
   invalid." when the handle is not in use (byte +4 is 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle27c {
    int f0;
    signed char used;   /* +4 */
    char pad5[35];
    int first;          /* +40 */
    int second;         /* +44 */
};

extern void FUN_0027b2e0(const char *message);
extern const char s_E2004090265_NULL_pointer_is_specified_004f2108[];
extern const char s_E2004090266_Specified_handle_is_invalid_004f2138[];

void FUN_0027cb40(struct Handle27c *handle, int first, int second) {
    if (handle == 0) {
        FUN_0027b2e0(s_E2004090265_NULL_pointer_is_specified_004f2108);
        return;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(s_E2004090266_Specified_handle_is_invalid_004f2138);
        return;
    }
    handle->first = first;
    handle->second = second;
}
