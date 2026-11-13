/* CRI ADXB AHX glue: hands an ADXB handle's AHX stream to the AHX decoder through hooks the decoder
 * registers. No decoder registers in this game, so the hooks stay null. */
#include "dw4/cri/adxb.h"
#include "dw4/cri/sfdsj.h"

/* The AHX decoder works in 96-sample units. */
#define ADXB_AHX_FRMSMPL 96

extern void (*adxb_ahx_setsjifn)(void *ahx, SfdSj *sji);
extern void (*adxb_ahx_setdecsmplfn)(void *ahx, int nsmpl);
extern void (*adxb_ahx_termsupplyfn)(void *ahx);
extern void (*adxb_ahx_execfn)(AdxbObj *adxb);

void ADXB_SetAhxInSj(AdxbObj *adxb, SfdSj *sji)
{
    if (adxb->ahx != 0) {
        adxb_ahx_setsjifn(adxb->ahx, sji);
    }
}

void ADXB_SetAhxDecSmpl(AdxbObj *adxb, int nsmpl)
{
    if (adxb->ahx != 0) {
        adxb_ahx_setdecsmplfn(adxb->ahx, nsmpl);
    }
    adxb->ahx_dec_nsmpl = nsmpl;
    adxb->ahx_dec_nfrm = nsmpl / ADXB_AHX_FRMSMPL;
}

void ADXB_ExecOneAhx(AdxbObj *adxb)
{
    adxb_ahx_execfn(adxb);
}

void ADXB_AhxTermSupply(AdxbObj *adxb)
{
    if (adxb->ahx != 0) {
        adxb_ahx_termsupplyfn(adxb->ahx);
    }
}
