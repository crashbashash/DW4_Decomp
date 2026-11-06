/* Walks every free-list bin of the allocator and refreshes the free/used totals in the allocator
 * statistics block. */
typedef struct MallocChunk {
    unsigned int previousSize;
    unsigned int size;
    struct MallocChunk *forward;
    struct MallocChunk *back;
} MallocChunk;

typedef struct MallocStats {
    int arena;
    int ordinaryBlocks;
    int smallBlocks;
    int mappedBlocks;
    int mappedBytes;
    int maxUsedBytes;
    int freeSmallBytes;
    int usedBytes;
    int freeBytes;
    int keepCost;
} MallocStats;

extern MallocChunk *DAT_004854b0[]; /* bin heads; entry 2 is the top chunk */
extern MallocStats DAT_004858e0;

#define BIN_AT(i) ((MallocChunk *)((char *)&DAT_004854b0[2 * (i) + 2] - 8))
#define CHUNK_SIZE(p) ((p)->size & ~3)
#define TOP_CHUNK (BIN_AT(0)->forward)

void FUN_00126180(void) {
    int i;
    MallocChunk *bin;
    MallocChunk *chunk;
    unsigned int available;
    int availableCount;

    available = CHUNK_SIZE(TOP_CHUNK);
    availableCount = available >= 16 ? 1 : 0;
    for (i = 1; i < 128; ++i) {
        bin = BIN_AT(i);
        for (chunk = bin->back; chunk != bin; chunk = chunk->back) {
            ++availableCount;
            available += CHUNK_SIZE(chunk);
        }
    }
    DAT_004858e0.ordinaryBlocks = availableCount;
    DAT_004858e0.usedBytes = DAT_004858e0.arena - available;
    DAT_004858e0.freeBytes = available;
    DAT_004858e0.keepCost = CHUNK_SIZE(TOP_CHUNK);
}
