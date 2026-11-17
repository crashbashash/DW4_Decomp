/* CRI ADXT Pro Logic II: attaches a PL2ENC encoder to a stereo ADXT handle's decoder. The decoder
 * then plays mono data through the encoder, placed at a position on the Pro Logic II plane, by
 * the hooks this file installs in ADXB, ADXSJD and ADXT. */
#include "dw4/cri/adxb.h"
#include "dw4/cri/pl2enc.h"
#include "dw4/cri/adx_ps2.h"
#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/adxsjd.h"
#include "dw4/cri/adxerrs.h"

void adxt_CallDetachPl2(AdxtObj *adxt);
void adxt_Pl2ErrFunc(void *obj, const char *message);
void adxt_Pl2Detach(AdxtObj *adxt);
void adxt_Pl2ExecOneSmpl(AdxbObj *adxb, int in, short *out_l, short *out_r);
void adxt_Pl2Reset(AdxbObj *adxb);
void adxt_Pl2SetSfreq(AdxbObj *adxb, int sfreq);

void ADXT_AttachPl2(AdxtObj *adxt, void *work, int wksize)
{
    AdxbObj *adxb;
    Pl2Enc *pl2;

    if (adxt->maxnch < 2) {
        ADXERR_CallErrFunc1("E2003091101 : ADXT handle must be created for stereo output.");
        return;
    }
    ADXT_Stop(adxt);
    adxt_CallDetachPl2(adxt);
    PL2ENC_EntryErrFunc(adxt_Pl2ErrFunc, 0);
    PL2ENC_Init(0);
    adxb = adxt->sjd->adxb;
    ADXM_Lock();
    pl2 = PL2ENC_Create(work, wksize);
    if (pl2 == 0) {
        ADXERR_CallErrFunc1("E2003091002 : Fail to attach Dolby Pro Logic II.");
        return;
    }
    PL2ENC_SetPos(pl2, adxb->pl2_x, adxb->pl2_y);
    adxb->pl2 = pl2;
    adxt_detach_pl2 = adxt_Pl2Detach;
    adxb_pl2_exec_func = adxt_Pl2ExecOneSmpl;
    adxb_pl2_reset_func = adxt_Pl2Reset;
    adxsjd_header_hook = adxt_Pl2SetSfreq;
    ADXM_Unlock();
}

void adxt_CallDetachPl2(AdxtObj *adxt)
{
    if (adxt_detach_pl2 != 0) {
        adxt_detach_pl2(adxt);
    }
}

/* x runs from -127 (left) to 127 (right), y from -127 (front) to 127 (back). */
void ADXT_SetPl2Pos(AdxtObj *adxt, int x, int y)
{
    AdxbObj *adxb;
    Pl2Enc *pl2;

    if (adxt == 0) {
        ADXERR_CallErrFunc1("E2003091605 : NULL pointer is specified.");
        return;
    }
    adxb = adxt->sjd->adxb;
    pl2 = adxb->pl2;
    if (adxt->maxnch < 2 || pl2 == 0) {
        ADXERR_CallErrFunc1("E2003091606 : ADXT handle must be created for 3D sound.");
        return;
    }
    PL2ENC_SetPos(pl2, x, y);
    adxb->pl2_x = x;
    adxb->pl2_y = y;
}

void adxt_Pl2Detach(AdxtObj *adxt)
{
    AdxbObj *adxb;
    Pl2Enc *pl2;

    adxb = adxt->sjd->adxb;
    pl2 = adxb->pl2;
    if (pl2 == 0) {
        return;
    }
    ADXT_Stop(adxt);
    ADXM_Lock();
    PL2ENC_Destroy(pl2);
    adxb->pl2 = 0;
    PL2ENC_Finish(0);
    ADXM_Unlock();
}

void adxt_Pl2Reset(AdxbObj *adxb)
{
    PL2ENC_Reset(adxb->pl2);
}

void adxt_Pl2ExecOneSmpl(AdxbObj *adxb, int in, short *out_l, short *out_r)
{
    PL2ENC_ExecOneSmpl(adxb->pl2, in, out_l, out_r);
}

void adxt_Pl2SetPos(AdxbObj *adxb, int x, int y)
{
    PL2ENC_SetPos(adxb->pl2, x, y);
}

void adxt_Pl2SetSfreq(AdxbObj *adxb, int sfreq)
{
    PL2ENC_SetSfreq(adxb->pl2, sfreq);
}

void adxt_Pl2ErrFunc(void *obj, const char *message)
{
    ADXERR_CallErrFunc1(message);
}
