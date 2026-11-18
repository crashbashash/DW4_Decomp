#include <string.h>
#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/adxenc.h"
#include "dw4/cri/adxcrs.h"
#include "dw4/cri/adxdcd.h"
#include "dw4/cri/skg.h"

/* CRI's _iir_filt: the second-order predictor the encoder runs to rebuild what the decoder will hear. */
typedef struct IirFilt {
    signed char used;   /* 0x00 */
    char rsv1;          /* 0x01 */
    short rsv2;         /* 0x02 */
    short k0;           /* 0x04 */
    short k1;           /* 0x06 */
    short d0;           /* 0x08 */
    short d1;           /* 0x0a */
} IirFilt;

/* CRI's predict_filt: one channel's prediction residual, its scale and its quantized nibbles. */
typedef struct PredictFilt {
    char used;                  /* 0x00 */
    char rsv1;                  /* 0x01 */
    short rsv2;                 /* 0x02 */
    short k0;                   /* 0x04 */
    short k1;                   /* 0x06 */
    short d0;                   /* 0x08 */
    short d1;                   /* 0x0a */
    short d0_0;                 /* 0x0c */
    short d1_0;                 /* 0x0e */
    short d0_1;                 /* 0x10 */
    short d1_1;                 /* 0x12 */
    int nsmpl;                  /* 0x14 */
    short rsig[32];             /* 0x18 */
    signed char rsig_q[32];     /* 0x58 */
    int max;                    /* 0x78 */
    short gain;                 /* 0x7c */
    char pad126[2];
    double dgain;               /* 0x80 */
    IirFilt *iflt;              /* 0x88 */
    char pad140[4];
} PredictFilt;

/* CRI's ADX_SJENC, grown in this build from 728 to 760 bytes by the AINF and common-information members. */
struct AdxEnc {
    signed char used;           /* 0x00 */
    signed char stat;           /* 0x01 */
    signed char maxnch;         /* 0x02 */
    signed char endflag;        /* 0x03 */
    SfdSj *sji[2];              /* 0x04 */
    SfdSj *sjo;                 /* 0x0c */
    SfdSjChunk cki[2];          /* 0x10 */
    SfdSjChunk cko;             /* 0x20 */
    int total_encsmpl;          /* 0x28 */
    int total_encdtlen;         /* 0x2c */
    int encpos;                 /* 0x30 */
    int maxencsmpl;             /* 0x34 */
    int org_nsmpl;              /* 0x38 */
    int total_nsmpl;            /* 0x3c */
    int strm_nsmpl;             /* 0x40 */
    int nsmpl_blk;              /* 0x44 */
    int hdinfo_size;            /* 0x48 */
    int code;                   /* 0x4c */
    int blklen;                 /* 0x50 */
    int bps;                    /* 0x54 */
    int nch;                    /* 0x58 */
    int sfreq;                  /* 0x5c */
    int encd_nsmpl;             /* 0x60 */
    int cof;                    /* 0x64 */
    int ins_nsmpl;              /* 0x68 */
    int nloop;                  /* 0x6c */
    int lp_spos;                /* 0x70 */
    int lp_sofst;               /* 0x74 */
    int lp_epos;                /* 0x78 */
    int lp_eofst;               /* 0x7c */
    PredictFilt *pflt[2];       /* 0x80 */
    short preblk_d0[2];         /* 0x88 */
    short preblk_d1[2];         /* 0x8c */
    short osig[2][32];          /* 0x90 */
    short rsig[2][32];          /* 0x110 */
    short rsig_g[2][32];        /* 0x190 */
    short rsig_q[2][32];        /* 0x210 */
    short gain[2];              /* 0x290 */
    char pad660[4];
    double dgain[2];            /* 0x298 */
    int sdata[2][4];            /* 0x2a8: one block's packed nibbles per channel */
    short idly0[2];             /* 0x2c8 */
    short idly1[2];             /* 0x2cc */
    unsigned short key;         /* 0x2d0 */
    unsigned short km;          /* 0x2d2 */
    unsigned short ka;          /* 0x2d4 */
    signed char ainf_flg;       /* 0x2d6: the header carries an AINF block */
    char dataid[16];            /* 0x2d7 */
    char pad743;
    short outvol;               /* 0x2e8 */
    short outpan[2];            /* 0x2ea */
    signed char cinf_flg;       /* 0x2ee */
    char pad751;
    void *cinf;                 /* 0x2f0 */
    int cinf_len;               /* 0x2f4 */
};

extern int adxkey_init_cnt;
extern void (*adxkey_err_func)(void *obj, const char *msg);
extern void *adxkey_err_obj;
extern int AdxGainDataMax;
extern char *cri_str;
extern AdxEnc adxsje_obj[8];
extern IirFilt adxsje_iirflt_obj[16];
extern PredictFilt adxsje_prdflt_obj[16];
extern const char CRI_MW[];
extern const char text_ADXENC_DLL_Ver_1_09_Oct_6_2004[];

