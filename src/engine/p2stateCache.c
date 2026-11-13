#include "dw4/p2stateCache.h"

extern p2StateCacheEntry *p2StateCache[P2_STATE_CACHE_BUCKETS];
extern p2StateCacheEntry *p2CurrentStateCacheEntry;
extern p2StateCacheEntry *p2FreeStateCacheEntries;
extern long long p2LastStateKeys[4];
extern unsigned long long *p2StateCachePacketArena;

void p2InitStateCache(void) {
    int bucket;

    bucket = 0;
    do {
        p2StateCache[bucket] = 0;
        bucket += 1;
    } while (bucket < P2_STATE_CACHE_BUCKETS);
    p2CurrentStateCacheEntry = 0;
    p2StateCachePacketArena = 0;
    p2FreeStateCacheEntries = 0;
    p2LastStateKeys[0] = 0;
    p2LastStateKeys[1] = 0;
    p2LastStateKeys[2] = 0;
    p2LastStateKeys[3] = 0;
}

void p2InvalidateStateCache(void) {
    p2LastStateKeys[0] = -1;
    p2LastStateKeys[1] = -1;
    p2LastStateKeys[2] = -1;
    p2LastStateKeys[3] = -1;
}
