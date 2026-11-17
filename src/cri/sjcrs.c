/* CRI SJCRS: the critical section the stream joints take, and the count of server passes running. */
#include "dw4/cri/svm.h"
#include "dw4/cri/sj.h"


extern int sjcrs_svr_cnt;
extern int D_004b5140;

void SJCRS_Init(void)
{
    sjcrs_svr_cnt = 0;
}

void SJCRS_Finish(void)
{
    sjcrs_svr_cnt = 0;
}

void SJCRS_BeginSvr(void)
{
    sjcrs_svr_cnt++;
}

void SJCRS_EndSvr(void)
{
    sjcrs_svr_cnt--;
}

/* Clears the word after the server count; nothing in the executable calls it. Retail leaves the word's
 * address in v0 and stores through it, the code of a function that returns that address. */
int *FUN_0027b2a0(void)
{
    D_004b5140 = 0;
    return &D_004b5140;  /* matching construct: no caller reads the result */
}

void SJCRS_Lock(void)
{
    SVM_Lock();
}

void SJCRS_Unlock(void)
{
    SVM_Unlock();
}
