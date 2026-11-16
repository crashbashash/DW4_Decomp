#include "dw4/cri/adxb.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static void (*adxb_ahx_setextfunc)(void *ahx, unsigned short *keys) = 0;
void (*adxb_pl2_exec_func)(AdxbObj *obj, int v, short *src, short *dst) = 0;
void (*adxb_pl2_reset_func)(AdxbObj *obj) = 0;
static unsigned short adxb_key0 = 0;
static unsigned short adxb_key1 = 0;
static unsigned short adxb_key2 = 0;
static AdxbObj adxb_obj[16] = {0};

void *memset(void *dst, int value, unsigned int size);
unsigned int strlen(const char *string);
int sprintf(char *dst, const char *format, ...);

void SKG_Init(void);
void SKG_Finish(void);
void SKG_GenerateKey(const char *text, unsigned int length, unsigned short *first, unsigned short *second,
                  unsigned short *third);
int ADX_DecodeInfo(unsigned short *hdr, int size, short *hdrlen, signed char *type, signed char *bits,
                 signed char *blksize, signed char *nch, int *rate, int *total, int *f16);
int ADX_DecodeInfoExVer(unsigned short *hdr, int size, unsigned char *ver, unsigned char *flag);
int ADX_DecodeInfoExADPCM2(unsigned short *hdr, int size, short *out);
int ADX_DecodeInfoExIdly(unsigned short *hdr, int size, unsigned short *dly1, unsigned short *dly2);
void ADX_DecodeInfoExLoop(unsigned short *hdr, int size, int *f32, short *f36, short *f38, int *f40, int *f44, int *f48,
                  int *f52);
void ADX_DecodeInfoAinf(unsigned short *hdr, int size, int *f204, char *f208, short *f224, short *f226);
void ADXERR_CallErrFunc2(const char *code, const char *message);

void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);

int ADXB_CheckSpsd(unsigned short *hdr);
int ADXB_DecodeHeaderSpsd(AdxbObj *dec, unsigned short *hdr, int size);
int ADXB_CheckWav(unsigned short *hdr);
int ADXB_DecodeHeaderWav(AdxbObj *dec, unsigned short *hdr, int size);
int ADXB_CheckAiff(unsigned short *hdr);
int ADXB_DecodeHeaderAiff(AdxbObj *dec, unsigned short *hdr, int size);
int ADXB_CheckAu(unsigned short *hdr);
int ADXB_DecodeHeaderAu(AdxbObj *dec, unsigned short *hdr, int size);
int ADXB_CheckAc3(unsigned short *hdr);
int ADXB_DecodeHeaderAc3(AdxbObj *dec, unsigned short *hdr, int size);

void ADXB_ExecOneAhx(AdxbObj *obj);
void ADXB_ExecOneSpsd(AdxbObj *obj);
void ADXB_ExecOneAiff(AdxbObj *obj);
void ADXB_ExecOneAu(AdxbObj *obj);
void ADXB_ExecOneWav(AdxbObj *obj);
void ADXB_ExecOneAc3(AdxbObj *obj);

short *adxb_DefGetWr(AdxbObj *obj, int *wpos, int *room, int *rest);
void ADXB_Destroy(AdxbObj *p);
void ADXB_EvokeDecode(AdxbObj *d);
int adxb_get_key(AdxbObj *adx, unsigned char ver, unsigned char type, int name,
                 unsigned short *k0, unsigned short *k1, unsigned short *k2);
void FUN_0025e5a0(AdxbObj *obj);

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

short *adxb_DefGetWr(AdxbObj *obj, int *wpos, int *room, int *rest)
{
    *wpos = obj->wpos;
    *room = obj->pcmbsize - obj->wpos;
    *rest = obj->total_nsmpl - obj->dec_nsmpl;
    return obj->pcmbuf;
}

void adxb_DefAddWr(AdxbObj *obj, int a, int b)
{
    obj->wpos += b;
    obj->dec_nsmpl += b;
}

/* matching construct: store-order search over the eight stores, 117 of 150 steps */
AdxbObj *ADXB_Create(int a0, short *a1, int a2, int a3)
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
    p->adxpd = ADXPD_Create();
    if (p->adxpd == 0) {
        ADXB_Destroy(p);
        return 0;
    }
    p->f56 = a0;
    p->pcmbuf = a1;
    p->pcmbsize = a2;
    p->pcmbdist = a3;
    p->cb120 = adxb_DefGetWr;
    p->obj124 = p;
    p->obj132 = p;
    p->cb128 = adxb_DefAddWr;
    p->f204 = 0;
    p->f224 = 0;
    p->f226[0] = -128;
    p->f226[1] = -128;
    memset(p->f208, 0, 16);
    return p;
}