int abs(int value);
int adxsje_calc_rsig(AdxEnc *e, int ch);
void adxsje_set_rsig(AdxEnc *e, int ch);
int adxsje_output_header(AdxEnc *e, SfdSj *out);

int ADXKEY_NopFunc(void)
{
    return 0;
}

int ADXKEY_EntryErrFunc(void (*func)(void *obj, const char *msg), void *obj)
{
    adxkey_err_func = func;
    adxkey_err_obj = obj;
    return 0;
}

int ADXKEY_CallErrFunc(const char *msg)
{
    if (adxkey_err_func != 0) {
        adxkey_err_func(adxkey_err_obj, msg);
    }
    return 0;
}

int ADXKEY_Init(void)
{
    adxkey_init_cnt += 1;
    return 0;
}

int ADXKEY_Finish(void)
{
    adxkey_init_cnt -= 1;
    return 0;
}

int ADXKEY_GenerateKey(const char *str, int len, unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    int i;
    short a;
    short b;
    short c;

    if (adxkey_init_cnt == 0) {
        ADXKEY_Init();
    }
    *k0 = 0;
    *k1 = 0;
    *k2 = 0;
    if (str == 0 && len <= 0) {
        return 0;
    }
    a = skg_tbl[256];
    for (i = 0; i < len; i++) {
        a = skg_tbl[a * skg_tbl[128 + str[i]] % 1024];
    }
    b = skg_tbl[512];
    for (i = 0; i < len; i++) {
        b = skg_tbl[b * skg_tbl[128 + str[i]] % 1024];
    }
    c = skg_tbl[768];
    for (i = 0; i < len; i++) {
        c = skg_tbl[c * skg_tbl[128 + str[i]] % 1024];
    }
    *k0 = a;
    *k1 = b;
    *k2 = c;
    return 0;
}

int ADXKEY_GetDefKey(unsigned short *k0, unsigned short *k1, unsigned short *k2)
{
    if (adxkey_init_cnt == 0) {
        ADXKEY_Init();
    }
    ADXKEY_GenerateKey(CRI_MW, 6, k0, k1, k2);
    return 0;
}

int ADXKEY_GetNextKey(unsigned short *x, unsigned short *mul, unsigned short *add)
{
    *x = *x * *mul + *add;
    return 0;
}

int ADXSJE_GetVersion(void)
{
    return 256;
}

const char *ADXSJE_GetVerStr(void)
{
    return text_ADXENC_DLL_Ver_1_09_Oct_6_2004;
}

int adxsje_nsmpl_to_ofst(int count, int base, int bits)
{
    return (bits + 31) / 32 * count * 18 + base + 4;
}

void ADXSJE_CalcLpInfo(int nch, int len, int len2, int *hdrlen, int *pad, int *size, int *size2)
{
    int blk;
    int nblk;
    int body;
    int hdr;
    int tail;

    blk = nch == 1 ? 64 : 32;
    *pad = (blk - len % blk) % blk;
    nblk = (len + *pad) / 32 * nch;
    body = nblk * 18;
    hdr = ADX_CalcHdrInfoLen(1, 0, 4, 4);
    tail = (2048 - (body + hdr + 4) % 2048) % 2048;
    *hdrlen = hdr + tail;
    *size = adxsje_nsmpl_to_ofst(nch, *hdrlen, len + *pad);
    *size2 = adxsje_nsmpl_to_ofst(nch, *hdrlen, len2 + *pad);
}

int ADXSJE_GetInfo(unsigned char *data, int size, int *out_c, int *out_e, int *out_f, int *out_g)
{
    short value_a;
    signed char value_b;
    signed char value_c;
    signed char value_d;
    signed char value_e;
    int value_h;
    int result;

    result = ADX_DecodeInfo(data, size, &value_a, &value_b, &value_c, &value_d, &value_e, out_f, out_g, &value_h);
    *out_e = value_e;
    *out_c = value_c;
    return result;
}

int adxsje_write68(void *src, int size, int n, SfdSj *sj)
{
    SfdSjChunk ck;
    int nbyte;
    int i;
    int *s4;
    int *d4;
    short *s2;
    short *d2;
    int w;

    nbyte = size * n;
    sj->vtbl->getChunk(sj, 0, nbyte, &ck);
    if (ck.len < nbyte) {
        sj->vtbl->ungetChunk(sj, 0, &ck);
        return 0;
    }
    if (size == 4) {
        s4 = src;
        d4 = (int *)ck.data;
        for (i = 0; i < n; i++) {
            w = *s4++;
            *d4++ = ((w >> 24) & 0xff) | ((w >> 8) & 0xff00) | ((w << 8) & 0xff0000) | (w << 24);
        }
    } else if (size == 2) {
        s2 = src;
        d2 = (short *)ck.data;
        for (i = 0; i < n; i++) {
            *d2++ = ((*s2 >> 8) & 0xff) | ((*s2 << 8) & 0xff00);
            s2++;
        }
    } else if (size == 1) {
        memcpy(ck.data, src, (unsigned short)n);
    } else {
        for (;;) {
        }
    }
    sj->vtbl->putChunk(sj, 1, &ck);
    return n;
}

