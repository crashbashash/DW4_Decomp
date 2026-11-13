/* CRI ADXB AC-3 glue: hands an ADXB handle's AC-3 stream to the AC-3 decoder through hooks the decoder
 * registers, and reads an AC-3 stream's header. No decoder registers in this game, so the hooks stay null. */
#include "dw4/cri/adxb.h"
#include "dw4/cri/sfdsj.h"

/* AC-3 frames carry 1536 samples. */
#define ADXB_AC3_FRMSMPL 1536

extern void (*adxb_ac3_setsjifn)(void *ac3, SfdSj *sji);
extern void (*adxb_ac3_termsupplyfn)(void *ac3);
extern void (*adxb_ac3_execfn)(AdxbObj *adxb);

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
int ADXB_DecodeHeaderAc3(AdxbObj *adxb, unsigned short *hdr, int size)
{
    if (adxb->ac3 == 0) {
        return 0;
    }
    adxb->hdr_set = 1;
    adxb->sfreq = 48000;
    adxb->nch = 1;
    adxb->fmtbps = 16;
    adxb->total_nsmpl = 0x7FFFFFFF;
    adxb->blklen = 127;
    adxb->blksmpl = ADXB_AC3_FRMSMPL;
    adxb->format = ADXB_FORMAT_AC3;
    adxb->buf.nch = 1;
    adxb->buf.blklen = 127;
    adxb->buf.blksmpl = ADXB_AC3_FRMSMPL;
    adxb->buf.pcmbuf = adxb->pcmbuf;
    adxb->buf.pcmbsize = adxb->pcmbsize;
    adxb->buf.pcmbdist = adxb->pcmbdist;
    adxb->wpos = 0;
    adxb->cof = 0;
    adxb->nloop = 0;
    adxb->lptype = 0;
    adxb->lpins_nsmpl = 0;
    adxb->lp_start_pos = 0;
    adxb->lp_start_ofst = 0;
    adxb->lp_end_pos = 0;
    adxb->lp_end_ofst = 0;
    adxb->dec_nsmpl = 0;
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
