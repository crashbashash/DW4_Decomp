#ifndef DW4_P2GS_H
#define DW4_P2GS_H

#ifdef __cplusplus
extern "C" {
#endif

/* The renderer's counters as p2GetStatistics copies them out, most as running totals: the caller
 * takes the difference of two copies. */
typedef struct p2Statistics {
    long long vertices;
    long long primitives;
    long long textureBinds;
    long long f24;
    long long f32;
    long long framesTimed;
    long long vsyncs;
    long long stateSends;
    long long functionTablesSent;
    long long lightingFunctionsSent;
    long long lightsSent;
    long long gifTagsSent;
    long long vertexFormatsSent;
    long long blendMatricesSent;
    long long gsRegistersSent;
    long long vuBufferLayoutsSent;
    long long passSetupsSent;
    long long lightingSwitches;
    long long materialSets;
    long long lightingModeSets;
    long long lightSets;
    long long lightSwitches;
    long long colourModeChanges;
    long long primitiveChanges;
    long long capabilityChanges;
    long long f200;
    long long f208;
    long long vif1DmaCount;
    long long vif1PartialPackets;
    long long f232;
    long long vif1DmaTime;
    long long gifDmaCount;
    long long gifPartialPackets;
    long long f264;
    long long gifDmaTime;
    long long dmaOverlapTime;
    long long frameTimeTotal;
    long long frameTimeMin;
    long long frameTimeMax;
    long long f312;
    long long f320;
    long long f328;
    long long dmaWaitTime;
    long long swapWaitTime;
    long long finishWaitTime;
    long long f360;
    long long sleepTime;
    long long f376;
    long long displayListVertices;
    long long displayListPrimitives;
    long long fastPathVertices;
    long long fastLitPathVertices;
    long long litPathVertices;
    long long vu1BlendVertices;
    long long vu0BlendVertices;
    long long vu1MultiPassVertices;
    long long indexedVertices;
} p2Statistics;

void p2FlushGsRegisters(void);
void p2SendGsRegister(int registerIndex);
void p2SetColour(unsigned int colour);
long long p2readGSPrivRegister(int registerIndex);
void p2writeGSPrivRegister(int registerIndex);
void p2UploadGsRegisters(int count, int *registers);
/* The same upload through the GIF channel. */
void p2UploadGsRegistersGif(int count, int *registers, int flush);
/* Appends a DMA call of the chain at `chain` to the GIF packet. */
void p2CallGifChain(unsigned int chain, int unused, int flush);
/* Append the VU1 program runs that end a VIF1 packet: the GS finish marker and a program restart. */
void p2AppendGsFinish(void);
void p2AppendProgramRestart(void);
/* The finish function and DMA predicate that let a GIF transfer wait until the GS has drawn the VIF1
 * packets submitted before it. */
struct p2FinishFunc;
void p2RecordFinishedSequence(struct p2FinishFunc *finish, int arg);
int p2SequenceFinishedPredicate(long long sequence);
void p2SetSpriteSizeMode(int mode);
int p2GetSpriteSizeMode(void);
/* Sends half a sprite's size to VU1 data memory. */
void p2SetSpriteHalfSize(float halfSize);

#ifdef __cplusplus
}
#endif

#endif
