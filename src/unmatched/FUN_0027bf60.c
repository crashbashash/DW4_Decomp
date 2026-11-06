/* 0x0027bf60 — FUN_0027bf60 (108 bytes). Resets a handle's transfer state: copies the start value (+32) to +16 and clears the counters at +12, +20, +24, +40, +44, +48 and +52; a NULL or unused (+4 clear) handle is reported through FUN_0027b2e0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Handle_27bf60 {
    int pad0;
    int used;       /* 0x04 */
    int pad8;
    int f12;    /* 0x0c */
    int current;    /* 0x10 */
    int f20;    /* 0x14 */
    int f24;    /* 0x18 */
    int pad28;
    int start;      /* 0x20 */
    int pad36;
    int f40;    /* 0x28 */
    int f44;    /* 0x2c */
    int f48;    /* 0x30 */
    int f52;    /* 0x34 */
} Handle_27bf60;

extern char E2004090207_NULL_pointer_is_specified[];   /* 'E2004090207 : NULL pointer is specified.' */
extern char E2004090208_Specified_handle_is_invalid[]; /* 'E2004090208 : Specified handle is invalid.' */
int FUN_0027b2e0(const char *message);

void FUN_0027bf60(Handle_27bf60 *handle) {
    if (handle == 0) {
        FUN_0027b2e0(E2004090207_NULL_pointer_is_specified);
        return;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(E2004090208_Specified_handle_is_invalid);
        return;
    }
    handle->current = handle->start;
    handle->f12 = 0;
    handle->f20 = 0;
    handle->f24 = 0;
    handle->f40 = 0;
    handle->f44 = 0;
    handle->f48 = 0;
    handle->f52 = 0;
}
