/* CRI ADX on PS2, memory side: the memory device alone, and the end-of-stream margin of ADXT's streams. */
#include "dw4/cri/adxfs.h"

/* End-of-stream margin handed to each ADXT stream. */
int adxt_stm_eos = 25;

void adxps2_err_mem(void *obj, const char *msg, int code)
{
    ADXERR_CallErrFunc1(msg);
}

void ADXPS2_SetupMemFs(void)
{
    cvFsEntryErrFunc(adxps2_err_mem, 0);
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
