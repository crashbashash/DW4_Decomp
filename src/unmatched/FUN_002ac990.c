/* Pops items from a ring buffer: FUN_002aca28 finds how many to skip for position `pos` (between
 * base and span), the tail and count advance by that many and the item now at the tail is copied
 * to *out. */
struct Item16 {
    long first; /* 64-bit; copied as a whole */
    int f8;
    int f12;
};

struct Ring {
    struct Item16 *items; /* +0 */
    int size;             /* +4 */
    int count;            /* +8 */
    int head;             /* +12 */
    int tail;             /* +16 */
};

int FUN_002aca28(struct Ring *ring, unsigned int pos, unsigned int base, unsigned int span);

void FUN_002ac990(struct Ring *ring, unsigned int pos, struct Item16 *out, unsigned int base, unsigned int span) {
    int skip;
    int tail;

    if (ring->count == 0) {
        return;
    }
    skip = FUN_002aca28(ring, pos, base, span);
    if (skip == -1) {
        return;
    }
    tail = ring->tail + skip;
    if (tail >= ring->size) {
        tail -= ring->size;
    }
    ring->tail = tail;
    ring->count -= skip;
    *out = ring->items[tail];
}
