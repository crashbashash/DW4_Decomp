#ifndef DW4_DMACHANNEL_H
#define DW4_DMACHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
