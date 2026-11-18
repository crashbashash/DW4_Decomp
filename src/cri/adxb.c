#include "dw4/cri/adxb.h"
#include <stdio.h>
#include <string.h>
#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/adxdcd.h"
#include "dw4/cri/adxcrs.h"
#include "dw4/cri/adxerrs.h"
#include "dw4/cri/skg.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static void (*adxb_ahx_setextfunc)(void *ahx, unsigned short *keys) = 0;
void (*adxb_pl2_exec_func)(AdxbObj *obj, int v, short *src, short *dst) = 0;
void (*adxb_pl2_reset_func)(AdxbObj *obj) = 0;
static unsigned short adxb_key0 = 0;
static unsigned short adxb_key1 = 0;
static unsigned short adxb_key2 = 0;
static AdxbObj adxb_obj[16] = {0};


void ADXB_Destroy(AdxbObj *p);
void ADXB_EvokeDecode(AdxbObj *d);
int adxb_get_key(AdxbObj *adx, unsigned char ver, unsigned char type, int name,
                 unsigned short *k0, unsigned short *k1, unsigned short *k2);
void adxb_dec_cb_proc(AdxbObj *obj);

void ADXB_Init(void)
{
    ADXPD_Init();
    SKG_Init();
    memset(adxb_obj, 0, 0x1040);
}

void ADXB_Finish(void)
{
    ADXPD_Finish();
    SKG_Finish();
    memset(adxb_obj, 0, 0x1040);
}

short *adxb_DefGetWr(void *adxb, int *wpos, int *room, int *rest)
{
    AdxbObj *obj = adxb;

    *wpos = obj->curwpos;
    *room = obj->pcmbsize - obj->curwpos;
    *rest = obj->total_nsmpl - obj->total_ndecsmpl;
    return obj->pcmbuf;
}

void adxb_DefAddWr(void *adxb, int a, int b)
{
    AdxbObj *obj = adxb;

    obj->curwpos += b;
    obj->total_ndecsmpl += b;
}

/* matching construct: store-order search over the eight stores, 117 of 150 steps */
AdxbObj *ADXB_Create(int maxnch, short *pcmbuf, int pcmbsize, int pcmbdist)
{
    AdxbObj *p;
    int i;
    for (i = 0; i < 16; i++) {
        if (adxb_obj[i].used == 0) {
            break;
        }
    }
    if (i == 16) {
        return 0;
    }
    p = &adxb_obj[i];
    memset(p, 0, sizeof(*p));
    p->used = 1;
    p->xpd = ADXPD_Create();
    if (p->xpd == 0) {
        ADXB_Destroy(p);
        return 0;
    }
    p->maxnch = maxnch;
    p->pcmbuf = pcmbuf;
    p->pcmbsize = pcmbsize;
    p->pcmbdist = pcmbdist;
    p->getwrfunc = adxb_DefGetWr;
    p->getwrobj = p;
    p->addwrobj = p;
    p->addwrfunc = adxb_DefAddWr;
    p->ainf_len = 0;
    p->def_outvol = 0;
    p->def_pan[0] = -128;
    p->def_pan[1] = -128;
    memset(p->dataid, 0, 16);
    return p;
}

void ADXB_Destroy(AdxbObj *rec)
{
    if (rec != 0) {
        AdxPdObj *handle = rec->xpd;
        rec->xpd = 0;
        ADXPD_Destroy(handle);
        memset(rec, 0, sizeof(*rec));
        rec->used = 0;
    }
}

