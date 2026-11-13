/* CRI PL2ENC: the Dolby Pro Logic II encoder. One mono sample becomes a left/right pair whose front
 * part follows the position's pan and whose surround part goes out of phase through a short delay. */
#include "dw4/cri/pl2enc.h"

void SVM_Lock(void);
void SVM_Unlock(void);
void *memset(void *dst, int value, unsigned int size);

extern int pl2enc_init_cnt;
extern Pl2EncErrFunc pl2enc_err_func;
extern void *pl2enc_err_obj;
extern int pl2enc_gain_tbl[];   /* 4.12 fixed point, by gain index */
extern char E03090306_NULL_pointer_is_specified[];
extern char E03090307_Illegal_parameter_is_specified[];
extern char E03091601_NULL_pointer_is_specified[];
extern char E03091602_Illegal_parameter_is_specified[];

void pl2enc_Reset(Pl2Enc *pl2);

#define PL2ENC_POS_MAX 127

/* the surround matrix, 4.12 fixed point */
#define PL2ENC_SURR_MAIN 3567
#define PL2ENC_SURR_CROSS 2006

void pl2enc_Lock(void)
{
    SVM_Lock();
}

void pl2enc_Unlock(void)
{
    SVM_Unlock();
}

void pl2enc_EntryErrFunc(Pl2EncErrFunc func, void *obj);

void PL2ENC_EntryErrFunc(Pl2EncErrFunc func, void *obj)
{
    pl2enc_Lock();
    pl2enc_EntryErrFunc(func, obj);
    pl2enc_Unlock();
}

void pl2enc_EntryErrFunc(Pl2EncErrFunc func, void *obj)
{
    pl2enc_err_func = func;
    pl2enc_err_obj = obj;
}

void pl2enc_CallErr(const char *message)
{
    if (pl2enc_err_func != 0) {
        pl2enc_err_func(pl2enc_err_obj, message);
    }
}

void pl2enc_Init(int reserved);

void PL2ENC_Init(int reserved)
{
    pl2enc_Lock();
    pl2enc_Init(reserved);
    pl2enc_Unlock();
}

void pl2enc_Init(int reserved);

void pl2enc_Finish(int reserved);

void PL2ENC_Finish(int reserved)
{
    pl2enc_Lock();
    pl2enc_Finish(reserved);
    pl2enc_Unlock();
}

void pl2enc_Finish(int reserved)
{
    pl2enc_init_cnt--;
}

Pl2Enc *pl2enc_Create(void *work, int wksize);

Pl2Enc *PL2ENC_Create(void *work, int wksize)
{
    Pl2Enc *pl2;

    pl2enc_Lock();
    pl2 = pl2enc_Create(work, wksize);
    pl2enc_Unlock();
    return pl2;
}

void pl2enc_Destroy(Pl2Enc *pl2);

void PL2ENC_Destroy(Pl2Enc *pl2)
{
    pl2enc_Lock();
    pl2enc_Destroy(pl2);
    pl2enc_Unlock();
}

void pl2enc_Destroy(Pl2Enc *pl2)
{
    memset(pl2, 0, sizeof(*pl2));
}

void PL2ENC_Reset(Pl2Enc *pl2)
{
    pl2enc_Lock();
    pl2enc_Reset(pl2);
    pl2enc_Unlock();
}

void pl2enc_Reset(Pl2Enc *pl2)
{
    int i;

    for (i = 0; i < PL2ENC_MAX_DELAY; i++) {
        pl2->dly_l[i] = 0;
        pl2->dly_r[i] = 0;
    }
    pl2->dly_pos = 0;
    pl2->dly_len = 64;
}

void pl2enc_ExecOneSmpl(Pl2Enc *pl2, short in, short *out_l, short *out_r);

void PL2ENC_ExecOneSmpl(Pl2Enc *pl2, short in, short *out_l, short *out_r)
{
    pl2enc_Lock();
    pl2enc_ExecOneSmpl(pl2, in, out_l, out_r);
    pl2enc_Unlock();
}

