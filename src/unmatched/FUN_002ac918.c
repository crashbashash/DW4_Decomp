/* Clears *out to -1 and, when entry `index` has a ring, looks up position `pos` (folded back by
 * the entry's span when it lies past base+span) through FUN_002ac990. */
struct Ring {
    void *items; /* +0 */
    int size;
    int count;
    int head;
};

struct EntryInfo {
    int f0;
    void *source;
    unsigned int base;  /* +8 */
    unsigned int span;  /* +12 */
};

/* One 116-byte (0x74) entry of the table at +0x1308. */
struct Entry74 {
    char pad0[16];
    struct EntryInfo info; /* +16 */
    char pad32[56 - 32];
    struct Ring ring;      /* +56 */
    char pad72[0x74 - 72];
};

struct Owner {
    char pad0[0x1308];
    struct Entry74 entries[1];
};

void FUN_002ac990(struct Ring *ring, unsigned int pos, long *out, unsigned int base, unsigned int span);

int FUN_002ac918(struct Owner *obj, int index, unsigned int pos, long *out) {
    /* matching construct: table base taken into a local before indexing */
    struct Entry74 *entries = obj->entries;
    struct Entry74 *entry;
    struct Ring *ring;
    struct EntryInfo *info;
    unsigned int span;
    unsigned int base;

    *out = -1;
    entry = &entries[index];
    ring = &entry->ring;
    info = &entry->info;
    span = info->span;
    base = info->base;
    if (ring->items == 0) {
        return 0;
    }
    FUN_002ac990(ring, pos < base + span ? pos : pos - span, out, base, span);
    return 0;
}