int ADXB_DecodeHeaderAdx(AdxbObj *obj, unsigned char *hdr, int size)
{
    unsigned short dly1[2];
    unsigned short dly2[2];
    unsigned short keys[4];
    short hdrlen;
    unsigned char ver;
    unsigned char flag;
    short k0;
    short k1;
    short k2;
    obj->hdcdflag = 1;
    if (ADX_DecodeInfo(hdr, size, &hdrlen, &obj->code, &obj->bps, &obj->blklen, &obj->nch, &obj->sfreq, &obj->total_nsmpl,
                     &obj->blknsmpl) < 0) {
        return 0;
    }
    if (obj->code >= 5) {
        if (obj->ahx == 0) {
            ADXERR_CallErrFunc2("E1060101 ADXB_DecodeHeaderAdx: ", "can't play AHX data by this handle");
            return -1;
        }
        obj->bps = 8;
        obj->blklen = obj->nch * 192;
        obj->blknsmpl = 96;
        obj->fmttype = 10;
        obj->cof = 0;
        obj->nloop = 0;
        obj->lp_type = 0;
        obj->lp_ins_nsmpl = 0;
        obj->lp_spos = 0;
        obj->lp_sofst = 0;
        obj->lp_epos = 0;
        obj->lp_eofst = 0;
        obj->total_ndecsmpl = 0;
        if (ADX_DecodeInfoExVer(hdr, size, &ver, &flag) < 0) {
            return 0;
        }
        keys[0] = 0;
        if (adxb_get_key(obj, ver, flag, obj->total_nsmpl, &keys[1], &keys[2], &keys[3]) < 0) {
            return -1;
        }
        if (adxb_ahx_setextfunc != 0) {
            adxb_ahx_setextfunc(obj->ahx, keys);
        }
    } else {
        if (ADX_DecodeInfoExVer(hdr, size, &ver, &flag) < 0) {
            return 0;
        }
        if (adxb_get_key(obj, ver, flag, obj->total_nsmpl, &k0, &k1, &k2) < 0) {
            return -1;
        }
        ADXPD_SetExtPrm(obj->xpd, k0, k1, k2);
        if (ADX_DecodeInfoExADPCM2(hdr, size, &obj->cof) < 0) {
            return 0;
        }
        if (ADX_DecodeInfoExIdly(hdr, size, dly1, dly2) < 0) {
            return 0;
        }
        ADXPD_SetCoef(obj->xpd, obj->sfreq, obj->cof);
        ADXPD_SetDly(obj->xpd, dly1, dly2);
        ADX_DecodeInfoExLoop(hdr, size, &obj->lp_ins_nsmpl, &obj->nloop, &obj->lp_type, &obj->lp_spos, &obj->lp_sofst, &obj->lp_epos, &obj->lp_eofst);
        ADX_DecodeInfoAinf(hdr, size, &obj->ainf_len, obj->dataid, &obj->def_outvol, obj->def_pan);
        obj->fmttype = 0;
    }
    obj->dp.nch = obj->nch;
    obj->dp.blksize = obj->blklen;
    obj->dp.blknsmpl = obj->blknsmpl;
    obj->dp.pcmbuf = obj->pcmbuf;
    obj->dp.pcmbsize = obj->pcmbsize;
    obj->dp.pcmbdist = obj->pcmbdist;
    obj->curwpos = 0;
    return hdrlen;
}

void ADXB_ResetDefFmt(AdxbObj *obj)
{
    obj->def_fmttype = 0;
}

void ADXB_SetDefPrm(AdxbObj *block)
{
    block->hdcdflag = 1;
    block->sfreq = 48000;
    block->nch = 2;
    block->bps = 16;
    block->total_nsmpl = 0x7fffffff;
    block->blklen = 127;
    block->blknsmpl = 1024;
    block->fmttype = block->def_fmttype;
    block->dp.nch = 2;
    block->dp.blksize = 127;
    block->dp.blknsmpl = 1024;
    block->dp.pcmbuf = block->pcmbuf;
    block->dp.pcmbsize = block->pcmbsize;
    block->dp.pcmbdist = block->pcmbdist;
    block->curwpos = 0;
    block->cof = 0;
    block->nloop = 0;
    block->lp_type = 0;
    block->lp_ins_nsmpl = 0;
    block->lp_spos = 0;
    block->lp_sofst = 0;
    block->lp_epos = 0;
    block->lp_eofst = 0;
    block->total_ndecsmpl = 0;
}

#define SWAP16(x) ((unsigned short)(((x) << 8) | ((x) >> 8)))
int ADXB_DecodeHeader(AdxbObj *dec, unsigned char *hdr, int size)
{
    if (SWAP16(*(unsigned short *)hdr) == 0x8000) {  /* the ADX mark is read as one halfword */
        return ADXB_DecodeHeaderAdx(dec, hdr, size);
    }
    if (ADXB_CheckSpsd(hdr) != 0) {
        return ADXB_DecodeHeaderSpsd(dec, hdr, size);
    }
    if (ADXB_CheckWav(hdr) != 0) {
        return ADXB_DecodeHeaderWav(dec, hdr, size);
    }
    if (ADXB_CheckAiff(hdr) != 0) {
        return ADXB_DecodeHeaderAiff(dec, hdr, size);
    }
    if (ADXB_CheckAu(hdr) != 0) {
        return ADXB_DecodeHeaderAu(dec, hdr, size);
    }
    if (ADXB_CheckAc3(hdr) != 0) {
        return ADXB_DecodeHeaderAc3(dec, hdr, size);
    }
    return -1;
}

