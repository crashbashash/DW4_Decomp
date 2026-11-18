/* CRI SJ (stream joint): the chunk interface every SJ implements, and the SJ modules: the memory
 * (SJMEM), ring-buffer (SJRBF) and chunk-list (SJUNI) joints, their IOP-side counterparts (SJRMT), the
 * EE-IOP join (SJX), the critical section (SJCRS), the error report (SJERR) and the tag utilities. */
#ifndef DW4_CRI_SJ_H
#define DW4_CRI_SJ_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SfdSj SfdSj;

typedef struct SfdSjChunk {
    char *data;
    int len;
} SfdSjChunk;

typedef struct SfdSjVtbl {
    void *queryInterface;                                          /* 0 */
    void *addRef;                                                  /* 4 */
    void *release;                                                 /* 8 */
    void (*destroy)(SfdSj *sj);                                    /* 12 */
    int (*getUuid)(SfdSj *sj);                                     /* 16 */
    void (*reset)(SfdSj *sj);                                      /* 20 */
    void (*getChunk)(SfdSj *sj, int id, int n, SfdSjChunk *ck);    /* 24 */
    void (*ungetChunk)(SfdSj *sj, int id, SfdSjChunk *ck);         /* 28 */
    void (*putChunk)(SfdSj *sj, int id, SfdSjChunk *ck);           /* 32 */
    int (*getNumData)(SfdSj *sj, int id);                          /* 36 */
} SfdSjVtbl;

/* An SJ handle: every joint's object starts with its function table. */
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

/* The lines of a joint: chunks are got from one and put to the other. */
enum SjLine {
    SJ_LIN_FREE = 0,
    SJ_LIN_DATA = 1
};

typedef void (*SjErrFunc)(void *obj, int code);

/* An SJX join; src/cri/sjx.c. */
typedef struct SjxObj SjxObj;

/* sjutl.c */
void SJ_SplitChunk(SfdSjChunk *ck, int nbyte, SfdSjChunk *head, SfdSjChunk *rest);
void SJ_MakeTag(SfdSjChunk *tag, const char *id);
void SJ_GetTagContent(char *tag, SfdSjChunk *content);
char *SJ_SearchTag(SfdSjChunk *ck, const char *id, const char *endid, SfdSjChunk *content);

/* sjcrs.c */
void SJCRS_Init(void);
void SJCRS_Finish(void);
void SJCRS_BeginSvr(void);
void SJCRS_EndSvr(void);
void SJCRS_Lock(void);
void SJCRS_Unlock(void);

/* sjerr.c */
void SJERR_CallErr(const char *message);

/* sjmem.c */
void SJMEM_Init(void);
void SJMEM_Finish(void);
SfdSj *SJMEM_Create(char *buf, int bsize);
char *SJMEM_GetBufPtr(SfdSj *sj);
int SJMEM_GetBufSize(SfdSj *sj);

/* sjrbf.c */
void SJRBF_Init(void);
void SJRBF_Finish(void);
SfdSj *SJRBF_Create(char *buf, int bsize, int xsize);
char *SJRBF_GetBufPtr(SfdSj *sj);
int SJRBF_GetBufSize(SfdSj *sj);
int SJRBF_GetXtrSize(SfdSj *sj);
void SJRBF_SetFlowCnt(SfdSj *sj, int line, int flow, int cnt);
int SJRBF_GetFlowCnt(SfdSj *sj, int line, int flow);

/* sjuni.c */
void SJUNI_Init(void);
void SJUNI_Finish(void);
SfdSj *SJUNI_Create(int mode, char *work, int wksize);

/* sjrmt.c: a remote handle is the IOP-side joint's address. */
void *SJRBF_CreateRmt(int buf, int bsize, int xsize);
void *SJMEM_CreateRmt(int buf, int bsize);
void *SJUNI_CreateRmt(int mode, int work, int wksize);
void SJRMT_Destroy(void *sjrmt);
int *SJRMT_GetUuid(void *sjrmt);
void SJRMT_Reset(void *sjrmt);
void SJRMT_GetChunk(void *sjrmt, int line, int nbyte, SfdSjChunk *ck);
void SJRMT_UngetChunk(void *sjrmt, int line, SfdSjChunk *ck);
int SJRMT_PutChunk(void *sjrmt, int line, SfdSjChunk *ck);
int SJRMT_GetNumData(void *sjrmt, int line);
int SJRMT_IsGetChunk(void *sjrmt, int line, int nbyte, int *rbyte);
void SJRMT_Init(void);
void SJRMT_Finish(void);

/* sjx.c */
void SJX_ExecServer(void);
void SJX_Init(void);
void SJX_Finish(void);
SjxObj *SJX_Create(SfdSj *sj, void *sjrmt, int line);
void SJX_Destroy(SjxObj *sjx);
void SJX_Reset(SjxObj *sjx);

#ifdef __cplusplus
}
#endif

#endif
