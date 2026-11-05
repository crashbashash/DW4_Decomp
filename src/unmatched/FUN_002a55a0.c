/* 0x002a55a0 — FUN_002a55a0 (220 bytes). Raises option 52 when the frame qualifies, then hands the frame to FUN_002a5740 while option 52 is 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdFrame {
    char pad0[48];
    int f48;                /* +48 */
    char pad52[35];
    signed char f87;        /* +87 */
} SfdFrame;

extern int FUN_002adc40(void *handle, int option);
extern int FUN_002ada78(void *handle, int option, int value);
extern int FUN_002a5680(void *handle, SfdFrame *frame);
extern void FUN_002a5740(void *handle, SfdFrame *frame, int a, int b);

void FUN_002a55a0(void *handle, SfdFrame *frame, int a, int b) {
    int enabled = FUN_002adc40(handle, 52);

    if (enabled == 0) {
        if (a >= 0 || frame->f48 == 0 || frame->f87 != 0
            /* a2 still holds 1 here; FUN_002a5680 may read it as a third argument */
            || (b != 0 && FUN_002a5680(handle, frame) != 0)) {
            enabled = 1;
            FUN_002ada78(handle, 52, 1);
        }
    }
    if (enabled == 1) {
        FUN_002a5740(handle, frame, a, b);
    }
}
