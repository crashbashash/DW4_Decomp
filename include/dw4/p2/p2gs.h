#ifndef DW4_P2GS_H
#define DW4_P2GS_H

#ifdef __cplusplus
extern "C" {
#endif

void p2FlushGsRegisters(void);
void p2SendGsRegister(int arg0);
void p2SetColour(unsigned int colour);
long long p2readGSPrivRegister(int registerIndex);
void p2writeGSPrivRegister(int registerIndex);
void p2UploadGsRegisters(int count, int *registers);
/* The finish function and DMA predicate that let a GIF transfer wait until the GS has drawn the VIF1
 * packets submitted before it. */
struct p2FinishFunc;
void p2RecordFinishedSequence(struct p2FinishFunc *finish, int arg);
int p2SequenceFinishedPredicate(long long sequence);
/* The value FUN_001f7340 last stored. */
int FUN_001f7360(void);

#ifdef __cplusplus
}
#endif

#endif
