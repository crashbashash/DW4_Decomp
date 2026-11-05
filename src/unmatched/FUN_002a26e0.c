/* 0x002a26e0 — FUN_002a26e0 (244 bytes). Clears options 6 and 5 once their streams (2 and 1) are idle and flags 6/7 allow it. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdStatus8052 {
    int f0;
    int f4;                 /* +4 */
    int f8;                 /* +8 */
} SfdStatus8052;

typedef struct SfdHandle {
    char pad0[8052];
    SfdStatus8052 *status;  /* +8052 */
} SfdHandle;

extern int FUN_002adc40(SfdHandle *handle, int option);
extern int FUN_0029e2d0(SfdHandle *handle, int stream);
extern int FUN_002b03a0(SfdHandle *handle, int flag);
extern int FUN_002ada78(SfdHandle *handle, int option, int value);

void FUN_002a26e0(SfdHandle *handle) {
    SfdStatus8052 *status = handle->status;

    if (FUN_002adc40(handle, 6) != 0 && FUN_002adc40(handle, 80) != 0) {
        if (FUN_0029e2d0(handle, 2) == 0 && status->f8 == 0) {
            if (FUN_002b03a0(handle, 6) != 0) {
                FUN_002ada78(handle, 6, 0);
            }
        }
    }
    if (FUN_002adc40(handle, 5) != 0 && FUN_002adc40(handle, 79) != 0 && FUN_0029e2d0(handle, 1) == 0
        && status->f4 == 0 && FUN_002b03a0(handle, 7) != 0) {
        FUN_002ada78(handle, 5, 0);
    }
}
