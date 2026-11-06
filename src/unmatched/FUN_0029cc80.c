/* Stores a new value at state+44 and forwards it to FUN_0029cd18 unless it is zero while handle+80
 * is 1. */
typedef struct SfdDecoderState {
    int decoder;            /* +0 */
    char pad4[40];
    int f44;                /* +44 */
} SfdDecoderState;

typedef struct SfdHandle {
    char pad0[80];
    int f80;                /* +80 */
    char pad84[4036];
    char block4120[4068];   /* +4120 */
    SfdDecoderState *state; /* +8188 */
} SfdHandle;

extern void FUN_0029cd18(int decoder, void *block, int value, int decoder2);

void FUN_0029cc80(SfdHandle *handle, int value) {
    SfdDecoderState *state = handle->state;
    void *block = handle->block4120;
    int decoder;

    state->f44 = value;
    decoder = state->decoder;
    if (value != 0 || handle->f80 != 1) {
        FUN_0029cd18(decoder, block, value, decoder);
    }
}
