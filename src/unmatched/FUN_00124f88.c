/* Allocates (through FUN_00126600) a stream-list node followed by `count` zeroed 88-byte streams
 * and links them into the node; returns the node or 0. */
typedef struct Stream124f88 { char opaque[88]; } Stream124f88;

typedef struct StreamList124f88 {
    struct StreamList124f88 *next;  /* +0 */
    int count;                      /* +4 */
    Stream124f88 *streams;          /* +8 */
} StreamList124f88;

void *FUN_00126600(void *state, unsigned int size);
void *memset(void *dst, int value, unsigned int size);

StreamList124f88 *FUN_00124f88(void *state, int count) {
    StreamList124f88 *list;
    Stream124f88 *streams;

    list = FUN_00126600(state, sizeof(*list) + count * sizeof(Stream124f88));
    if (list == 0) {
        return 0;
    }
    streams = (Stream124f88 *)(list + 1);
    list->next = 0;
    list->count = count;
    list->streams = streams;
    memset(streams, 0, count * sizeof(Stream124f88));
    return list;
}
