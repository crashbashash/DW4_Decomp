/* Queues a 16-byte item on entry `index`'s ring (FUN_002ac880) when the item is valid and the ring
 * exists, reporting error 0xFF000421 on overflow. */
struct Item16 {
    long first;  /* 64-bit; negative = no item */
    long second;
};

struct Ring {
    struct Item16 *items; /* +0 */
    int size;
    int count;
    int head;
};

/* One 116-byte (0x74) entry of the table at +0x1308. */
struct Entry74 {
    char pad0[56];
    struct Ring ring; /* +56 */
    char pad72[0x74 - 72];
};

struct Owner {
    char pad0[0x1308];
    struct Entry74 entries[1];
};

int FUN_002ac880(struct Ring *ring, struct Item16 *item, int *full);
int FUN_002a0bb8(struct Owner *obj, int code);

int FUN_002ac7f0(struct Owner *obj, int index, struct Item16 *item, int *full) {
    struct Ring *ring;

    *full = 0;
    if (item->first < 0) {
        return 0;
    }
    ring = &obj->entries[index].ring;
    if (ring->items == 0) {
        return 0;
    }
    if (FUN_002ac880(ring, item, full) == -1) {
        return FUN_002a0bb8(obj, 0xFF000421);
    }
    return 0;
}
