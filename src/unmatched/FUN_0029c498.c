/* Refreshes the cached value of handle option 27 and pushes a change to the decoder. */
typedef struct SfdDecoderState {
    int decoder;            /* +0: passed to FUN_0026c7b0 */
    char pad4[64];
    int cachedOption27;     /* +68 */
} SfdDecoderState;

typedef struct SfdHandle {
    char pad0[8188];
    SfdDecoderState *state; /* +8188 */
} SfdHandle;

extern int FUN_002adc40(SfdHandle *handle, int option);
extern void FUN_0026c7b0(int decoder, int value);

void FUN_0029c498(SfdHandle *handle) {
    SfdDecoderState *state = handle->state;
    int decoder = state->decoder;
    int value = FUN_002adc40(handle, 27);

    if (state->cachedOption27 != value) {
        state->cachedOption27 = value;
        FUN_0026c7b0(decoder, value);
    }
}
