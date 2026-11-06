/* Initialises a C-library state block: installs the cleanup hook, marks it initialised, sets up
 * three 88-byte streams (flags 4/9/10 on files 0/1/2) and links them as the block's stream list. */
typedef struct Stream125138 { char opaque[88]; } Stream125138;

typedef struct StreamList125138 {
    struct StreamList125138 *next;  /* +0 */
    int count;                      /* +4 */
    Stream125138 *streams;          /* +8 */
} StreamList125138;

typedef struct LibState125138 {
    char pad0[56];
    int initialised;                /* +56 */
    void (*cleanup)();              /* +60: FUN_001250f8 */
    char pad64[408];
    StreamList125138 list;          /* +472 */
    Stream125138 std_streams[3];    /* +484 */
} LibState125138;

void FUN_00124f28(Stream125138 *stream, int flags, int file, LibState125138 *state);
void FUN_001250f8();

void FUN_00125138(LibState125138 *state) {
    state->cleanup = FUN_001250f8;
    state->initialised = 1;
    FUN_00124f28(&state->std_streams[0], 4, 0, state);
    FUN_00124f28(&state->std_streams[1], 9, 1, state);
    FUN_00124f28(&state->std_streams[2], 10, 2, state);
    state->list.next = 0;
    state->list.count = 3;
    state->list.streams = state->std_streams;
}
