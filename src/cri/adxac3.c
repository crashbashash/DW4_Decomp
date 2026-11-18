/* CRI ADXB AC-3 glue: hands an ADXB handle's AC-3 stream to the AC-3 decoder through hooks the decoder
 * registers, and reads an AC-3 stream's header. No decoder registers in this game, so the hooks stay null. */
#include "dw4/cri/adxb.h"
#include "dw4/cri/sj.h"

/* AC-3 frames carry 1536 samples. */
#define ADXB_AC3_FRMSMPL 1536

void (*adxb_ac3_setsjifn)(void *ac3, SfdSj *sji) = 0;
void (*adxb_ac3_termsupplyfn)(void *ac3) = 0;
void (*adxb_ac3_execfn)(AdxbObj *adxb) = 0;

void ADXB_SetAc3InSj(AdxbObj *adxb, SfdSj *sji)
{
    if (adxb->ac3 != 0) {
        adxb_ac3_setsjifn(adxb->ac3, sji);
    }
}

void ADXB_SetAc3DecSmpl(AdxbObj *adxb, int nsmpl)
{
    adxb->ac3_dec_nsmpl = nsmpl;
    adxb->ac3_dec_nfrm = nsmpl / ADXB_AC3_FRMSMPL;
}

void ADXB_Ac3TermSupply(AdxbObj *adxb)
{
    if (adxb->ac3 != 0) {
        adxb_ac3_termsupplyfn(adxb->ac3);
    }
}

void ADXB_ExecOneAc3(AdxbObj *adxb)
{
    if (adxb->ac3 != 0) {
        adxb_ac3_execfn(adxb);
    }
}

/* AC-3 carries no header ADXB can read: the stream is taken as mono 16-bit 48 kHz in 1536-sample frames. */
int ADXB_DecodeHeaderAc3(AdxbObj *adxb, unsigned char *hdr, int size)
{
    if (adxb->ac3 == 0) {
        return 0;
    }
    adxb->hdcdflag = 1;
    adxb->sfreq = 48000;
    adxb->nch = 1;
    adxb->bps = 16;
    adxb->total_nsmpl = 0x7FFFFFFF;
    adxb->blklen = 127;
    adxb->blknsmpl = ADXB_AC3_FRMSMPL;
    adxb->fmttype = ADXB_FORMAT_AC3;
    adxb->dp.nch = 1;
    adxb->dp.blksize = 127;
    adxb->dp.blknsmpl = ADXB_AC3_FRMSMPL;
    adxb->dp.pcmbuf = adxb->pcmbuf;
    adxb->dp.pcmbsize = adxb->pcmbsize;
    adxb->dp.pcmbdist = adxb->pcmbdist;
    adxb->curwpos = 0;
    adxb->cof = 0;
    adxb->nloop = 0;
    adxb->lp_type = 0;
    adxb->lp_ins_nsmpl = 0;
    adxb->lp_spos = 0;
    adxb->lp_sofst = 0;
    adxb->lp_epos = 0;
    adxb->lp_eofst = 0;
    adxb->total_ndecsmpl = 0;
    return 1;
}

/* The AC-3 sync word 0x0B77, in either byte order, at the start or 16 bytes in. */
int ADXB_CheckAc3(unsigned char *hdr)
{
    if (hdr[0] == 0x0b && hdr[1] == 0x77) {
        return 1;
    }
    if (hdr[0] == 0x77 && hdr[1] == 0x0b) {
        return 1;
    }
    if (hdr[16] == 0x0b && hdr[17] == 0x77) {
        return 1;
    }
    if (hdr[16] == 0x77 && hdr[17] == 0x0b) {
        return 1;
    }
    return 0;
}
