/* Frame swapping and the GS FINISH queue.
 *
 * A swap toggles the draw buffer and, unless the display flips at the next vertical blank, shows the
 * buffer just drawn at once. Swapping waits while the frames drawn run more than p2SwapLatency ahead
 * of the frames shown, and the VIF1 packet of a new frame waits until the buffer it draws into is off
 * the screen (swapbuffersDrawPredicate).
 *
 * Code that must run once the GS has drawn what was submitted before it queues a finish function;
 * the packets submitted after it wait for the GS FINISH handler, which calls the functions queued
 * before them. A finish sequence is a GS SIGNAL id written behind the submitted work: the signal
 * handler records each id the GS reaches, so a thread can wait for everything up to one. */
#include "dw4/eekernel.h"
#include "dw4/p2core.h"
#include "dw4/p2dma.h"
#include "dw4/p2pool.h"
#include "dw4/p2swap.h"
#include "dw4/p2timer.h"

/* p2DmaWatchFlags bits of the waits here */
enum {
    P2_WATCH_SWAPBUFFERS = 0x4,
    P2_WATCH_FINISH_SEQUENCE = 0x8
};

/* A DMA tag: REF reads qwc quadwords from addr. */
typedef union p2DmaTag {
    struct {
        unsigned int qwc : 16;
        unsigned int pad : 10;
        unsigned int pce : 2;
        unsigned int id : 3;
        unsigned int irq : 1;
        unsigned int addr : 31;
        unsigned int spr : 1;
        unsigned int data[2];
    } f;
    unsigned int word[4];
} p2DmaTag;

/* The GS privileged DISPFB register image: the frame buffer a read circuit shows. */
typedef union p2GsDispfb {
    unsigned long long word;
    struct {
        unsigned short fbp : 9;
        unsigned short fbw : 6;
    } field;
} p2GsDispfb;

int FUN_00113f20(void);
int FUN_00113f78(void);
int p2GetDisplayFlags(void);
void FUN_001f76c0(int reg);
void FUN_001f8190(int reg);
long long p2readGSPrivRegister(int reg);
void p2SubmitDmaPacket(int channel, p2DmaPacket *packet);
void p2AddDmaPredicate(int channel, int (*test)(long long arg), long long arg);
long long p2AddPreviousFinishFuncPredicate(void);
void p2RegisterPredicateName(int (*predicate)(long long), const char *name);
int p2TryStartDmaPacket(int channel);
void p2UploadViewport(void);
void p2BuildDisplayPacket(void);
int swapbuffersPredicate(long long frame);
int swapbuffersDrawPredicate(long long buffer);
void p2AddFinishFunc(void (*func)(p2FinishFunc *finish, int arg), int arg);
int p2NewFinishSequence(int signal);
void p2FlushVif1Packet(void);

extern int p2FirstOpen;
extern p2DmaPacket *p2DmaCurrentPacket[P2_DMA_CHANNEL_COUNT];
extern int p2BlockedSema;
extern int p2PreviousFinishFuncDone;
extern p2GsDispfb p2GsDispfb1;
extern p2GsDispfb p2GsDispfb2;
extern p2DmaTag p2DisplayPacketTag;
extern struct SemaParam p2SwapSemaParam;

extern p2FinishFunc *p2FinishTail;
extern p2FinishFunc *p2FinishHead;
extern p2FinishFunc *p2FreeFinishFuncs;
extern int p2VsyncSwapPending;
extern int p2FrameDrawn;
extern int p2LastDrawBuffer;
extern long long p2FramesSwapped;
extern int p2FinishFuncSema;
extern long long p2VsyncsWaited;
extern unsigned int p2DisplayPacket;
extern int p2DisplayPacketQwc;
extern int p2FinishSequence;
extern unsigned int p2FinishSequenceDone;
extern int p2SwapLatency;
extern int p2SwapOnVsync;
extern int p2FinishesPending;
extern long long p2FrameStartTime;
extern long long p2FramesTimed;
extern long long p2FrameTimeTotal;
extern unsigned long long p2FrameTimeMax;
extern unsigned long long p2FrameTimeMin;
extern int p2SwapInterval;
extern int p2VsyncsSinceSwap;
extern int p2GsSignalCount;

