/* CRI UTY: the integer arithmetic, time comparison and timer helpers the Sofdec modules share. */
#ifndef DW4_CRI_UTY_H
#define DW4_CRI_UTY_H

int UTY_MulDiv(int a, int b, int c);
long long UTY_MulDivRound64(long long a, long long b, long long c);
int UTY_CmpTime(int num0, int den0, int num1, int den1);
void UTY_InitTmr(int channel);
void UTY_FinishTmr(void);
long long UTY_GetTmr(void);
int UTY_IsTmrVoid(void);
long long UTY_GetTmrUnit(void);

#endif