void iirflt_init(void)
{
    memset(adxsje_iirflt_obj, 0, sizeof(adxsje_iirflt_obj));
}

IirFilt *iirflt_create(void)
{
    IirFilt *entry;
    int i;

    for (i = 0; i < 16; i++) {
        entry = &adxsje_iirflt_obj[i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i < 16) {
        return entry;
    }
    return 0;
}

void iirflt_destroy(IirFilt *entry)
{
    if (entry != 0) {
        entry->used = 0;
        memset(entry, 0, sizeof(IirFilt));
    }
}

void iirflt_set_coef(IirFilt *p, short k0, short k1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    p->k0 = k0;
    p->k1 = k1;
}

void iirflt_set_delay(IirFilt *p, short h0, short h1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    p->d0 = h0;
    p->d1 = h1;
}

void iirflt_get_delay(IirFilt *p, unsigned short *h0, unsigned short *h1)
{
    unsigned short t = p->d0;
    *h0 = t;
    *h1 = p->d1;
}

short iirflt_put_sig(IirFilt *state, short input)
{
    int value;
    short output;

    if (state != 0) {
        value = ((state->k0 * state->d0 + state->k1 * state->d1) >> 12) + input;
        if (value < 32767) {
            output = value < -32768 ? -32768 : value;
        } else {
            output = 32767;
        }
        state->d1 = state->d0;
        state->d0 = output;
        return output;
    }
    return input;
}

PredictFilt *pflt_create(int nsmpl)
{
    IirFilt *pred = iirflt_create();
    PredictFilt *entry;
    int i;

    if (pred == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        entry = &adxsje_prdflt_obj[i];
        if (entry->used == 0) {
            break;
        }
    }
    /* Retail writes these even when the table is full (into the last entry). */
    entry->nsmpl = nsmpl;
    entry->iflt = pred;
    if (i < 16) {
        entry->used = 1;
        return entry;
    }
    return 0;
}

void pflt_destroy(PredictFilt *entry)
{
    if (entry != 0) {
        entry->used = 0;
        memset(entry, 0, sizeof(PredictFilt));
    }
}

void pflt_set_coef(PredictFilt *f, short k0, short k1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    f->k0 = k0;
    f->k1 = k1;
}

void pflt_calc_coef(PredictFilt *f, int id, int arg)
{
    short first;
    short second;

    ADX_GetCoefficient((short)id, arg, &first, &second);  /* the encoder passes the cutoff as a 16-bit value */
    pflt_set_coef(f, first, second);
    iirflt_set_coef(f->iflt, first, second);
}

void pflt_set_delay(PredictFilt *f, short h0, short h1)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    f->d0 = h0;
    f->d1 = h1;
}

void pflt_put_sig(PredictFilt *f, int i, short input)
{
    int j;
    int value;
    short output;
    int level;
    unsigned short prev;

    if (i == 0) {
        for (j = 0; j < f->nsmpl; j++) {
            f->rsig[j] = 0;
        }
        f->max = 0;
    }
    if (f != 0) {
        value = input - ((f->k0 * f->d0) >> 12) - ((f->k1 * f->d1) >> 12);
        f->rsig[i] = output = value > 32767 ? 32767 : (value < -32768 ? -32768 : value);
        level = abs(output);
        if (f->max < level) {
            f->max = level;
        }
        prev = f->d0;
        f->d0 = input;
        f->d1 = prev;
    }
}

void pflt_calc_gain(PredictFilt *f)
{
    int scale;
    int n;

    n = (f->max - 1) / 7 + 1;
    scale = (n < AdxGainDataMax) ? n : AdxGainDataMax;
    scale = (scale < 1) ? 1 : scale;
    f->gain = scale;
    if (f->max == 0) {
        f->dgain = 32767.0;
    } else {
        f->dgain = 32767.0 / f->max;
    }
}

short pflt_get_rsig(PredictFilt *f, int i)
{
    short v;

    v = 0;
    if (f != 0) {
        v = f->rsig[i];
    }
    return v;
}

int pflt_get_rsig_q(PredictFilt *f, int i)
{
    int v;

    v = 0;
    if (f != 0) {
        v = f->rsig_q[i];
    }
    return v;
}

