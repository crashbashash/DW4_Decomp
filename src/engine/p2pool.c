#include "dw4/p2core.h"
#include "dw4/p2dma.h"
#include "dw4/p2pool.h"
#include "dw4/p2swap.h"
#include "dw4/p2stateCache.h"

#define P2_HEAP_TEMPORARY 9
#define P2_HEAP_DRIVER 25

/* The fields of the image and texture records the pool reaches; their files own the records. */
typedef struct p2ImageRecord {
    void *memory;
    struct p2ImageRecord *next;
} p2ImageRecord;

typedef struct p2TextureRecord {
    char f0[24];
    struct p2TextureRecord *next;
    char f28[12];
    void *memory;
} p2TextureRecord;

void *Memory_AllocateAligned16(int size, int pool);
void Memory_FreeToSelector(void *memory, int pool);

extern int p2DmaPacketCount[P2_DMA_CHANNEL_COUNT];
extern int p2DmaPacketSizeVif0;
extern int p2DmaPacketSizeVif1;
extern int p2DmaPacketSizeGif;

/* records per block, by kind */
extern int p2ImageBlockSize;
extern int p2TextureBlockSize;
extern int p2FinishBlockSize;
extern int p2DmaPredicateBlockSize;
extern int p2DmaCompletionBlockSize;
extern int p2StateCacheBlockSize;
extern int p2MultiPassBlockSize;
extern int p2DisplayListBlockSize;

/* records allocated so far, by kind */
extern int p2ImageRecords;
extern int p2TextureRecords;
extern int p2FinishRecords;
extern int p2DmaPredicateRecords;
extern int p2DmaCompletionRecords;
extern int p2StateCacheRecords;
extern int p2MultiPassRecords;
extern int p2DisplayListRecords;
extern int p2DmaPacketsAllocated[P2_DMA_CHANNEL_COUNT];

/* a channel whose packets come from one block only, and whether it has had it */
extern int p2DmaPoolFixedVif1;
extern int p2DmaPoolFixedGif;

extern p2ImageRecord *p2ImagePool;
extern p2TextureRecord *p2FreeTextures;
extern p2DisplayList *p2DisplayListPool;
extern p2DmaPredicate *p2DmaPredicatePool;
extern p2DmaCompletion *p2DmaCompletionPool;
extern p2FinishFunc *p2FreeFinishFuncs;
extern p2StateCacheEntry *p2StateCache[P2_STATE_CACHE_BUCKETS];
extern p2StateCacheEntry *p2FreeStateCacheEntries;

void p2ResetDmaPacketCount(int channel) {
    switch (channel) {
    case P2_DMA_VIF0:
        p2DmaPacketsAllocated[P2_DMA_VIF0] = 0;
        break;
    case P2_DMA_VIF1:
        p2DmaPacketsAllocated[P2_DMA_VIF1] = 0;
        break;
    case P2_DMA_GIF:
        p2DmaPacketsAllocated[P2_DMA_GIF] = 0;
        break;
    }
}

void p2SetPoolSize(int type, int size) {
    switch (type) {
    case P2_POOL_DISPLAY_LIST:
        p2DisplayListBlockSize = size;
        return;
    case P2_POOL_STATE_CACHE:
        p2StateCacheBlockSize = size;
        return;
    case P2_POOL_MULTIPASS:
        p2MultiPassBlockSize = size;
        return;
    case P2_POOL_IMAGE:
        p2ImageBlockSize = size;
        return;
    case P2_POOL_TEXTURE:
        p2TextureBlockSize = size;
        return;
    case P2_POOL_DMA_PREDICATE:
        p2DmaPredicateBlockSize = size;
        return;
    case P2_POOL_DMA_COMPLETION:
        p2DmaCompletionBlockSize = size;
        return;
    case P2_POOL_FINISH:
        p2FinishBlockSize = size;
        return;
    case P2_POOL_DMA_BUFFER_VIF0:
        p2DmaPacketCount[P2_DMA_VIF0] = size;
        p2DmaPacketsAllocated[P2_DMA_VIF0] = 0;
        return;
    case P2_POOL_DMA_BUFFER_VIF1:
        p2DmaPacketCount[P2_DMA_VIF1] = size;
        p2DmaPacketsAllocated[P2_DMA_VIF1] = 0;
        return;
    case P2_POOL_DMA_BUFFER_GIF:
        p2DmaPacketCount[P2_DMA_GIF] = size;
        p2DmaPacketsAllocated[P2_DMA_GIF] = 0;
        return;
    case P2_POOL_DMA_BUFFER_VIF0_SIZE:
        p2DmaPacketSizeVif0 = size;
        return;
    case P2_POOL_DMA_BUFFER_VIF1_SIZE:
        p2DmaPacketSizeVif1 = size;
        return;
    case P2_POOL_DMA_BUFFER_GIF_SIZE:
        p2DmaPacketSizeGif = size;
    default:
        return;
    }
}

