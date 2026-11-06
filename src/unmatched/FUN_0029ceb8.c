/* Returns the record at +3340 of the handle's work area while the state's count at +64 is not
 * positive, else NULL. */
typedef struct SfdDecoderState {
    char pad0[64];
    int f64;                /* +64 */
} SfdDecoderState;

typedef struct SfdHandle {
    char pad0[8188];
    SfdDecoderState *state; /* +8188 */
    char pad8192[5672];
    char *work;             /* +13864 */
} SfdHandle;

void *FUN_0029ceb8(SfdHandle *handle) {
    char *work = handle->work;
    SfdDecoderState *state = handle->state;

    if (work == 0) {
        return 0;
    }
    if (state->f64 > 0) {
        return 0;
    }
    return work + 3340;
}