void pflt_set_rsig_q(PredictFilt *f, int i, signed char v)
{
    f->rsig_q[i] = v;
}

int adxsje_get_pcm_data(AdxEnc *x, int pos, int n, short **bufs)
{
    SfdSjChunk ck;
    int i;
    int cnt;
    SfdSj **sj;

    sj = x->sji;
    cnt = 0;
    for (i = 0; i < x->nch; i++) {
        cnt = sj[i]->vtbl->getNumData(sj[i], 1) / sizeof(short);
        if (cnt < n) {
            return 0;
        }
    }
    for (i = 0; i < x->nch; i++) {
        for (cnt = 0; cnt < n;) {
            sj[i]->vtbl->getChunk(sj[i], 1, n * 2, &ck);
            memcpy(&bufs[i][cnt], ck.data, ck.len);
            cnt += (short)(ck.len / sizeof(short));
            sj[i]->vtbl->putChunk(sj[i], 0, &ck);
        }
    }
    return cnt;
}

int adxsje_calc_rsig(AdxEnc *e, int ch)
{
    PredictFilt *f;
    IirFilt *pred;
    unsigned short h0;
    unsigned short h1;
    short sample;
    short decoded;
    int level;
    int i;

    f = e->pflt[ch];
    pred = f->iflt;
    pflt_set_delay(f, e->preblk_d0[ch], e->preblk_d1[ch]);
    /* matching construct: variant search — the samples are read as *(e->osig[ch] + i), not e->osig[ch][i]; the row offset then stays a loop invariant of its own in both loops */
    for (i = 0; i < e->nsmpl_blk; i++) {
        pflt_put_sig(f, i, *(e->osig[ch] + i));
    }
    pflt_calc_gain(f);
    iirflt_set_delay(f->iflt, e->preblk_d0[ch], e->preblk_d1[ch]);
    for (i = 0; i < e->nsmpl_blk; i++) {
        sample = *(e->osig[ch] + i);
        iirflt_get_delay(pred, &h0, &h1);
        pflt_set_delay(f, h0, h1);
        pflt_put_sig(f, i, sample);
        level = pflt_get_rsig(f, i) * f->dgain;
        level = (short)(level > 32767 ? 32767 : (level < -32768 ? -32768 : level));
        level = (level < 0 ? level - 2340 : level + 2340) / 4681;
        level = level >= 7 ? 7 : (level < -8 ? -8 : level);
        pflt_set_rsig_q(f, i, level);
        level *= f->gain;
        decoded = level > 32767 ? 32767 : (level < -32768 ? -32768 : level);
        iirflt_put_sig(f->iflt, decoded);
    }
    return 0;
}

/* Quantizes channel ch's block: the filter residuals, scaled to 16 bits, become 4-bit nibbles (4681 = 32768 / 7 per
 * step, rounded half away from zero) packed big-end first into e->sdata[ch]; recon gets the dequantized samples. */
void adxsje_set_rsig(AdxEnc *e, int ch)
{
    int j = 0;
    PredictFilt *f;
    short *resid;
    short *norm;
    short *recon;
    unsigned char *data;
    int per;
    int byte;
    int level;
    int i;
    int nib;

    resid = e->rsig[ch];
    norm = e->rsig_g[ch];
    recon = e->rsig_q[ch];
    data = (unsigned char *)e->sdata[ch];
    per = 8 / e->bps;
    f = e->pflt[ch];
    byte = -1;
    for (i = 0; i < e->nsmpl_blk; i++) {
        resid[i] = pflt_get_rsig(f, i);
        level = resid[i] * f->dgain;
        level = (level > 32767) ? 32767 : ((level < -32768) ? -32768 : level);
        norm[i] = level;
        if (norm[i] < 0) {
            level = (level - 2340) / 4681;
        } else {
            level = (level + 2340) / 4681;
        }
        nib = level >= 7 ? 7 : (level < -8 ? -8 : level);
        level = nib * f->gain * f->dgain;
        level = (level > 32767) ? 32767 : ((level < -32768) ? -32768 : level);
        recon[i] = level;
        if (i % per == 0) {
            byte++;
            data[byte] = 0;
            j = 1;
        }
        nib = ((nib << (8 - e->bps)) & 0xff) >> (8 - e->bps);
        data[byte] |= nib << ((per - j) * e->bps);
        j++;
    }
}