void ADXB_Destroy(AdxbObj *rec)
{
    if (rec != 0) {
        AdxPdObj *handle = rec->adxpd;
        rec->adxpd = 0;
        ADXPD_Destroy(handle);
        memset(rec, 0, sizeof(*rec));
        rec->used = 0;
    }
}

int ADXB_DecodeHeaderAdx(AdxbObj *obj, unsigned short *hdr, int size)
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
    obj->hdr_set = 1;
    if (ADX_DecodeInfo(hdr, size, &hdrlen, &obj->hdrtype, &obj->fmtbps, &obj->blklen, &obj->nch, &obj->sfreq, &obj->total_nsmpl,
                     &obj->blksmpl) < 0) {
        return 0;
    }
    if (obj->hdrtype >= 5) {
        if (obj->ahx == 0) {
            ADXERR_CallErrFunc2("E1060101 ADXB_DecodeHeaderAdx: ", "can't play AHX data by this handle");
            return -1;
        }
        obj->fmtbps = 8;
        obj->blklen = obj->nch * 192;
        obj->blksmpl = 96;
        obj->format = 10;
        obj->cof = 0;
        obj->nloop = 0;
        obj->lptype = 0;
        obj->lpins_nsmpl = 0;
        obj->lp_start_pos = 0;
        obj->lp_start_ofst = 0;
        obj->lp_end_pos = 0;
        obj->lp_end_ofst = 0;
        obj->dec_nsmpl = 0;
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
        ADXPD_SetExtPrm(obj->adxpd, k0, k1, k2);
        if (ADX_DecodeInfoExADPCM2(hdr, size, &obj->cof) < 0) {
            return 0;
        }
        if (ADX_DecodeInfoExIdly(hdr, size, dly1, dly2) < 0) {
            return 0;
        }
        ADXPD_SetCoef(obj->adxpd, obj->sfreq, obj->cof);
        ADXPD_SetDly(obj->adxpd, dly1, dly2);
        ADX_DecodeInfoExLoop(hdr, size, &obj->lpins_nsmpl, &obj->nloop, &obj->lptype, &obj->lp_start_pos, &obj->lp_start_ofst, &obj->lp_end_pos, &obj->lp_end_ofst);
        ADX_DecodeInfoAinf(hdr, size, &obj->f204, obj->f208, &obj->f224, obj->f226);
        obj->format = 0;
    }
    obj->buf.nch = obj->nch;
    obj->buf.blklen = obj->blklen;
    obj->buf.blksmpl = obj->blksmpl;
    obj->buf.pcmbuf = obj->pcmbuf;
    obj->buf.pcmbsize = obj->pcmbsize;
    obj->buf.pcmbdist = obj->pcmbdist;
    obj->wpos = 0;
    return hdrlen;
}

void FUN_0025d830(AdxbObj *obj)
{
    obj->def_format = 0;
}

void adxb_SetDefaultFmt(AdxbObj *block)
{
    block->hdr_set = 1;
    block->sfreq = 48000;
    block->nch = 2;
    block->fmtbps = 16;
    block->total_nsmpl = 0x7fffffff;
    block->blklen = 127;
    block->blksmpl = 1024;
    block->format = block->def_format;
    block->buf.nch = 2;
    block->buf.blklen = 127;
    block->buf.blksmpl = 1024;
    block->buf.pcmbuf = block->pcmbuf;
    block->buf.pcmbsize = block->pcmbsize;
    block->buf.pcmbdist = block->pcmbdist;
    block->wpos = 0;
    block->cof = 0;
    block->nloop = 0;
    block->lptype = 0;
    block->lpins_nsmpl = 0;
    block->lp_start_pos = 0;
    block->lp_start_ofst = 0;
    block->lp_end_pos = 0;
    block->lp_end_ofst = 0;
    block->dec_nsmpl = 0;
}

