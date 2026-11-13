/* CRI ADX on PS2, memory side: the memory device alone, and the end-of-stream margin of ADXT's streams. */
#include "dw4/cri/adxfs.h"

extern int adxt_stm_eos;

void adxps2_mfs_errfn(void *obj, const char *msg, int code)
{
    ADXERR_CallErrFunc1(msg);
}

void ADXPS2_SetupMfs(void)
{
    cvFsEntryErrFunc(adxps2_mfs_errfn, 0);
    cvFsAddDev("MFS", mfCiGetInterface, 0);
}

int ADXT_GetStmEos(void)
{
    return adxt_stm_eos;
}

void ADXT_SetStmEos(int eos)
{
    adxt_stm_eos = eos;
}