int adxsje_encode_blk(AdxEnc *e)
{
    short *bufs[2];
    unsigned short h0;
    unsigned short h1;
    int n;
    int i;
    int ch;
    PredictFilt *f;
    IirFilt *pred;

    bufs[0] = e->osig[0];
    bufs[1] = e->osig[1];
    n = e->total_nsmpl - e->encpos;
    if (e->nsmpl_blk < n) {
        n = e->nsmpl_blk;
    }
    if (adxsje_get_pcm_data(e, e->encpos, n, bufs) == 0) {
        return 0;
    }
    if (n < e->nsmpl_blk) {
        for (i = 0; i < e->nch; i++) {
            if (bufs[i] != 0) {
                memset(bufs[i] + n, 0, (e->nsmpl_blk - n) * 2);
            }
        }
    }
    e->encpos += e->nsmpl_blk;
    for (ch = 0; ch < e->nch; ch++) {
        adxsje_calc_rsig(e, ch);
        f = e->pflt[ch];
        pred = f->iflt;
        e->gain[ch] = f->gain;
        e->dgain[ch] = f->dgain;
        iirflt_get_delay(pred, &h0, &h1);
        e->preblk_d0[ch] = h0;
        e->preblk_d1[ch] = h1;
        adxsje_set_rsig(e, ch);
    }
    return e->nsmpl_blk;
}

int adxsje_output_sdata(AdxEnc *e)
{
    int *blk;
    SfdSj *sj;
    short s;
    char b;
    int total;
    int i;

    total = 0;
    sj = e->sjo;
    for (i = 0; i < e->nch; i++) {
        s = e->key ^ (e->gain[i] - 1);
        blk = e->sdata[i];
        e->key = (e->key * e->km + e->ka) & 0x7fff;
        if (blk[0] == 0 && blk[1] == 0 && blk[2] == 0 && blk[3] == 0) {
            s = 0;
        }
        b = s >> 8;
        adxsje_write68(&b, 1, 1, sj);
        b = s;
        adxsje_write68(&b, 1, 1, sj);
        adxsje_write68(blk, 1, 16, sj);
        total += 18;
    }
    return total;
}

int adxsje_encode_data(AdxEnc *e)
{
    SfdSj *sj;
    int total;

    total = 0;
    sj = e->sjo;
    do {
        if (sj->vtbl->getNumData(sj, 0) / 18 / e->nch <= 0) {
            break;
        }
        if (adxsje_encode_blk(e) == 0) {
            break;
        }
        total += adxsje_output_sdata(e);
    } while (e->encpos < e->total_nsmpl);
    return total;
}

int adxsje_write_end_code(AdxEnc *e)
{
    int len;
    unsigned short tag;
    char zero;
    int n;
    int i;
    SfdSj *sj;
    int ofst;

    sj = e->sjo;
    ofst = e->total_encdtlen;
    if (e->nloop <= 0) {
        len = e->blklen;
    } else {
        len = (ofst + e->blklen + 2047) / 2048 * 2048 - ofst;
    }
    n = len - 4;
    if (sj->vtbl->getNumData(sj, 0) < len) {
        return 0;
    }
    tag = 0x8001;
    adxsje_write68(&tag, 2, 1, sj);
    tag = n;
    adxsje_write68(&tag, 2, 1, sj);
    zero = 0;
    for (i = 0; i < n; i++) {
        adxsje_write68(&zero, 1, 1, sj);
    }
    return len;
}

/* Writes one item of the header and counts its bytes; a short write abandons the header. */
#define ADXSJE_PUT(p, size, n)                                    \
    if (adxsje_write68((p), (size), (n), sj) != (n)) {            \
        goto err;                                                 \
    }                                                             \
    len += (size) * (n)

/* Writes the ADX header: the fixed part, the loop records, the AINF and CINF chunks, zero padding and the
 * copyright string. Returns its size, or 0 when the output stream has no room or a write falls short. */