int p2GetPoolAllocated(unsigned int type) {
    switch (type) {
    case P2_POOL_STATE_CACHE:
        return p2StateCacheRecords;
    case P2_POOL_DISPLAY_LIST:
        return p2DisplayListRecords;
    case P2_POOL_MULTIPASS:
        return p2MultiPassRecords;
    case P2_POOL_IMAGE:
        return p2ImageRecords;
    case P2_POOL_TEXTURE:
        return p2TextureRecords;
    case P2_POOL_FINISH:
        return p2FinishRecords;
    case P2_POOL_DMA_PREDICATE:
        return p2DmaPredicateRecords;
    case P2_POOL_DMA_COMPLETION:
        return p2DmaCompletionRecords;
    case P2_POOL_DMA_BUFFER_VIF0:
    case P2_POOL_DMA_BUFFER_VIF1:
    case P2_POOL_DMA_BUFFER_GIF:
        return p2DmaPacketsAllocated[type];
    case P2_POOL_DMA_BUFFER_VIF0_SIZE:
        return p2DmaPacketSizeVif0;
    case P2_POOL_DMA_BUFFER_VIF1_SIZE:
        return p2DmaPacketSizeVif1;
    case P2_POOL_DMA_BUFFER_GIF_SIZE:
        return p2DmaPacketSizeGif;
    default:
        return 0;
    }
}

void p2FixDmaPacketPool(int channel) {
    switch (channel) {
    case P2_DMA_VIF1:
        p2DmaPoolFixedVif1 = 1;
        break;
    case P2_DMA_GIF:
        p2DmaPoolFixedGif = 1;
        break;
    }
}

/* Releases every block of a kind. The block allocations are gathered first, from the first record of
 * each block on the free lists, into a temporary array. */
