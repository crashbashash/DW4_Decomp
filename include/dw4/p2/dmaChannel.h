#ifndef DW4_DMACHANNEL_H
#define DW4_DMACHANNEL_H

#include "dw4/p2/p2dma.h"

#ifdef __cplusplus
extern "C" {
#endif

extern p2DmaPacket *p2DmaCurrentPacket[P2_DMA_CHANNEL_COUNT];
extern p2DmaPacket *p2DmaLastPacket[P2_DMA_CHANNEL_COUNT];
extern int p2DmaHandlerIds[P2_DMA_CHANNEL_COUNT];
extern p2DmaPredicate *p2DmaPredicatePool;
extern p2DmaCompletion *p2DmaCompletionPool;
void p2AddDmaCompletion(int channel, void (*func)(void *), void *arg);
void p2AddDmaPredicate(int channel, int (*predicate)(long long), long long arg);
long long p2AddPreviousFinishFuncPredicate(void);
int p2DmaSequenceLastCompleted(int channel, long long sequence);
long long p2GetVif1WaitSequence(void);
void p2RegisterPredicateName(int (*predicate)(long long), const char *name);
void p2ReserveDmaCompletions(int count);
void p2ShutdownDmaChannels(void);
void p2TryStartDmaPacket(int channel);
void p2WaitDmaSequence(int channel, long long sequence);
int textureDeferredPredicate(long long sequence);
int textureLoadedPredicate(long long sequence);

/* Closes the current packet of `channel` and makes the next packet of its ring current. */
void p2SubmitDmaPacket(int channel);

#ifdef __cplusplus
}
#endif

#endif