int adxsje_output_header(AdxEnc *e, SfdSj *sj)
{
    SfdSjChunk ck;
    int i4;
    unsigned short tag;
    short hdr;
    short i2;
    signed char i1;
    int padlen;
    int crilen;
    int room;
    int len;
    int i;

    crilen = strlen(cri_str);
    sj->vtbl->getChunk(sj, 0, 0x7fffffff, &ck);
    room = ck.len;
    sj->vtbl->ungetChunk(sj, 0, &ck);
    if (room < e->hdinfo_size + 4) {
        return 0;
    }
    tag = 0x8000;
    if (adxsje_write68(&tag, 2, 1, sj) != 1) {
        goto err;
    }
    hdr = e->hdinfo_size;
    if (adxsje_write68(&hdr, 2, 1, sj) != 1) {
        goto err;
    }
    len = 0;
    i1 = e->code;
    ADXSJE_PUT(&i1, 1, 1);
    i1 = e->blklen;
    ADXSJE_PUT(&i1, 1, 1);
    i1 = e->bps;
    ADXSJE_PUT(&i1, 1, 1);
    i1 = e->nch;
    ADXSJE_PUT(&i1, 1, 1);
    i4 = e->sfreq;
    ADXSJE_PUT(&i4, 4, 1);
    i4 = e->encd_nsmpl;
    ADXSJE_PUT(&i4, 4, 1);
    i2 = e->cof;
    ADXSJE_PUT(&i2, 2, 1);
    i1 = 4;
    ADXSJE_PUT(&i1, 1, 1);
    if ((short)e->key == 0) {  /* matching construct: the key is read signed */
        i1 = 0;
    } else {
        i1 = 8;
    }
    ADXSJE_PUT(&i1, 1, 1);
    i4 = 0;
    ADXSJE_PUT(&i4, 4, 1);
    i2 = e->idly0[0];
    ADXSJE_PUT(&i2, 2, 1);
    i2 = e->idly1[0];
    ADXSJE_PUT(&i2, 2, 1);
    i2 = e->idly0[1];
    ADXSJE_PUT(&i2, 2, 1);
    i2 = e->idly1[1];
    ADXSJE_PUT(&i2, 2, 1);
    if (e->nloop > 0) {
        i2 = e->ins_nsmpl;
        ADXSJE_PUT(&i2, 2, 1);
        i2 = e->nloop;
        ADXSJE_PUT(&i2, 2, 1);
        for (i = 0; i < e->nloop; i++) {
            i2 = i;
            ADXSJE_PUT(&i2, 2, 1);
            i2 = 1;
            ADXSJE_PUT(&i2, 2, 1);
            i4 = e->lp_spos;
            ADXSJE_PUT(&i4, 4, 1);
            i4 = e->lp_sofst;
            ADXSJE_PUT(&i4, 4, 1);
            i4 = e->lp_epos;
            ADXSJE_PUT(&i4, 4, 1);
            i4 = e->lp_eofst;
            ADXSJE_PUT(&i4, 4, 1);
        }
    }
    if (e->ainf_flg == 1) {
        if (e->nloop == 0) {
            i4 = 0;
            ADXSJE_PUT(&i4, 4, 1);
        }
        i4 = 0x41494e46;  /* "AINF" */
        ADXSJE_PUT(&i4, 4, 1);
        i4 = 24;
        ADXSJE_PUT(&i4, 4, 1);
        ADXSJE_PUT(e->dataid, 1, 16);
        i2 = e->outvol;
        ADXSJE_PUT(&i2, 2, 1);
        i2 = 0;
        ADXSJE_PUT(&i2, 2, 1);
        i2 = e->outpan[0];
        ADXSJE_PUT(&i2, 2, 1);
        i2 = e->outpan[1];
        ADXSJE_PUT(&i2, 2, 1);
    }
    if (e->cinf_flg == 1) {
        if (e->nloop == 0) {
            i4 = 0;
            ADXSJE_PUT(&i4, 4, 1);
        }
        i4 = 0x43494e46;  /* "CINF" */
        ADXSJE_PUT(&i4, 4, 1);
        i4 = e->cinf_len;
        ADXSJE_PUT(&i4, 4, 1);
        if (e->cinf_len != 0 && e->cinf != 0) {
            ADXSJE_PUT(e->cinf, 1, e->cinf_len);
        }
    }
    i1 = 0;
    padlen = e->hdinfo_size - crilen;
    while (len < padlen) {
        ADXSJE_PUT(&i1, 1, 1);
    }
    ADXSJE_PUT(cri_str, 1, crilen);
    return len + 4;
err:
    return 0;
}

void ADXSJE_Init(void)
{
    ADXKEY_Init();
    memset(adxsje_obj, 0, sizeof(adxsje_obj));
}

void ADXSJE_Finish(void)
{
    ADXKEY_Finish();
    memset(adxsje_obj, 0, sizeof(adxsje_obj));
}

/* Takes a free encoder for nch input streams and one output stream, with the defaults: 4-bit ADX at 44100 Hz
 * in 18-byte blocks, a cutoff of 500 and no loop. */
AdxEnc *ADXSJE_Create(int nch, SfdSj **in, SfdSj *out)
{
    AdxEnc *e;
    int i;
    int j;

    for (i = 0; i < 8; i++) {
        if (adxsje_obj[i].used == 0) {
            break;
        }
    }
    if (i == 8) {
        return 0;
    }
    e = &adxsje_obj[i];
    e->maxnch = nch;
    for (j = 0; j < nch; j++) {
        e->sji[j] = in[j];
    }
    e->sjo = out;
    e->stat = 0;
    e->total_encsmpl = 0;
    e->total_encdtlen = 0;
    e->encpos = 0;
    e->maxencsmpl = 0x7fff0000;
    e->hdinfo_size = ADX_CalcHdrInfoLen(0, 0, 4, 4);
    e->code = 3;
    e->nch = nch;
    e->sfreq = 44100;
    e->bps = 4;
    e->blklen = 18;
    e->nsmpl_blk = (e->blklen - 2) * 8 / e->bps;
    e->encd_nsmpl = 0x7fff0000;
    e->cof = 500;
    e->ins_nsmpl = 0;
    e->nloop = 0;
    e->lp_spos = 0;
    e->lp_sofst = 0;
    e->lp_epos = 0;
    e->lp_eofst = 0;
    e->org_nsmpl = 0;
    e->total_nsmpl = 0;
    e->strm_nsmpl = ((e->encd_nsmpl - 1) / e->nsmpl_blk + 1) * e->nsmpl_blk;
    e->pflt[0] = pflt_create(e->nsmpl_blk);
    e->pflt[1] = pflt_create(e->nsmpl_blk);
    e->idly0[0] = e->idly1[0] = 0;
    e->idly0[1] = e->idly1[1] = 0;
    e->ainf_flg = 0;
    e->outvol = 0;
    e->outpan[0] = -128;
    e->outpan[1] = -128;
    memset(e->dataid, 0, 16);
    e->used = 1;
    return e;
}

