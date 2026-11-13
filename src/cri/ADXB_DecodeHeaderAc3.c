/* The unit compiles without -Iinclude, so the shared header is reached by path. */
#include "../../include/dw4/cri/adxb.h"

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
    adxb->blksmpl = 0x600;
    adxb->format = ADXB_FORMAT_AC3;
    adxb->buf.nch = 1;
    adxb->buf.blklen = 127;
    adxb->buf.blksmpl = 0x600;
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
