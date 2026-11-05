/* 0x00275c88 — FUN_00275c88 (56 bytes). Returns the word at +28 of a handle, reporting a null handle and returning 0 for it.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle275 {
    signed char used;      /* +0 */
    signed char shared;    /* +1 */
    signed char state;     /* +2 */
    char pad3[21];
    int fd;                /* +24 */
    int value28;           /* +28 */
    char pad32[8];
    int sectors;           /* +40 */
};

extern void FUN_002753d8(int detail, const char *message);
extern const char s_E0092712_handl_is_null_004f0850[];

int FUN_00275c88(struct Handle275 *handle) {
    if (handle == 0) {
        FUN_002753d8(0, s_E0092712_handl_is_null_004f0850);
        return 0;
    }
    return handle->value28;
}
