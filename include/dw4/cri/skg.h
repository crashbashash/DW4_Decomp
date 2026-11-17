/* CRI SKG: the three 16-bit ADX decryption keys derived from a key string, and the SKG error callback;
 * src/cri/skg.c. */
#ifndef DW4_CRI_SKG_H
#define DW4_CRI_SKG_H

#ifdef __cplusplus
extern "C" {
#endif

/* The SKG table: entries 256, 512 and 768 start the three keys, entries 128 + c weigh character c. */
#define SKG_TBL_NUM 1024

typedef void (*SkgErrFunc)(void *obj, int arg);

extern const short skg_tbl[SKG_TBL_NUM];

int SKG_NopFunc(void);
int SKG_EntryErrFunc(SkgErrFunc func, void *obj);
int SKG_CallErrFunc(int arg);
int SKG_Init(void);
int SKG_Finish(void);
int SKG_GenerateKey(const char *str, int len, unsigned short *k0, unsigned short *k1, unsigned short *k2);
int SKG_GetDefKey(unsigned short *k0, unsigned short *k1, unsigned short *k2);
int SKG_GetNextKey(unsigned short *seed, unsigned short *mul, unsigned short *add);

#ifdef __cplusplus
}
#endif

#endif