void ADXB_EntryGetWrFunc(AdxbObj *obj, AdxbGetWrFunc cb, void *arg)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    obj->getwrfunc = cb;
    obj->getwrobj = arg;
}

void ADXB_EntryAddWrFunc(AdxbObj *obj, AdxbAddWrFunc cb, void *arg)
{
    obj->addwrfunc = cb;
    obj->addwrobj = arg;
}

short *ADXB_GetPcmBuf(AdxbObj *obj)
{
    return obj->pcmbuf;
}

int ADXB_GetFormat(AdxbObj *obj)
{
    return obj->fmttype;
}

int ADXB_GetSfreq(AdxbObj *obj)
{
    return obj->sfreq;
}

int ADXB_GetNumChan(AdxbObj *obj)
{
    if (obj->nch == 1 && obj->pl2 != 0) {
        return 2;
    }
    return obj->nch;
}

int ADXB_GetFmtBps(AdxbObj *obj)
{
    return obj->bps;
}

int ADXB_GetOutBps(AdxbObj *block)
{
    short mode = block->fmttype;
    if (mode == 0) {
        return 16;
    }
    if (mode == 2) {
        if (block->cdctype == 2) {
            return 4;
        }
        if (block->cdctype == 1) {
            return 8;
        }
        return 16;
    }
    if (mode == 1) {
        if (block->cdctype == 2) {
            return 4;
        }
        return 16;
    }
    return 16;
}

int ADXB_GetBlkSmpl(AdxbObj *obj)
{
    return obj->blknsmpl;
}

int ADXB_GetBlkLen(AdxbObj *obj)
{
    return obj->blklen;
}

int ADXB_GetTotalNumSmpl(AdxbObj *obj)
{
    return obj->total_nsmpl;
}

int ADXB_GetCof(AdxbObj *obj)
{
    return obj->cof;
}

int ADXB_GetLpInsNsmpl(AdxbObj *obj)
{
    return obj->lp_ins_nsmpl;
}

int ADXB_GetNumLoop(AdxbObj *obj)
{
    return obj->nloop;
}

int ADXB_GetLpStartPos(AdxbObj *obj)
{
    return obj->lp_spos;
}

int ADXB_GetLpStartOfst(AdxbObj *obj)
{
    int ofst;
    ofst = 0;
    if (obj != 0) {
        ofst = obj->lp_sofst;
    }
    return ofst;
}

int ADXB_GetLpEndPos(AdxbObj *obj)
{
    return obj->lp_epos;
}

int ADXB_GetLpEndOfst(AdxbObj *obj)
{
    return obj->lp_eofst;
}

int ADXB_GetAinfLen(AdxbObj *obj)
{
    return obj->ainf_len;
}

short ADXB_GetDefOutVol(AdxbObj *obj)
{
    return obj->def_outvol;
}

short ADXB_GetDefPan(AdxbObj *adxb, int ch)
{
    return adxb->def_pan[ch];
}

char *ADXB_GetDataId(AdxbObj *obj)
{
    return obj->dataid;
}

void ADXB_TakeSnapshot(AdxbObj *obj)
{
    ADXPD_GetDly(obj->xpd, obj->dly1, obj->dly2);
    ADXPD_GetExtPrm(obj->xpd, &obj->xp_key, &obj->xp_km, &obj->xp_ka);
}

void ADXB_RestoreSnapshot(AdxbObj *rec)
{
    ADXPD_SetDly(rec->xpd, rec->dly1, rec->dly2);
    ADXPD_SetExtPrm(rec->xpd, rec->xp_key, rec->xp_km, rec->xp_ka);
}

void ADXB_SetExtString(AdxbObj *block, const char *text)
{
    unsigned short first;
    unsigned short second;
    unsigned short third;
    SKG_GenerateKey(text, strlen(text), &first, &second, &third);
    block->k0 = first;
    block->km = second;
    block->ka = third;
}

void ADXB_SetDefExtString(const char *text)
{
    SKG_GenerateKey(text, strlen(text), &adxb_key0, &adxb_key1, &adxb_key2);
}

int adxb_get_key(AdxbObj *adx, unsigned char ver, unsigned char type, int name,
                 unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    char buf[16];
    if (ver < 4) {
        *k0 = 0;
        *k1 = 0;
        *k2 = 0;
    } else if (type >= 16) {
        sprintf(buf, "%08X", name);
        SKG_GenerateKey(buf, 8, k0, k1, k2);
    } else if (type >= 8) {
        if (adx->k0 == 0 && adx->km == 0 && adx->ka == 0) {
            adx->k0 = adxb_key0;
            adx->km = adxb_key1;
            adx->ka = adxb_key2;
        }
        *k0 = adx->k0;
        *k1 = adx->km;
        *k2 = adx->ka;
    } else {
        *k0 = 0;
        *k1 = 0;
        *k2 = 0;
    }
    return 0;
}

