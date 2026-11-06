/* Walks every stream on the state block's stream lists and ORs together the callback's result for
 * each stream whose flags (+12) are non-zero. */
typedef struct Stream125c90 {
    char pad0[12];
    short flags;                    /* +12: 0 = slot unused */
    char pad14[74];
} Stream125c90;

typedef struct StreamList125c90 {
    struct StreamList125c90 *next;  /* +0 */
    int count;                      /* +4 */
    Stream125c90 *streams;          /* +8 */
} StreamList125c90;

typedef struct LibState125c90 {
    char pad0[472];
    StreamList125c90 list;          /* +472 */
} LibState125c90;

int FUN_00125c90(LibState125c90 *state, int (*fn)(Stream125c90 *)) {
    Stream125c90 *stream;
    StreamList125c90 *list;
    int n;
    int ret = 0;

    for (list = &state->list; list != 0; list = list->next) {
        for (stream = list->streams, n = list->count; --n >= 0; stream++) {
            if (stream->flags != 0) {
                ret |= fn(stream);
            }
        }
    }
    return ret;
}
