#ifndef SFDSJ_H
#define SFDSJ_H

typedef struct SfdSj SfdSj;

typedef struct SfdSjChunk {
    char *data;
    int len;
} SfdSjChunk;

typedef struct SfdSjVtbl {
    void *f0;
    void *f4;
    void *f8;
    void (*destroy)(SfdSj *sj);                                    /* 12 */
    int (*getUuid)(SfdSj *sj);                                     /* 16 */
    void (*reset)(SfdSj *sj);                                      /* 20 */
    void (*getChunk)(SfdSj *sj, int id, int n, SfdSjChunk *ck);    /* 24 */
    void (*ungetChunk)(SfdSj *sj, int id, SfdSjChunk *ck);         /* 28 */
    void (*putChunk)(SfdSj *sj, int id, SfdSjChunk *ck);           /* 32 */
    int (*getNumData)(SfdSj *sj, int id);                          /* 36 */
} SfdSjVtbl;

struct SfdSj {
    SfdSjVtbl *vtbl;
};

typedef struct SfdBufStat {
    SfdSjChunk ck0;  /* 0 */
    SfdSjChunk ck1;  /* 8 */
    char *tailData;
    int tailLen;
    int tailFlag;
    int pad28;
} SfdBufStat;

#endif
