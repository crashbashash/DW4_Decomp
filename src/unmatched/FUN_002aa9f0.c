/* Advances the stream state by its kind (2, 3, or 4/6 via FUN_002aaea0/FUN_002abe70) once
 * FUN_002aaab0 reports both inputs ready; returns the state. */
int FUN_002aaab0();
void FUN_002aab60();
int FUN_002aaea0();
void FUN_002abe70();

struct Stream2aa9f0 {
    char pad0[72];
    int state;                            /* +72 */
    int kind;                             /* +76 */
};

/* Advances the stream state once FUN_002aaab0 reports both inputs ready; returns the new state. */
int FUN_002aa9f0(struct Stream2aa9f0 *stream) {
    int state = stream->state;
    int kind = stream->kind;

    if (FUN_002aaab0(stream) == 0) {
        return state;
    }
    FUN_002aab60(stream);
    switch (kind) {
    case 2:
        state = 2;
        break;
    case 3:
        state = 3;
        break;
    case 4:
    case 6:
        if (FUN_002aaea0(stream) != 0) {
            state = 4;
            FUN_002abe70(stream);
        } else {
            state = 3;
        }
        break;
    }
    return state;
}
