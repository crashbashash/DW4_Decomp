/* 0x00278410 — FUN_00278410 (76 bytes). Clears the busy byte (+1) of a handle inside the
   FUN_00277da0 / FUN_00277db8 critical section; a null handle is reported as "E0092912:handl is null.".
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Handle278 {
    signed char used;     /* +0 */
    signed char busy;     /* +1 */
};

extern void FUN_00277de8(int detail, const char *message);
extern void FUN_00277da0(void);
extern void FUN_00277db8(void);
extern const char s_E0092912_handl_is_null_004f0e30[];

void FUN_00278410(struct Handle278 *handle) {
    if (handle == 0) {
        FUN_00277de8(0, s_E0092912_handl_is_null_004f0e30);
        return;
    }
    FUN_00277da0();
    handle->busy = 0;
    FUN_00277db8();
}
