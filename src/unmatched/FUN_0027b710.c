/* 0x0027b710 — FUN_0027b710 (84 bytes). Rewinds a handle: copies the start value (+24) into the current
   position (+12) and clears +16; reports "E2004090237 : NULL pointer is specified." for a null handle and
   "E2004090238 : Specified handle is invalid." when the handle is not in use (+4 is 0).
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle27b {
    int f0;
    int used;      /* +4 */
    int f8;
    int position;  /* +12 */
    int f16;       /* +16 */
    int f20;
    int start;     /* +24 */
};

extern void FUN_0027b2e0(const char *message);
extern const char s_E2004090237_NULL_pointer_is_specified_004f1b98[];
extern const char s_E2004090238_Specified_handle_is_invalid_004f1bc8[];

void FUN_0027b710(struct Handle27b *handle) {
    if (handle == 0) {
        FUN_0027b2e0(s_E2004090237_NULL_pointer_is_specified_004f1b98);
        return;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(s_E2004090238_Specified_handle_is_invalid_004f1bc8);
        return;
    }
    handle->position = handle->start;
    handle->f16 = 0;
}
