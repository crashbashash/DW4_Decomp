/* CRI PL2ENC: the Dolby Pro Logic II encoder that spreads a mono voice over a stereo pair. */
#ifndef DW4_CRI_PL2ENC_H
#define DW4_CRI_PL2ENC_H

#define PL2ENC_MAX_DELAY 96     /* words in each surround delay line */
#define PL2ENC_BLK_SMPL 32      /* samples PL2ENC_ExecOneBlk encodes */

typedef struct Pl2Enc {
    void *work;         /* 0x00: the caller's work area */
    int wksize;         /* 0x04 */
    int *dly_l;         /* 0x08: surround delay lines, PL2ENC_MAX_DELAY words each */
    int *dly_r;         /* 0x0c */
    int sfreq;          /* 0x10 */
    int dly_pos;        /* 0x14 */
    int dly_len;        /* 0x18: one sample per 750 Hz of sfreq */
    int gain_l;         /* 0x1c: indices into pl2enc_gain_tbl, 0 to 254 */
    int gain_r;         /* 0x20 */
    int gain_c;         /* 0x24: front */
    int gain_s;         /* 0x28: surround */
} Pl2Enc;

typedef void (*Pl2EncErrFunc)(void *obj, const char *message);

void PL2ENC_EntryErrFunc(Pl2EncErrFunc func, void *obj);
void PL2ENC_Init(int reserved);
void PL2ENC_Finish(int reserved);
Pl2Enc *PL2ENC_Create(void *work, int wksize);
void PL2ENC_Destroy(Pl2Enc *pl2);
void PL2ENC_Reset(Pl2Enc *pl2);
void PL2ENC_ExecOneSmpl(Pl2Enc *pl2, short in, short *out_l, short *out_r);
void PL2ENC_ExecOneBlk(Pl2Enc *pl2, short *in, short *out_l, short *out_r);
void PL2ENC_SetPos(Pl2Enc *pl2, int x, int y);
void PL2ENC_SetSfreq(Pl2Enc *pl2, int sfreq);

#endif
