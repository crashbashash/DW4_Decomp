/* 0x0027b690 — FUN_0027b690 (80 bytes). Stores a pair of words into +28 / +32 of a handle; reports
   "E2004090235 : NULL pointer is specified." for a null handle and "E2004090236 : Specified handle is
   invalid." when the handle is not in use (+4 is 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle27b {
    int f0;
    int used;      /* +4 */
    char pad8[20];
    int first;     /* +28 */
    int second;    /* +32 */
};

extern void FUN_0027b2e0(const char *message);
extern const char s_E2004090235_NULL_pointer_is_specified_004f1b38[];
extern const char s_E2004090236_Specified_handle_is_invalid_004f1b68[];

void FUN_0027b690(struct Handle27b *handle, int first, int second) {
    if (handle == 0) {
        FUN_0027b2e0(s_E2004090235_NULL_pointer_is_specified_004f1b38);
        return;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(s_E2004090236_Specified_handle_is_invalid_004f1b68);
        return;
    }
    handle->first = first;
    handle->second = second;
}
