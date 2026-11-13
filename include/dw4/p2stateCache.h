/* p2stateCache.h - the p2 renderer's state cache.
 *
 * A draw's render state packs into a 64-bit key; the cache maps keys to the GS/VIF packet built for
 * that state, so a repeated state costs a lookup instead of a rebuild. Entries hang off 256 hash
 * buckets; p2InvalidateStateCache forgets the keys last matched. */
#ifndef DW4_P2STATECACHE_H
#define DW4_P2STATECACHE_H

#define P2_STATE_CACHE_BUCKETS 256

typedef struct p2StateCacheEntry {
    void *memory;                       /* the first entry of a pool block keeps the block */
    struct p2StateCacheEntry *next;
    char f8[24];
    char ownsPacket;
    char f33[623];
    void *packet;
    char f660[12];
} p2StateCacheEntry;

void p2InitStateCache(void);
void p2InvalidateStateCache(void);

#endif