#define SWAP16(x) ((unsigned short)(((x) << 8) | ((x) >> 8)))
int ADXB_DecodeHeader(AdxbObj *dec, unsigned short *hdr, int size)
{
    if (SWAP16(*hdr) == 0x8000) {
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

void ADXB_EntryGetWrFunc(AdxbObj *obj, short *(*cb)(AdxbObj *obj, int *a, int *b, int *c), AdxbObj *arg)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    obj->cb120 = cb;
    obj->obj124 = arg;
}

void ADXB_EntryAddWrFunc(AdxbObj *obj, void (*cb)(AdxbObj *obj, int a, int b), AdxbObj *arg)
{
    obj->cb128 = cb;
    obj->obj132 = arg;
}

short *ADXB_GetPcmBuf(AdxbObj *obj)
{
    return obj->pcmbuf;
}

short ADXB_GetFormat(AdxbObj *obj)
{
    return obj->format;
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

char ADXB_GetFmtBps(AdxbObj *obj)
{
    return obj->fmtbps;
}

int ADXB_GetOutBps(AdxbObj *block)
{
    short mode = block->format;
    if (mode == 0) {
        return 16;
    }
    if (mode == 2) {
        if (block->pcmfmt == 2) {
            return 4;
        }
        if (block->pcmfmt == 1) {
            return 8;
        }
        return 16;
    }
    if (mode == 1) {
        if (block->pcmfmt == 2) {
            return 4;
        }
        return 16;
    }
    return 16;
}

int ADXB_GetBlkSmpl(AdxbObj *obj)
{
    return obj->blksmpl;
}

char ADXB_GetBlkLen(AdxbObj *obj)
{
    return obj->blklen;
}

int ADXB_GetTotalNumSmpl(AdxbObj *obj)
{
    return obj->total_nsmpl;
}

short ADXB_GetCof(AdxbObj *obj)
{
    return obj->cof;
}

int ADXB_GetLpInsNsmpl(AdxbObj *obj)
{
    return obj->lpins_nsmpl;
}

short ADXB_GetNumLoop(AdxbObj *obj)
{
    return obj->nloop;
}

int ADXB_GetLpStartPos(AdxbObj *obj)
{
    return obj->lp_start_pos;
}

int FUN_0025db48(AdxbObj *obj)
{
    int var_v0;
    var_v0 = 0;
    if (obj != 0) {
        var_v0 = obj->lp_start_ofst;
    }
    return var_v0;
}

int ADXB_GetLpEndPos(AdxbObj *obj)
{
    return obj->lp_end_pos;
}

int ADXB_GetLpEndOfst(AdxbObj *obj)
{
    return obj->lp_end_ofst;
}

int FUN_0025db70(AdxbObj *obj)
{
    return obj->f204;
}

short FUN_0025db78(AdxbObj *obj)
{
    return obj->f224;
}

short ADXB_GetDefPan(int arg0, int arg1)
{
    arg1 *= 2;
    arg1 += arg0;
    return *(short *)((char *)arg1 + 226);
}

char *FUN_0025db90(AdxbObj *obj)
{
    return obj->f208;
}

void ADXB_TakeSnapshot(AdxbObj *obj)
{
    ADXPD_GetDly(obj->adxpd, obj->dly1, obj->dly2);
    ADXPD_GetExtPrm(obj->adxpd, &obj->f166, &obj->f168, &obj->f170);
}

void FUN_0025dbd8(AdxbObj *rec)
{
    ADXPD_SetDly(rec->adxpd, rec->dly1, rec->dly2);
    ADXPD_SetExtPrm(rec->adxpd, rec->f166, rec->f168, rec->f170);
}

void FUN_0025dc18(AdxbObj *block, const char *text)
{
    unsigned short first;
    unsigned short second;
    unsigned short third;
    SKG_GenerateKey(text, strlen(text), &first, &second, &third);
    block->f160 = first;
    block->f162 = second;
    block->f164 = third;
}

void FUN_0025dc80(const char *text)
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
        if (adx->f160 == 0 && adx->f162 == 0 && adx->f164 == 0) {
            adx->f160 = adxb_key0;
            adx->f162 = adxb_key1;
            adx->f164 = adxb_key2;
        }
        *k0 = adx->f160;
        *k1 = adx->f162;
        *k2 = adx->f164;
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

void ADXB_EntryData(AdxbObj *block, int buffer, int bytes)
{
    if (block->format == 0) {
        block->buf.ibuf = (char *)buffer;
        block->buf.len = bytes / block->blklen;
        block->f116 = 0;
    } else {
        block->buf.ibuf = (char *)buffer;
        block->buf.len = bytes / (block->fmtbps / 8 * block->nch);
        block->f116 = 0;
    }
    block->f144 = 0;
    block->f148 = 0;
    block->f248 = 0;
    block->f244 = 0;
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
    ADXPD_Stop(rec->adxpd);
    rec->stat = 0;
}

void ADXB_Reset(AdxbObj *obj)
{
    if (obj->stat == 3) {
        ADXPD_Reset(obj->adxpd);
        obj->wpos = 0;
        obj->stat = 0;
    }
}

int ADXB_GetDecDtLen(AdxbObj *obj)
{
    return obj->f148;
}

int ADXB_GetDecNumSmpl(AdxbObj *obj)
{
    return obj->f144;
}

void FUN_0025df00(AdxbObj *obj, void (*cb)(void *context, int count, int bytes), void *context)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    obj->f252 = cb;
    obj->f256 = context;
}

AdxPdObj *ADXB_GetAdxpd(AdxbObj *obj)
{
    return obj->adxpd;
}

void ADXB_EvokeExpandMono(AdxbObj *obj, int n)
{
    AdxPdObj *pd;
    AdxbBuf *buf;
    buf = &obj->buf;
    pd = obj->adxpd;
    ADXPD_EntryMono(pd, (unsigned char *)obj->buf.ibuf, n, buf->pcmbuf + buf->pos, 0);
    ADXPD_Start(pd);
}

void ADXB_EvokeExpandSte(AdxbObj *obj, int n)
{
    short *obufl;
    AdxPdObj *pd;
    AdxbBuf *buf;
    buf = &obj->buf;
    pd = obj->adxpd;
    obufl = buf->pcmbuf + buf->pos;
    ADXPD_EntrySte(pd, (unsigned char *)obj->buf.ibuf, n * 2, obufl, obufl + buf->pcmbdist);
    ADXPD_Start(pd);
}

void ADXB_EvokeExpandPl2(AdxbObj *obj, int n)
{
    short *obufl;
    AdxPdObj *pd;
    AdxbBuf *buf;
    buf = &obj->buf;
    pd = obj->adxpd;
    obufl = buf->pcmbuf + buf->pos;
    ADXPD_EntryPl2(pd, (unsigned char *)obj->buf.ibuf, n, obufl, obufl + buf->pcmbdist);
    ADXPD_Start(pd);
}

void ADXB_EvokeDecode(AdxbObj *obj)
{
    AdxbBuf *buf = &obj->buf;
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

    nblk = buf->len / buf->nch;
    size = buf->pcmbsize;
    blksmpl = buf->blksmpl;
    pos = buf->pos;
    end = buf->end;

    endblk = (end + blksmpl - 1) / blksmpl;
    sizeblk = (size - pos + blksmpl - 1) / blksmpl;
    rest = blksmpl - (end + blksmpl - 1) % blksmpl - 1;

    lim = buf->lim;
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
    AdxbBuf *b = &d->buf;
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
    blk = b->blksmpl;
    t = b->end + blk - 1;
    size = d->pcmbsize;
    dst = b->pcmbuf;
    a = d->pcmbdist;
    blklen = b->blklen;
    q = t / blk;
    r = blk - t % blk - 1;
    pos = b->pos;
    done = ADXPD_GetNumBlk(d->adxpd);
    nch = b->nch;
    n = done * blk / nch;
    n = (done < q * nch) ? n : n - r;
    pos += n;
    d->f148 = done * blklen;
    d->f144 = n;
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
        if (ADXPD_GetStat(w->adxpd) == 0) {
            w->cb120(w->obj124, &w->buf.pos, &w->buf.lim, &w->buf.end);
            ADXB_EvokeDecode(w);
            w->stat = 2;
        }
    }
    if (w->stat == 2) {
        ADXPD_ExecHndl(w->adxpd);
        if (ADXPD_GetStat(w->adxpd) == 3) {
            if (w->pl2 != 0) {
                pd = w->adxpd;
                ADXCRS_Lock();
                for (i = 0; i < pd->nblk_decoded * 32; i++) {
                    adxb_pl2_exec_func(w, pd->obufl[i], &pd->obufl[i], &pd->obufr[i]);
                }
                ADXCRS_Unlock();
            }
            ADXB_EndDecode(w);
            ADXPD_Reset(w->adxpd);
            w->cb128(w->obj132, w->f148, w->f144);
            w->stat = 3;
        }
    }
}