void p2FreePool(unsigned int type) {
    switch (type) {
    case P2_POOL_STATE_CACHE: {
        p2StateCacheEntry *entry;
        void **blocks;
        int count;
        int bucket;
        void *memory;
        void *data;
        void *freeMemory;
        p2StateCacheEntry *free;
        int i;

        blocks = Memory_AllocateAligned16(p2StateCacheRecords * 4, P2_HEAP_TEMPORARY);
        count = 0;
        if (blocks != 0) {
            bucket = 0;
            do {
                entry = p2StateCache[bucket];
                while (entry != 0) {
                    memory = entry->memory;
                    if (memory != 0) {
                        blocks[count] = memory;
                        count++;
                    }
                    data = entry->packet;
                    if (data != 0 && entry->ownsPacket != 0) {
                        Memory_FreeToSelector(data, P2_HEAP_DRIVER);
                        entry->packet = 0;
                    }
                    entry = entry->next;
                }
                bucket++;
            } while (bucket < P2_STATE_CACHE_BUCKETS);
            free = p2FreeStateCacheEntries;
            while (free != 0) {
                freeMemory = free->memory;
                if (freeMemory != 0) {
                    blocks[count] = freeMemory;
                    count++;
                }
                free = free->next;
            }
        }
        for (i = 0; i < count; i++) {
            Memory_FreeToSelector(blocks[i], P2_HEAP_DRIVER);
        }
        Memory_FreeToSelector(blocks, P2_HEAP_TEMPORARY);
        return;
    }
    case P2_POOL_DISPLAY_LIST: {
        p2DisplayList *list;
        void **blocks;
        int count;
        int i;

        list = p2DisplayListPool;
        blocks = Memory_AllocateAligned16(p2DisplayListRecords * 4, P2_HEAP_TEMPORARY);
        count = 0;
        if (blocks != 0) {
            while (list != 0) {
                if (list->memory != 0) {
                    blocks[count] = list->memory;
                    count++;
                }
                list = list->next;
            }
        }
        for (i = 0; i < count; i++) {
            Memory_FreeToSelector(blocks[i], P2_HEAP_DRIVER);
        }
        Memory_FreeToSelector(blocks, P2_HEAP_TEMPORARY);
        return;
    }
    case P2_POOL_IMAGE: {
        p2ImageRecord *image;
        void **blocks;
        int count;
        int i;

        image = p2ImagePool;
        blocks = Memory_AllocateAligned16(p2ImageRecords * 4, P2_HEAP_TEMPORARY);
        count = 0;
        if (blocks != 0) {
            while (image != 0) {
                if (image->memory != 0) {
                    blocks[count] = image->memory;
                    count++;
                }
                image = image->next;
            }
        }
        for (i = 0; i < count; i++) {
            Memory_FreeToSelector(blocks[i], P2_HEAP_DRIVER);
        }
        Memory_FreeToSelector(blocks, P2_HEAP_TEMPORARY);
        return;
    }
    case P2_POOL_TEXTURE: {
        p2TextureRecord *texture;
        void **blocks;
        int count;
        int i;

        texture = p2FreeTextures;
        blocks = Memory_AllocateAligned16(p2TextureRecords * 4, P2_HEAP_TEMPORARY);
        count = 0;
        if (blocks != 0) {
            while (texture != 0) {
                if (texture->memory != 0) {
                    blocks[count] = texture->memory;
                    count++;
                }
                texture = texture->next;
            }
        }
        for (i = 0; i < count; i++) {
            Memory_FreeToSelector(blocks[i], P2_HEAP_DRIVER);
        }
        Memory_FreeToSelector(blocks, P2_HEAP_TEMPORARY);
        return;
    }
    case P2_POOL_FINISH: {
        p2FinishFunc *finish;
        void **blocks;
        int count;
        int i;

        finish = p2FreeFinishFuncs;
        blocks = Memory_AllocateAligned16(p2FinishRecords * 4, P2_HEAP_TEMPORARY);
        count = 0;
        if (blocks != 0) {
            while (finish != 0) {
                if (finish->memory != 0) {
                    blocks[count] = finish->memory;
                    count++;
                }
                finish = finish->next;
            }
        }
        for (i = 0; i < count; i++) {
            Memory_FreeToSelector(blocks[i], P2_HEAP_DRIVER);
        }
        Memory_FreeToSelector(blocks, P2_HEAP_TEMPORARY);
        return;
    }
    case P2_POOL_DMA_PREDICATE: {
        p2DmaPredicate *predicate;
        void **blocks;
        int count;
        int i;

        predicate = p2DmaPredicatePool;
        blocks = Memory_AllocateAligned16(p2DmaPredicateRecords * 4, P2_HEAP_TEMPORARY);
        count = 0;
        if (blocks != 0) {
            while (predicate != 0) {
                if (predicate->memory != 0) {
                    blocks[count] = predicate->memory;
                    count++;
                }
                predicate = predicate->next;
            }
        }
        for (i = 0; i < count; i++) {
            Memory_FreeToSelector(blocks[i], P2_HEAP_DRIVER);
        }
        Memory_FreeToSelector(blocks, P2_HEAP_TEMPORARY);
        return;
    }
    case P2_POOL_DMA_COMPLETION: {
        p2DmaCompletion *completion;
        void **blocks;
        int count;
        int i;

        completion = p2DmaCompletionPool;
        blocks = Memory_AllocateAligned16(p2DmaCompletionRecords * 4, P2_HEAP_TEMPORARY);
        count = 0;
        if (blocks != 0) {
            while (completion != 0) {
                if (completion->memory != 0) {
                    blocks[count] = completion->memory;
                    count++;
                }
                completion = completion->next;
            }
        }
        for (i = 0; i < count; i++) {
            Memory_FreeToSelector(blocks[i], P2_HEAP_DRIVER);
        }
        Memory_FreeToSelector(blocks, P2_HEAP_TEMPORARY);
        return;
    }
    case P2_POOL_DMA_BUFFER_VIF0:
    case P2_POOL_DMA_BUFFER_VIF1:
    case P2_POOL_DMA_BUFFER_GIF:
        p2DmaPacketCount[type] = -1;
        return;
    case P2_POOL_DMA_BUFFER_VIF0_SIZE:
    case P2_POOL_DMA_BUFFER_VIF1_SIZE:
    case P2_POOL_DMA_BUFFER_GIF_SIZE:
        p2DmaPacketSizeVif0 = -1;
    default:
        return;
    }
}
