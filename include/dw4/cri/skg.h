/* CRI SKG: the three 16-bit ADX decryption keys derived from a key string, and the ADXKEY callback;
 * src/cri/skg.c. */
#ifndef DW4_CRI_SKG_H
#define DW4_CRI_SKG_H

#ifdef __cplusplus
extern "C" {
#endif

/* The SKG table: entries 256, 512 and 768 start the three keys, entries 128 + c weigh character c. */
#define SKG_TBL_NUM 1024

typedef void (*AdxKeyCbFunc)(void *obj, int arg);

extern const short skg_tbl[SKG_TBL_NUM];

int ADXKEY_Nop(void);
int ADXKEY_EntryCbFunc(AdxKeyCbFunc func, void *obj);
int ADXKEY_ExecCbFunc(int arg);
int SKG_Init(void);
int SKG_Finish(void);
int SKG_GenerateKey(const char *str, int len, unsigned short *k0, unsigned short *k1, unsigned short *k2);
int SKG_GetDefKey(unsigned short *k0, unsigned short *k1, unsigned short *k2);
int ADXKEY_NextSeed(unsigned short *seed, unsigned short *mul, unsigned short *add);

#ifdef __cplusplus
}
#endif

#endif