/* The frame count and the flag words are written by interrupt handlers while thread code waits on them; the
 * semaphore ids are written only by p2InitSwap and read twice in each wait. */
extern volatile int p2FinishSema;
extern volatile int p2SwapSema;
extern volatile long long p2FramesShown;
extern volatile p2DmaWatch p2DmaWatchFlags;

/* Queued at the end of a frame: the GS has drawn it. */
void p2RecordFrameTime(p2FinishFunc *finish, int arg) {
    long long now;
    unsigned long long elapsed;

    p2FrameDrawn = 1;
    p2ReadClock(&now);
    elapsed = now - p2FrameStartTime;
    p2FrameTimeTotal += elapsed;
    p2FramesTimed += 1;
    if (elapsed < p2FrameTimeMin) {
        p2FrameTimeMin = elapsed;
    }
    if (p2FrameTimeMax < elapsed) {
        p2FrameTimeMax = elapsed;
    }
}

void p2InitSwap(void) {
    struct SemaParam param;

    param = p2SwapSemaParam;
    if (p2FirstOpen != 0) {
        param.maxCount = 5;
        param.initCount = 0;
        p2FinishSema = CreateSema(&param);
        param.maxCount = 5;
        param.initCount = 1;
        p2SwapSema = CreateSema(&param);
        param.maxCount = 1;
        param.initCount = 1;
        p2FinishFuncSema = CreateSema(&param);
        p2RegisterPredicateName(swapbuffersPredicate, "swapbuffersPredicate");
        p2RegisterPredicateName(swapbuffersDrawPredicate, "swapbuffersDrawPredicate");
        p2BuildDisplayPacket();
    }
    if (p2Display.singleBuffered != 0) {
        p2Display.displayBuffer = 0;
        p2Display.drawBuffer = 0;
    } else {
        p2Display.drawBuffer = 0;
        p2Display.displayBuffer = 1;
    }
    p2FinishTail = 0;
    p2FinishHead = 0;
    p2FreeFinishFuncs = 0;
    p2GrowPool(P2_POOL_FINISH, &p2FreeFinishFuncs);
    p2FinishesPending = 0;
    p2SwapLatency = 2;
    p2SwapOnVsync = 1;
    p2FrameTimeTotal = 0;
    p2PreviousFinishFuncDone = 1;
    p2VsyncSwapPending = 1;
    p2FrameDrawn = 0;
    p2LastDrawBuffer = 0;
    p2FramesShown = 0;
    p2FramesSwapped = 1;
    p2VsyncsWaited = 0;
    p2FinishSequence = 1;
    p2FinishSequenceDone = 0;
    p2NewFinishSequence(1);
}

void p2EndFrame(void) {
    p2LastDrawBuffer = p2Display.drawBuffer;
    p2AddFinishFunc(p2RecordFrameTime, 0);
    p2FlushVif1Packet();
}

/* The swap of frame `frame` may go ahead once the frame before it is on the screen. */
int swapbuffersPredicate(long long frame) {
    return p2FramesShown + 1 >= frame;
}

/* A frame drawing into `buffer` may start once that buffer is off the screen. */
int swapbuffersDrawPredicate(long long buffer) {
    return buffer != p2Display.displayBuffer;
}

void p2SetSingleFrameLatency(void) {
    p2SwapLatency = 1;
}

void p2SetSwapInterval(int vsyncs) {
    p2SwapInterval = vsyncs;
    p2VsyncsSinceSwap = 0;
}

/* Sends the packet that switches the display to the new frame. */
void p2QueueDisplayPacket(void) {
    unsigned int *cursor;
    int qwc;

    p2FlushVif1Packet();
    cursor = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p2DisplayPacketTag.f.addr = p2DisplayPacket & ~0xF;
    qwc = p2DisplayPacketQwc;
    *(unsigned short *)&p2DisplayPacketTag = qwc;
    cursor[0] = p2DisplayPacketTag.word[0];
    cursor[1] = p2DisplayPacketTag.word[1];
    cursor[2] = p2DisplayPacketTag.word[2];
    cursor[3] = p2DisplayPacketTag.word[3];
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(cursor + 4);
    p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
    p2GsDirtyRegisters |= 0x40122140 | ((long long)0x50A1 << 32);
}

