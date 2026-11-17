/* CRI ADX header and block decoding: the ADX header fields, the prediction coefficients and the 4-bit
 * ADPCM block decoders; src/cri/adxdcd.c. */
#ifndef DW4_CRI_ADXDCD_H
#define DW4_CRI_ADXDCD_H

#ifdef __cplusplus
extern "C" {
#endif

void ADX_GetCoefficient(int cutoff, int sfreq, short *k0, short *k1);
int ADX_ScanInfoCode(unsigned char *buf, int size, short *pos);
int ADX_IsAdxFmt(unsigned char *hdr, int size, short *ofst);
int ADX_DecodeInfo(unsigned char *hdr, int len, short *ofst, signed char *type, signed char *bsize, signed char *bits,
                   signed char *nch, int *sfreq, int *nsmpl, int *blksmpl);
int ADX_DecodeInfoExADPCM2(unsigned char *hdr, int size, short *out);
int ADX_DecodeInfoExVer(unsigned char *hdr, int size, unsigned char *ver, unsigned char *flag);
int ADX_DecodeInfoExIdly(unsigned char *hdr, int size, unsigned short *start, unsigned short *end);
int ADX_DecodeInfoExLoop(unsigned char *hdr, int size, int *lptype, short *nloop, short *lpflg, int *lpstart,
                         int *lpstartofst, int *lpend, int *lpendofst);
int ADX_DecodeInfoAinf(unsigned char *hdr, int size, int *ainfsiz, char *ainf, short *volume, short *pan);
int ADX_DecodeFooter(unsigned char *hdr, int size, short *ofst);
int ADX_CalcHdrInfoLen(int type, int len, int ofst, unsigned int blk);
int ADX_DecodeMono4(unsigned char *ibuf, int nblk, short *obuf, short *dly, short k0, short k1, unsigned short *seed,
                    short mul, short add);
int ADX_DecodeSte4AsMono(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr, short k0,
                         short k1, unsigned short *seed, short mul, short add);
int ADX_DecodeSte4AsSte(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr, short k0,
                        short k1, unsigned short *seed, short mul, short add);
int ADX_DecodeSte4(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr, short *dlyr, short k0,
                   short k1, unsigned short *seed, short mul, short add);

#ifdef __cplusplus
}
#endif

#endif
