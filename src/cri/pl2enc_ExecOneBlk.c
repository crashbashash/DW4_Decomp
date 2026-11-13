/* Dolby Pro Logic II encoder state. */
typedef struct Pl2Enc {
    void *work;      /* 0x00 */
    int worksize;    /* 0x04 */
    int *delay_l;    /* 0x08 */
    int *delay_r;    /* 0x0c */
    int pad16;       /* 0x10 */
    int pos;         /* 0x14 */
    int len;         /* 0x18 */
    int gain_l;      /* 0x1c */
    int gain_r;      /* 0x20 */
    int gain_c;      /* 0x24 */
    int gain_s;      /* 0x28 */
} Pl2Enc;

extern int pl2enc_gain_tbl[];  /* 4.12 fixed-point gains, indexed by gain step */

void pl2enc_ExecOneBlk(Pl2Enc *pl2, short *in, short *out_l, short *out_r) {
    int i, s, l, r, ls, rs, c, ol, or;
    int *dl;
    int *dr;

    dr = pl2->delay_r;
    dl = pl2->delay_l;
    for (i = 0; i < 32; i++) {
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
        *dl = (ls * -3567 + rs * -2006) >> 12;
        out_l[i] = ol;
        dl++;
        *dr = (rs * 3567 + ls * 2006) >> 12;
        dr++;
        out_r[i] = or;
    }
}