/* matching construct: statement-order sweep of the five trailing stores */

void ADXSJE_Destroy(AdxEnc *e)
{
    if (e == 0) {
        return;
    }
    ADXCRS_Lock();
    if (e->pflt[0] != 0) {
        pflt_destroy(e->pflt[0]);
    }
    if (e->pflt[1] != 0) {
        pflt_destroy(e->pflt[1]);
    }
    /* matching construct: hand search — the four status bytes are cleared together, one word store */
    memset(e, 0, 4);
    ADXCRS_Unlock();
}

void ADXSJE_Start(AdxEnc *x)
{
    SfdSjChunk ck;
    int i;
    int len;

    for (i = 0; i < x->nch; i++) {
        len = x->ins_nsmpl * 2;
        if (len > 0) {
            x->sji[i]->vtbl->getChunk(x->sji[i], 0, len, &ck);
            if (ck.len != len) {
                x->sji[i]->vtbl->ungetChunk(x->sji[i], 0, &ck);
                for (;;) {
                }
            }
            memset(ck.data, 0, ck.len);
            x->sji[i]->vtbl->putChunk(x->sji[i], 1, &ck);
        }
    }
    x->total_encsmpl = 0;
    x->total_encdtlen = 0;
    x->encpos = 0;
    x->endflag = 0;
    x->stat = 1;
}

int ADXSJE_GetStat(AdxEnc *e)
{
    return e->stat;
}

void ADXSJE_Stop(AdxEnc *e)
{
    e->endflag = 1;
}

void ADXSJE_SetSfreq(AdxEnc *e, int v)
{
    e->sfreq = v;
}

void ADXSJE_SetHdInfoSize(AdxEnc *e, int v)
{
    e->hdinfo_size = v;
}

void ADXSJE_SetNumChan(AdxEnc *e, int v)
{
    e->nch = v;
}

void ADXSJE_SetOutBps(AdxEnc *e, int v)
{
    e->bps = v;
}

void ADXSJE_SetBlkSmpl(AdxEnc *e, int blklen)
{
    e->nsmpl_blk = blklen;
    if (e->pflt[0] != 0) {
        pflt_destroy(e->pflt[0]);
    }
    e->pflt[0] = pflt_create(e->nsmpl_blk);
    if (e->pflt[1] != 0) {
        pflt_destroy(e->pflt[1]);
    }
    e->pflt[1] = pflt_create(e->nsmpl_blk);
}

void ADXSJE_SetBlkLen(AdxEnc *e, int v)
{
    e->blklen = v;
}

void ADXSJE_SetTotalNumSmpl(AdxEnc *e, int v)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    e->total_nsmpl = v;
    e->encd_nsmpl = v;
}

void ADXSJE_SetCof(AdxEnc *e, int v)
{
    e->cof = v;
}

void ADXSJE_SetNumLoop(AdxEnc *e, int v)
{
    e->nloop = v;
}

void ADXSJE_SetLpInsNsmpl(AdxEnc *e, int v)
{
    e->ins_nsmpl = v;
}

void ADXSJE_SetLpStartPos(AdxEnc *e, int v)
{
    e->lp_spos = v;
}

void ADXSJE_SetLpStartOfst(AdxEnc *e, int v)
{
    e->lp_sofst = v;
}

void ADXSJE_SetLpEndPos(AdxEnc *e, int v)
{
    e->lp_epos = v;
}

void ADXSJE_SetLpEndOfst(AdxEnc *e, int v)
{
    e->lp_eofst = v;
}

void ADXSJE_SetAinfOutputVol(AdxEnc *e, int v)
{
    if (e->ainf_flg != 1) {
        e->ainf_flg = 1;
        e->hdinfo_size += 36;
    }
    e->outvol = v;
}

