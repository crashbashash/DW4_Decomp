#ifndef DW4_P2MULTIPASS_H
#define DW4_P2MULTIPASS_H

#include "dw4/p2core.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int p2TextureCombineMode[P2_PROGRAM_COUNT];
extern int p2TextureFunction[P2_PROGRAM_COUNT];
void p2CopyContext1ToContext2(void);
int p2GetPassCombineMode(void);
void p2GetPassMasks(int pass, unsigned int *frameMask, unsigned int *zbufMask);
void p2SetPassCount(int passes);
void p2UploadTex0Context2(void);

#ifdef __cplusplus
}
#endif

#endif
