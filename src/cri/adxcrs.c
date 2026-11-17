/* CRI ADXCRS: the critical section the ADX libraries take around shared state. */
#include "dw4/cri/svm.h"
#include "dw4/cri/adxcrs.h"


extern int adxcrs_lock_cnt;

void ADXCRS_Init(void)
{
    adxcrs_lock_cnt = 0;
}

void ADXCRS_Lock(void)
{
    SVM_Lock();
}

void ADXCRS_Unlock(void)
{
    SVM_Unlock();
}
