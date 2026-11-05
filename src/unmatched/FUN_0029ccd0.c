/* 0x0029ccd0 — FUN_0029ccd0 (72 bytes). Forwards a value to FUN_0029cd18 unless it is zero while state+44 is 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdDecoderState {
    int decoder;            /* +0 */
    char pad4[40];
    int f44;                /* +44 */
} SfdDecoderState;

typedef struct SfdHandle {
    char pad0[4120];
    char block4120[4068];   /* +4120 */
    SfdDecoderState *state; /* +8188 */
} SfdHandle;

extern void FUN_0029cd18(int decoder, void *block, int value);

void FUN_0029ccd0(SfdHandle *handle, int value) {
    SfdDecoderState *state = handle->state;
    void *block = handle->block4120;
    int decoder = state->decoder;

    if (value != 0 || state->f44 != 1) {
        FUN_0029cd18(decoder, block, value);
    }
}
