/* CRI SKG (SKG/PS2EE Ver.0.64): derives the three 16-bit ADX decryption keys from a key string, and the
 * ADXKEY entry points around it: a key callback the application registers, and one step of the key's seed. */

typedef void (*AdxKeyCbFunc)(void *obj, int arg);

/* The 1024-entry SKG table: entries 256, 512 and 768 start the three keys, entries 128 + c weigh character c. */
#define SKG_TBL_NUM 1024

extern AdxKeyCbFunc adxkey_cbfunc;
extern void *adxkey_cbobj;
extern int skg_init_cnt;
extern const short skg_tbl[SKG_TBL_NUM];
/* "CRI-MW", the middleware's default key string */
extern const signed char skg_def_key[];

int ADXKEY_Nop(void)
{
    return 0;
}

int ADXKEY_EntryCbFunc(AdxKeyCbFunc func, void *obj)
{
    adxkey_cbfunc = func;
    adxkey_cbobj = obj;
    return 0;
}

int ADXKEY_ExecCbFunc(int arg)
{
    if (adxkey_cbfunc != 0) {
        adxkey_cbfunc(adxkey_cbobj, arg);
    }
    return 0;
}

int SKG_Init(void)
{
    skg_init_cnt++;
    return 0;
}

int SKG_Finish(void)
{
    skg_init_cnt--;
    return 0;
}

int SKG_GenerateKey(const signed char *str, int len, short *k0, short *k1, short *k2)
{
    int i;
    short key0;
    short key1;
    short key2;

    if (skg_init_cnt == 0) {
        SKG_Init();
    }
    *k0 = 0;
    *k1 = 0;
    *k2 = 0;
    if (str == 0 && len <= 0) {
        return 0;
    }
    key0 = skg_tbl[256];
    for (i = 0; i < len; i++) {
        key0 = skg_tbl[key0 * skg_tbl[128 + str[i]] % SKG_TBL_NUM];
    }
    key1 = skg_tbl[512];
    for (i = 0; i < len; i++) {
        key1 = skg_tbl[key1 * skg_tbl[128 + str[i]] % SKG_TBL_NUM];
    }
    key2 = skg_tbl[768];
    for (i = 0; i < len; i++) {
        key2 = skg_tbl[key2 * skg_tbl[128 + str[i]] % SKG_TBL_NUM];
    }
    *k0 = key0;
    *k1 = key1;
    *k2 = key2;
    return 0;
}

/* The keys of the default key string "CRI-MW". */
int SKG_GetDefKey(short *k0, short *k1, short *k2)
{
    if (skg_init_cnt == 0) {
        SKG_Init();
    }
    SKG_GenerateKey(skg_def_key, 6, k0, k1, k2);
    return 0;
}

/* One step of the ADX key generator: seed = seed * mul + add, 16 bits. */
int ADXKEY_NextSeed(unsigned short *seed, unsigned short *mul, unsigned short *add)
{
    *seed = *add + (*seed * *mul);
    return 0;
}
