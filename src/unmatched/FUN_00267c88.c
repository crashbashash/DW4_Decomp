/* 0x00267c88 — FUN_00267c88 (120 bytes). Second-order predictor step: adds ((k0 * h0 + k1 * h1) >> 12) to the input, clamps to 16 bits, shifts the history and returns the new sample; with no state returns the input. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Predictor_267c88 {
    int pad0;
    short k0;       /* 0x04: coefficient of the last output */
    short k1;       /* 0x06: coefficient of the one before */
    short h0;       /* 0x08: last output */
    short h1;       /* 0x0a: the one before */
} Predictor_267c88;

short FUN_00267c88(Predictor_267c88 *state, short input) {
    int value;
    short output;

    if (state != 0) {
        value = ((state->k0 * state->h0 + state->k1 * state->h1) >> 12) + input;
        if (value < 32767) {
            output = value < -32768 ? -32768 : value;
        } else {
            output = 32767;
        }
        state->h1 = state->h0;
        state->h0 = output;
        return output;
    }
    return input;
}

