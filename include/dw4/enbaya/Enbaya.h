#ifndef DW4_ENBAYA_H
#define DW4_ENBAYA_H

struct EnbayaAnimationData;
struct EnbayaContext;
struct EnbayaDecoderState;
struct EnbayaSlot;

#ifdef __cplusplus
extern "C" {
#endif

/* Creates the Enbaya codec's memory management on first use: the given allocator object, or the
 * malloc/free default when it is 0. */
void Enbaya_InitMemoryManagement(void **memory);
void thunk_Enbaya_InitMemoryManagement(void **memory);
/* Builds a decoder for `boneCount` bones in `memory`; returns it. */
void *FUN_0027ee00(void *memory, int boneCount);
/* Starts decoding `data`, resetting the decoder's position. */
void FUN_0027ef50(struct EnbayaDecoderState *state, struct EnbayaAnimationData *data, unsigned char fastCache);
/* The two keys of `track` around `time`, advancing the decoder to it when it lies outside the decoded span. */
void FUN_0027fa60(struct EnbayaContext *context, float time, int track, struct EnbayaSlot **before, struct EnbayaSlot **after);
void FUN_002800d0(struct EnbayaDecoderState *state);

#ifdef __cplusplus
}
#endif

#endif
