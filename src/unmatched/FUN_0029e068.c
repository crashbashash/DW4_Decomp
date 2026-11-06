/* Maps the bytes available on one side of a ring (ops slot 36) as up to two chunks via slot 24,
 * the second covering the wrap, releasing each with slot 28; returns the byte count. */
struct Chunk {
    char *data;
    int size;
};
struct Ring;
struct RingOps {
    char pad[24];
    void (*fn24)(struct Ring *, int, int, struct Chunk *);   /* map up to n bytes */
    void (*fn28)(struct Ring *, int, struct Chunk *);        /* release a mapping */
    char pad32[36 - 32];
    int (*fn36)(struct Ring *);                              /* bytes available */
};
struct Ring {
    struct RingOps *ops;
};

int FUN_0029e068(struct Ring *ring, int side, struct Chunk *first, struct Chunk *second) {
    int available = ring->ops->fn36(ring);

    ring->ops->fn24(ring, side, 0x7FFFFFFF, first);
    if (first->size < available) {
        ring->ops->fn24(ring, side, 0x7FFFFFFF, second);
        ring->ops->fn28(ring, side, second);
    } else {
        second->data = 0;
        second->size = 0;
    }
    ring->ops->fn28(ring, side, first);
    return available;
}