void FUN_0025e4b8(AdxbObj *v)
{
    if (v->format == 0) {
        ADXB_ExecOneAdx(v);
    } else if (v->format == 10) {
        ADXB_ExecOneAhx(v);
    } else if (v->format == 2) {
        ADXB_ExecOneSpsd(v);
    } else if (v->format == 3) {
        ADXB_ExecOneAiff(v);
    } else if (v->format == 4) {
        ADXB_ExecOneAu(v);
    } else if (v->format == 1) {
        ADXB_ExecOneWav(v);
    } else if (v->format == 15) {
        ADXB_ExecOneAc3(v);
    }
    if (v->f252 != 0) {
        FUN_0025e5a0(v);
    }
}

void FUN_0025e5a0(AdxbObj *block)
{
    int frames;
    int count = block->f148 - block->f244;
    frames = block->f144; /* matching construct: permuter — f144 read into a local before the wrap test */
    if (count < 0) {
        count += 0x7fffffff;
    }
    block->f252(block->f256, count, frames * block->nch * 2);
    block->f244 = block->f148;
}

void ADXB_ExecServer(void)
{
    AdxbObj *slot = adxb_obj;
    int remaining = 15;
    do {
        if (slot->used == 1) {
            FUN_0025e4b8(slot);
        }
        remaining--;
        slot++;
    } while (remaining >= 0);
}