/* Ends the frame: waits while too many frames are queued ahead of the display, then either leaves
 * the flip to the vertical-blank handler or shows the new frame at once. */
void p2SwapBuffers(void) {
    long long start;
    long long end;
    int displayFlags;
    int displayBuffer;
    int page;
    p2GsRegisterSet *gs;

    displayFlags = p2GetDisplayFlags();
    p2FramesSwapped += 1;
    if (displayFlags != 0) {
        p2QueueDisplayPacket();
    }
    if (p2SwapOnVsync != 0) {
        FUN_00113f20();
        p2DmaWatchFlags.busy |= P2_WATCH_SWAPBUFFERS;
        FUN_00113f78();
        while (p2FramesSwapped > p2FramesShown + p2SwapLatency) {
            p2ReadClock(&start);
            p2BlockedSema = p2SwapSema;
            WaitSema(p2SwapSema);
            p2BlockedSema = -1;
            p2ReadClock(&end);
            p2SwapWaitTime += (long long)((end - start) << 32) >> 32;
        }
        p2SwapLatency = 2;
        FUN_00113f20();
        p2DmaWatchFlags.busy &= ~P2_WATCH_SWAPBUFFERS;
        p2DmaWatchFlags.seen &= ~P2_WATCH_SWAPBUFFERS;
        FUN_00113f78();
        p2AddDmaPredicate(P2_DMA_VIF1, swapbuffersPredicate, p2FramesSwapped);
    } else {
        p2FrameDrawn = 0;
        if (displayFlags == 0) {
            p2Display.displayBuffer ^= 1;
            displayBuffer = p2Display.displayBuffer;
            p2GsDispfb2.field.fbp = (displayBuffer != 0) ? p2Display.secondBufferPage : 0;
            if (displayBuffer != 0) {
                page = p2Display.secondBufferPage;
            } else {
                page = 0;
            }
            p2GsDispfb1.field.fbp = page;
            FUN_001f8190(9);
            FUN_001f8190(7);
        }
    }
    if (p2Display.singleBuffered == 0) {
        p2Display.drawBuffer = ((p2Display.drawBuffer != 0) ^ 1) & 0xFF;
        if (p2Display.interlaced != 0 && (p2Display.frameCount == 1 || p2Display.frameMode == 0)) {
            p2AddDmaPredicate(P2_DMA_VIF1, swapbuffersDrawPredicate, p2Display.drawBuffer);
        }
        if (p2Display.frameMode != 0 && p2Display.frameCount == 1) {
            if (p2Display.drawBuffer == 0) {
                p2CurrentGsRegisters->scanmsk.field.msk = 3;
            } else {
                p2CurrentGsRegisters->scanmsk.field.msk = 2;
            }
            FUN_001f76c0(P2_GS_SCANMSK);
        }
        if (displayFlags == 0) {
            if (p2Display.frameMode != 0 && p2Display.frameCount == 1) {
                p2CurrentGsRegisters->frame[0].field.fbp = 0;
            } else {
                p2CurrentGsRegisters->frame[0].field.fbp = (p2Display.drawBuffer != 0) ? p2Display.secondBufferPage : 0;
            }
        }
        gs = p2CurrentGsRegisters;
        gs->frame[1].half[0] = gs->frame[0].half[0];
        gs->frame[1].half[1] = gs->frame[0].half[1];
        FUN_001f76c0(P2_GS_FRAME_1);
        FUN_001f76c0(P2_GS_FRAME_2);
        if (p2Display.frameMode == 0 && p2Display.frameCount == 2) {
            p2UploadViewport();
        }
    }
}

