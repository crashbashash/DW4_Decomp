/* CRI ADXERR: the ADX libraries' error report, passed to the application's callback and to SVM;
 * src/cri/adxerrs.c. */
#ifndef DW4_CRI_ADXERRS_H
#define DW4_CRI_ADXERRS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*AdxErrFunc)(void *obj, char *msg);

void ADXERR_Init(void);
void ADXERR_Finish(void);
void ADXERR_EntryErrFunc(AdxErrFunc func, void *obj);
void ADXERR_CallErrFunc1(const char *msg);
void ADXERR_CallErrFunc2(const char *code, const char *msg);
void ADXERR_ItoA(int value, char *dst, int size);
void ADXERR_ItoA2(int value, int extra, char *text, int size);

#ifdef __cplusplus
}
#endif

#endif