int ADXB_GetStat(AdxbObj *obj)
{
    return obj->stat;
}

void ADXB_EntryData(AdxbObj *block, char *buffer, int bytes)
{
    if (block->fmttype == 0) {
        block->dp.ibuf = buffer;
        block->dp.niblk = bytes / block->blklen;
        block->dp.ndecsmpl = 0;
    } else {
        block->dp.ibuf = buffer;
        block->dp.niblk = bytes / (block->bps / 8 * block->nch);
        block->dp.ndecsmpl = 0;
    }
    block->ndecsmpl = 0;
    block->ndeclen = 0;
    block->f248 = 0;
    block->cb_ndeclen = 0;
}

void ADXB_Start(AdxbObj *obj)
{
    if (obj->stat == 0) {
        obj->stat = 1;
    }
}

void ADXB_Stop(AdxbObj *rec)
{
    if (rec->pl2) {
        adxb_pl2_reset_func(rec);
    }
    ADXPD_Stop(rec->xpd);
    rec->stat = 0;
}

void ADXB_Reset(AdxbObj *obj)
{
    if (obj->stat == 3) {
        ADXPD_Reset(obj->xpd);
        obj->curwpos = 0;
        obj->stat = 0;
    }
}

int ADXB_GetDecDtLen(AdxbObj *obj)
{
    return obj->ndeclen;
}

int ADXB_GetDecNumSmpl(AdxbObj *obj)
{
    return obj->ndecsmpl;
}

void ADXB_EntryDecFunc(AdxbObj *obj, void (*cb)(void *context, int count, int bytes), void *context)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    obj->decfunc = cb;
    obj->decobj = context;
}

AdxPdObj *ADXB_GetAdxpd(AdxbObj *obj)
{
    return obj->xpd;
}

void ADXB_EvokeExpandMono(AdxbObj *obj, int n)
{
    AdxPdObj *pd;
    AdxDecPara *buf;
    buf = &obj->dp;
    pd = obj->xpd;
    ADXPD_EntryMono(pd, (unsigned char *)obj->dp.ibuf, n, buf->pcmbuf + buf->wpos, 0);
    ADXPD_Start(pd);
}

void ADXB_EvokeExpandSte(AdxbObj *obj, int n)
{
    short *obufl;
    AdxPdObj *pd;
    AdxDecPara *buf;
    buf = &obj->dp;
    pd = obj->xpd;
    obufl = buf->pcmbuf + buf->wpos;
    ADXPD_EntrySte(pd, (unsigned char *)obj->dp.ibuf, n * 2, obufl, obufl + buf->pcmbdist);
    ADXPD_Start(pd);
}

void ADXB_EvokeExpandPl2(AdxbObj *obj, int n)
{
    short *obufl;
    AdxPdObj *pd;
    AdxDecPara *buf;
    buf = &obj->dp;
    pd = obj->xpd;
    obufl = buf->pcmbuf + buf->wpos;
    ADXPD_EntryPl2(pd, (unsigned char *)obj->dp.ibuf, n, obufl, obufl + buf->pcmbdist);
    ADXPD_Start(pd);
}

void ADXB_EvokeDecode(AdxbObj *obj)
{
    AdxDecPara *buf = &obj->dp;
    int nblk;
    int size;
    int blksmpl;
    int pos;
    int end;
    int endblk;
    int sizeblk;
    int rest;
    int lim;
    int sizesmpl;
    int n;

    nblk = buf->niblk / buf->nch;
    size = buf->pcmbsize;
    blksmpl = buf->blknsmpl;
    pos = buf->wpos;
    end = buf->lp_nsmpl;

    endblk = (end + blksmpl - 1) / blksmpl;
    sizeblk = (size - pos + blksmpl - 1) / blksmpl;
    rest = blksmpl - (end + blksmpl - 1) % blksmpl - 1;

    lim = buf->nroom;
    sizesmpl = sizeblk * blksmpl;

    if (endblk < sizeblk) {
        if (pos + sizesmpl - rest < size) {
            sizeblk += 1;
        }
    }
    if (end < lim) {
        lim += rest;
    }

    n = MIN(lim / blksmpl, nblk);
    n = MIN(endblk, n);
    n = MIN(sizeblk, n);

    if (buf->nch == 2) {
        ADXB_EvokeExpandSte(obj, n);
    } else if (obj->pl2 != 0) {
        ADXB_EvokeExpandPl2(obj, n);
    } else {
        ADXB_EvokeExpandMono(obj, n);
    }
}

