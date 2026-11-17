#ifndef DW4_P2VIF_H
#define DW4_P2VIF_H

#ifdef __cplusplus
extern "C" {
#endif

int p2GetVifMask(void);
float p2GetVifRowScale(void);
void p2SetVifMask(int mask);
void p2SetVifRowScale(float scale);

#ifdef __cplusplus
}
#endif

#endif
