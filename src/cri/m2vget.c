#include "dw4/cri/m2v.h"

int M2VLIB_CheckHn(void *hn);
int M2VERR_SetCode(void *hn, int code);

void M2V_GetPicAtr(Mpeg2Ctx *hn, M2vPicAtr *picatr)
{
    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF03020C);
        return;
    }
    *picatr = hn->picatr;
}

void M2V_GetBitRate(Mpeg2Ctx *hn, int *bit_rate)
{
    Mpeg2Ext *h = &hn->ext;

    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF03020D);
        return;
    }
    *bit_rate = h->bit_rate;
}

void M2V_GetVbvBufSiz(Mpeg2Ctx *hn, int *vbv_size, int *vbv_delay, int *reserved)
{
    Mpeg2Ext *h = &hn->ext;

    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF03020F);
        return;
    }
    *vbv_size = h->vbv_buffer_size << 11;
    *vbv_delay = h->vbv_delay;
    *reserved = -1;
}

void M2V_GetLinkFlg(Mpeg2Ctx *hn, int *closed_gop, int *broken_link)
{
    Mpeg2Ext *h = &hn->ext;

    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF03020E);
        return;
    }
    *closed_gop = h->closed_gop;
    *broken_link = h->broken_link;
}
