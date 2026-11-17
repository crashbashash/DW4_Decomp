/* p2swap.h - frame swapping and the GS FINISH queue.
 *
 * A finish function is queued behind the packets submitted so far: the GS FINISH handler calls it once
 * the GS has drawn everything before it. */
#ifndef DW4_P2SWAP_H
#define DW4_P2SWAP_H

typedef struct p2FinishFunc {
    void *memory;                       /* the first record of a pool block keeps the block */
    struct p2FinishFunc *next;
    long long sequence;                 /* the finish predicate of the packet it waits behind */
    void (*func)(struct p2FinishFunc *finish, int arg);
    int arg;
} p2FinishFunc;

#ifdef __cplusplus
extern "C" {
#endif

extern p2FinishFunc *p2FreeFinishFuncs;
/* Frame timing: frames timed, their total time and the longest and shortest frame. */
extern long long p2FramesTimed;
extern long long p2FrameTimeTotal;
extern unsigned long long p2FrameTimeMax;
extern unsigned long long p2FrameTimeMin;

void p2BuildDisplayPacket(void);
void p2EndFrame(void);
void p2FinishHandler(void);
void p2FlushVif1Packet(void);
void p2GsSignalHandler(void);
int p2NewFinishSequence(int signal);
void p2SetSingleFrameLatency(void);
void p2SwapBuffers(void);
void p2WaitFinishSequence(unsigned int sequence);
int swapbuffersDrawPredicate(long long buffer);
void p2SetSwapInterval(int vsyncs);
void p2VsyncHandler(void);

#ifdef __cplusplus
}
#endif

#endif