void pl2enc_ExecOneSmpl(Pl2Enc *pl2, short in, short *out_l, short *out_r)
{
    int s, l, r, ls, rs, c, ol, or;

    s = pl2enc_gain_tbl[pl2->gain_s];
    l = (in * pl2enc_gain_tbl[pl2->gain_l]) >> 12;
    r = (in * pl2enc_gain_tbl[pl2->gain_r]) >> 12;
    ls = (l * s) >> 12;
    rs = (r * s) >> 12;
    c = pl2enc_gain_tbl[pl2->gain_c];
    ol = ((l * c) >> 12) + pl2->dly_l[pl2->dly_pos];
    or = ((r * c) >> 12) + pl2->dly_r[pl2->dly_pos];
    if (ol > 32767) {
        ol = 32767;
    } else if (ol < -32768) {
        ol = -32768;
    }
    if (or > 32767) {
        or = 32767;
    } else if (or < -32768) {
        or = -32768;
    }
    pl2->dly_l[pl2->dly_pos] = (ls * -PL2ENC_SURR_MAIN + rs * -PL2ENC_SURR_CROSS) >> 12;
    *out_l = ol;
    pl2->dly_r[pl2->dly_pos] = (rs * PL2ENC_SURR_MAIN + ls * PL2ENC_SURR_CROSS) >> 12;
    *out_r = or;
    pl2->dly_pos++;
    if (pl2->dly_pos >= pl2->dly_len) {
        pl2->dly_pos = 0;
    }
}

void pl2enc_ExecOneBlk(Pl2Enc *pl2, short *in, short *out_l, short *out_r);

void PL2ENC_ExecOneBlk(Pl2Enc *pl2, short *in, short *out_l, short *out_r)
{
    pl2enc_Lock();
    pl2enc_ExecOneBlk(pl2, in, out_l, out_r);
    pl2enc_Unlock();
}

/* The block form reads the delay lines from their start and does not move dly_pos. */
void pl2enc_ExecOneBlk(Pl2Enc *pl2, short *in, short *out_l, short *out_r)
{
    int i, s, l, r, ls, rs, c, ol, or;
    int *dl;
    int *dr;

    dr = pl2->dly_r;
    dl = pl2->dly_l;
    for (i = 0; i < PL2ENC_BLK_SMPL; i++) {
        s = pl2enc_gain_tbl[pl2->gain_s];
        l = (in[i] * pl2enc_gain_tbl[pl2->gain_l]) >> 12;
        r = (in[i] * pl2enc_gain_tbl[pl2->gain_r]) >> 12;
        ls = (l * s) >> 12;
        rs = (r * s) >> 12;
        c = pl2enc_gain_tbl[pl2->gain_c];
        ol = ((l * c) >> 12) + *dl;
        or = ((r * c) >> 12) + *dr;
        if (ol > 32767) {
            ol = 32767;
        } else if (ol < -32768) {
            ol = -32768;
        }
        if (or > 32767) {
            or = 32767;
        } else if (or < -32768) {
            or = -32768;
        }
        *dl = (ls * -PL2ENC_SURR_MAIN + rs * -PL2ENC_SURR_CROSS) >> 12;
        out_l[i] = ol;
        dl++;
        *dr = (rs * PL2ENC_SURR_MAIN + ls * PL2ENC_SURR_CROSS) >> 12;
        dr++;
        out_r[i] = or;
    }
}

void pl2enc_SetPos(Pl2Enc *pl2, int x, int y);

void PL2ENC_SetPos(Pl2Enc *pl2, int x, int y)
{
    pl2enc_Lock();
    pl2enc_SetPos(pl2, x, y);
    pl2enc_Unlock();
}

#define ABS(x) ((x) < 0 ? -(x) : (x))

void pl2enc_SetPos(Pl2Enc *pl2, int x, int y)
{
    if (pl2 == 0) {
        pl2enc_CallErr(E03090306_NULL_pointer_is_specified);
        return;
    }
    if (x < -PL2ENC_POS_MAX || x > PL2ENC_POS_MAX || y < -PL2ENC_POS_MAX || y > PL2ENC_POS_MAX) {
        pl2enc_CallErr(E03090307_Illegal_parameter_is_specified);
        return;
    }
    pl2->gain_l = ABS(x + PL2ENC_POS_MAX);
    pl2->gain_r = ABS(x - PL2ENC_POS_MAX);
    pl2->gain_c = ABS(y + PL2ENC_POS_MAX);
    pl2->gain_s = ABS(y - PL2ENC_POS_MAX);
}

void pl2enc_SetSfreq(Pl2Enc *pl2, int sfreq);

void PL2ENC_SetSfreq(Pl2Enc *pl2, int sfreq)
{
    pl2enc_Lock();
    pl2enc_SetSfreq(pl2, sfreq);
    pl2enc_Unlock();
}

void pl2enc_SetSfreq(Pl2Enc *pl2, int sfreq)
{
    int len;

    if (pl2 == 0) {
        pl2enc_CallErr(E03091601_NULL_pointer_is_specified);
        return;
    }
    if (sfreq <= 0) {
        pl2enc_CallErr(E03091602_Illegal_parameter_is_specified);
        return;
    }
    len = sfreq / 750;
    pl2->sfreq = sfreq;
    if (len > PL2ENC_MAX_DELAY) {
        len = PL2ENC_MAX_DELAY;
    } else if (len < 1) {
        len = 1;
    }
    pl2->dly_len = len;
}
