/* p2pool.h - the p2 renderer's typed record pools.
 *
 * Each kind of renderer record (IG_GFX_INTERNAL_STRUCT_*_PSX2 in the visual context's settings) comes
 * from a free list of its own. p2GrowPool allocates a block of records when a list runs dry and links
 * them onto it; the first record of each block keeps the block's allocation so that p2FreePool can
 * release every block of a kind at shutdown. The size setting of a kind is the number of records a
 * block holds; the DMA buffer kinds instead set each channel's packet count and packet size. */
#ifndef DW4_P2POOL_H
#define DW4_P2POOL_H

#include "dw4/p2/p2dma.h"

enum p2PoolType {
    P2_POOL_DMA_BUFFER_VIF0,
    P2_POOL_DMA_BUFFER_VIF1,
    P2_POOL_DMA_BUFFER_GIF,
    P2_POOL_IMAGE,
    P2_POOL_DMA_BUFFER_VIF0_SIZE,
    P2_POOL_DMA_BUFFER_VIF1_SIZE,
    P2_POOL_DMA_BUFFER_GIF_SIZE,
    P2_POOL_DMA_PREDICATE,
    P2_POOL_DMA_COMPLETION,
    P2_POOL_FINISH,
    P2_POOL_TEXTURE,
    P2_POOL_STATE_CACHE,
    P2_POOL_MULTIPASS,
    P2_POOL_DISPLAY_LIST
};

#ifdef __cplusplus
extern "C" {
#endif

/* The packets of each DMA channel's ring, and the size of a packet of each channel. */
extern int p2DmaPacketCount[P2_DMA_CHANNEL_COUNT];
extern int p2DmaPacketSizeVif0;
extern int p2DmaPacketSizeVif1;
extern int p2DmaPacketSizeGif;

void p2GrowPool(int type, void *freeList);
void p2SetPoolSize(int type, int size);
int p2GetPoolAllocated(unsigned int type);
void p2FixDmaPacketPool(int channel);
void p2FreePool(unsigned int type, int unused);
void p2ResetDmaPacketCount(int channel);

#ifdef __cplusplus
}
#endif

#endif