void ADXSJE_SetAinfOutputPan(AdxEnc *e, int i, int v)
{
    if (e->ainf_flg != 1) {
        e->ainf_flg = 1;
        e->hdinfo_size += 36;
    }
    e->outpan[i] = v;
}

void ADXSJE_SetAinfDataId(AdxEnc *e, const char *name)
{
    if (e->ainf_flg != 1) {
        e->ainf_flg = 1;
        e->hdinfo_size += 36;
    }
    memset(e->dataid, 0, 16);
    strncpy(e->dataid, name, 16);
}

void ADXSJE_ClearAinf(AdxEnc *e)
{
    if (e->ainf_flg == 1) {
        e->ainf_flg = 0;
        e->hdinfo_size += 36;
    }
    e->outvol = 0;
    e->outpan[0] = -128;
    e->outpan[1] = -128;
    memset(e->dataid, 0, 16);
}

void ADXSJE_SetCommonInf(AdxEnc *e, void *cinf, int len)
{
    if (e->cinf_flg != 1) {
        e->cinf_flg = 1;
        e->cinf = cinf;
        e->cinf_len = len;
        e->hdinfo_size += (len + 2047) / 2048 * 2048 + 4;
    }
}

void ADXSJE_SetConfigSfa(AdxEnc *e, int nch, int sfreq, int nsmpl)
{
    /* matching construct: permuter — the no-op a2++/a2-- raises a2's use count so ee-gcc gives it s0 (retail order s0=a2, s1=object, s2=a3) */
    sfreq++;
    sfreq--;
    ADXSJE_SetNumChan(e, nch);
    ADXSJE_SetSfreq(e, sfreq);
    ADXSJE_SetTotalNumSmpl(e, nsmpl);
    ADXSJE_SetHdInfoSize(e, 284);
}

void ADXSJE_SetExtString(AdxEnc *e, const char *text)
{
    unsigned short a, b, c;

    ADXKEY_GenerateKey(text, strlen(text), &a, &b, &c);
    e->key = a;
    e->km = b;
    e->ka = c;
}

int ADXSJE_GetEncDtLen(AdxEnc *e)
{
    return e->total_encdtlen;
}

int ADXSJE_GetEncNumSmpl(AdxEnc *e)
{
    return e->encpos;
}

void ADXSJE_SetEncPos(AdxEnc *e, int v)
{
    e->encpos = v;
}

int ADXSJE_GetEncPos(AdxEnc *e)
{
    return e->encpos;
}

void ADXSJE_SetInSj(AdxEnc *e, unsigned int i, SfdSj *sj)
{
    if (i < 2) {
        e->sji[i] = sj;
    }
}

void ADXSJE_SetOutSj(AdxEnc *e, SfdSj *sj)
{
    e->sjo = sj;
}

void adxsje_encode_prep(AdxEnc *e)
{
    SfdSjChunk ck;
    SfdSj *out;
    int i;
    int n;

    out = e->sjo;
    for (i = 0; i < e->nch; i++) {
        e->sji[i]->vtbl->getChunk(e->sji[i], 1, 2, &ck);
        if (ck.len == 0) {
            break;
        }
        e->idly0[i] = e->idly1[i] = *(short *)ck.data;
        e->sji[i]->vtbl->ungetChunk(e->sji[i], 1, &ck);
    }
    if (i < e->nch) {
        return;
    }
    for (i = 0; i < e->nch; i++) {
        e->preblk_d0[i] = e->idly0[i];
        e->preblk_d1[i] = e->idly1[i];
    }
    n = adxsje_output_header(e, out);
    if (n == 0) {
        return;
    }
    e->total_encdtlen += n;
    for (i = 0; i < e->nch; i++) {
        pflt_calc_coef(e->pflt[i], e->cof, e->sfreq);
    }
    e->stat = 2;
}

void adxsje_encode_exec(AdxEnc *e)
{
    int count;

    /* matching construct: goto — retail re-tests the ended flag after setting it; structured loops reorder the blocks */
loop:
    if (e->endflag == 0) {
        while ((count = adxsje_encode_data(e)) != 0) {
            e->total_encdtlen += count;
            if (e->encpos >= e->total_nsmpl) {
                e->endflag = 1;
                goto loop;
            }
        }
        return;
    }
    if (adxsje_write_end_code(e) > 0) {
        e->stat = 3;
    }
}

void ADXSJE_ExecHndl(AdxEnc *e)
{
    if (e->stat == 1) {
        adxsje_encode_prep(e);
    } else if (e->stat == 2) {
        adxsje_encode_exec(e);
    }
}

void ADXSJE_ExecServer(void)
{
    int i;
    AdxEnc *e;

    e = adxsje_obj;
    i = 7;
    do {
        if (e->used == 1) {
            ADXSJE_ExecHndl(e);
        }
        i -= 1;
        e++;
    } while (i >= 0);
}
