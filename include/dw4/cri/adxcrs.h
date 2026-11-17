/* CRI ADXCRS: the critical section the ADX libraries take around shared state; src/cri/adxcrs.c. */
#ifndef DW4_CRI_ADXCRS_H
#define DW4_CRI_ADXCRS_H

#ifdef __cplusplus
extern "C" {
#endif

void ADXCRS_Init(void);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);

#ifdef __cplusplus
}
#endif

#endif