void memcpy2(short *dst, short *src, int count)
{
    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

void ADXB_CopyExtraBufSte(short *buffer, int offset, int second, int count)
{
    memcpy2(buffer, buffer + offset, count);
    memcpy2(buffer + second, buffer + (second + offset), count);
}

void ADXB_CopyExtraBufMono(short *buffer, int offset, int unused, int count)
{
    memcpy2(buffer, buffer + offset, count);
}

/* matching construct: statement-order search, first step */
void ADXB_EndDecode(AdxbObj *d)
{
    AdxDecPara *b = &d->dp;
    int blk;
    int nch;
    int t;
    int r;
    int q;
    int done;
    int n;
    int pos;
    int size;
    int a;
    int blklen;
    short *dst;
    blk = b->blknsmpl;
    t = b->lp_nsmpl + blk - 1;
    size = d->pcmbsize;
    dst = b->pcmbuf;
    a = d->pcmbdist;
    blklen = b->blksize;
    q = t / blk;
    r = blk - t % blk - 1;
    pos = b->wpos;
    done = ADXPD_GetNumBlk(d->xpd);
    nch = b->nch;
    n = done * blk / nch;
    n = (done < q * nch) ? n : n - r;
    pos += n;
    d->ndeclen = done * blklen;
    d->ndecsmpl = n;
    if (pos >= size) {
        pos -= size;
        if (b->nch == 2 || d->pl2 != 0) {
            ADXB_CopyExtraBufSte(dst, size, a, pos);
        } else {
            ADXB_CopyExtraBufMono(dst, size, a, pos);
        }
    }
}

void ADXB_ExecOneAdx(AdxbObj *w)
{
    AdxPdObj *pd;
    int i;
    if (w->stat == 1) {
        if (ADXPD_GetStat(w->xpd) == 0) {
            w->getwrfunc(w->getwrobj, &w->dp.wpos, &w->dp.nroom, &w->dp.lp_nsmpl);
            ADXB_EvokeDecode(w);
            w->stat = 2;
        }
    }
    if (w->stat == 2) {
        ADXPD_ExecHndl(w->xpd);
        if (ADXPD_GetStat(w->xpd) == 3) {
            if (w->pl2 != 0) {
                pd = w->xpd;
                ADXCRS_Lock();
                for (i = 0; i < pd->nblk_decoded * 32; i++) {
                    adxb_pl2_exec_func(w, pd->obufl[i], &pd->obufl[i], &pd->obufr[i]);
                }
                ADXCRS_Unlock();
            }
            ADXB_EndDecode(w);
            ADXPD_Reset(w->xpd);
            w->addwrfunc(w->addwrobj, w->ndeclen, w->ndecsmpl);
            w->stat = 3;
        }
    }
}

void ADXB_ExecHndl(AdxbObj *v)
{
    if (v->fmttype == 0) {
        ADXB_ExecOneAdx(v);
    } else if (v->fmttype == 10) {
        ADXB_ExecOneAhx(v);
    } else if (v->fmttype == 2) {
        ADXB_ExecOneSpsd(v);
    } else if (v->fmttype == 3) {
        ADXB_ExecOneAiff(v);
    } else if (v->fmttype == 4) {
        ADXB_ExecOneAu(v);
    } else if (v->fmttype == 1) {
        ADXB_ExecOneWav(v);
    } else if (v->fmttype == 15) {
        ADXB_ExecOneAc3(v);
    }
    if (v->decfunc != 0) {
        adxb_dec_cb_proc(v);
    }
}

void adxb_dec_cb_proc(AdxbObj *block)
{
    int frames;
    int count = block->ndeclen - block->cb_ndeclen;
    frames = block->ndecsmpl; /* matching construct: permuter — ndecsmpl read into a local before the wrap test */
    if (count < 0) {
        count += 0x7fffffff;
    }
    block->decfunc(block->decobj, count, frames * block->nch * 2);
    block->cb_ndeclen = block->ndeclen;
}

void ADXB_ExecServer(void)
{
    AdxbObj *slot = adxb_obj;
    int remaining = 15;
    do {
        if (slot->used == 1) {
            ADXB_ExecHndl(slot);
        }
        remaining--;
        slot++;
    } while (remaining >= 0);
}