/* The GS FINISH handler: calls the finish functions queued behind the packet that just finished. */
void p2FinishHandler(void) {
    struct SemaParam status;
    long long sequence;
    p2FinishFunc *finish;

    if (p2FinishHead != 0) {
        sequence = p2FinishHead->sequence;
        while (!!p2FinishHead && sequence == p2FinishHead->sequence) {
            p2FinishHead->func(p2FinishHead, p2FinishHead->arg);
            finish = p2FinishHead;
            if (finish == p2FinishTail) {
                p2FinishTail = 0;
                p2FinishHead = 0;
            } else {
                p2FinishHead = finish->next;
            }
            finish->next = p2FreeFinishFuncs;
            p2FreeFinishFuncs = finish;
        }
    }
    p2PreviousFinishFuncDone = 1;
    iReferSemaStatus(p2FinishFuncSema, &status);
    if (status.currentCount != status.maxCount) {
        iSignalSema(p2FinishFuncSema);
    }
    p2TryStartDmaPacket(P2_DMA_VIF1);
    p2TryStartDmaPacket(P2_DMA_GIF);
}

void p2AddFinishFunc(void (*func)(p2FinishFunc *finish, int arg), int arg) {
    p2FinishFunc *finish;

    if (p2FreeFinishFuncs == 0) {
        p2GrowPool(P2_POOL_FINISH, &p2FreeFinishFuncs);
    }
    FUN_00113f20();
    finish = p2FreeFinishFuncs;
    p2FreeFinishFuncs = finish->next;
    FUN_00113f78();
    finish->sequence = p2AddPreviousFinishFuncPredicate();
    finish->func = func;
    finish->arg = arg;
    finish->next = 0;
    FUN_00113f20();
    if (p2FinishTail != 0) {
        p2FinishTail->next = finish;
    } else {
        p2FinishHead = finish;
    }
    p2FinishTail = finish;
    FUN_00113f78();
}

/* Starts a new finish sequence: the id goes into the GS SIGNAL register image, sent with the next
 * register update. Returns the sequence. */
int p2NewFinishSequence(int signal) {
    int sequence;

    sequence = p2FinishSequence + 1;
    p2FinishSequence = sequence;
    ((int *)&p2CurrentGsRegisters->signal)[0] = sequence;
    ((int *)&p2CurrentGsRegisters->signal)[1] = -1;
    p2FinishesPending += 1;
    if (signal != 0) {
        FUN_001f76c0(P2_GS_SIGNAL);
    }
    return p2FinishSequence;
}

/* Waits until the GS has reached finish sequence `sequence`. */
void p2WaitFinishSequence(unsigned int sequence) {
    long long start;
    long long end;

    p2FlushVif1Packet();
    FUN_00113f20();
    p2DmaWatchFlags.busy |= P2_WATCH_FINISH_SEQUENCE;
    FUN_00113f78();
    while (p2FinishSequenceDone < sequence) {
        p2ReadClock(&start);
        p2BlockedSema = p2FinishSema;
        WaitSema(p2FinishSema);
        p2BlockedSema = -1;
        p2ReadClock(&end);
        p2FinishWaitTime += (long long)((end - start) << 32) >> 32;
    }
    FUN_00113f20();
    p2DmaWatchFlags.busy &= ~P2_WATCH_FINISH_SEQUENCE;
    p2DmaWatchFlags.seen &= ~P2_WATCH_FINISH_SEQUENCE;
    FUN_00113f78();
    p2FinishesPending -= 1;
}

/* The GS SIGNAL handler: the GS has reached the finish sequence in SIGLBLID. */
void p2GsSignalHandler(void) {
    struct SemaParam status;

    p2GsSignalCount += 1;
    p2FinishSequenceDone = (int)p2readGSPrivRegister(0x48);
    iReferSemaStatus(p2FinishSema, &status);
    if (status.currentCount != status.maxCount) {
        iSignalSema(p2FinishSema);
    }
}

/* Submits the current VIF1 packet if anything was written to it or it carries the finish predicate. */
void p2FlushVif1Packet(void) {
    p2DmaPacket *packet = p2DmaCurrentPacket[P2_DMA_VIF1];

    if (packet->chain != packet->cursor || packet->finishPredicate != 0) {
        p2SubmitDmaPacket(P2_DMA_VIF1, packet);
    }
}
