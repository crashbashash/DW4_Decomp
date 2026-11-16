#include "dw4/cri/adxt.h"

typedef struct CriSjChunk {
    void *ptr;
    int len;
} CriSjChunk;

typedef struct Sj Sj;
typedef struct SjVtbl {
    void *pad0[3];
    void (*destroy)(Sj *sj);
    void *pad16[2];
    void (*get_chunk)(Sj *sj, int id, int nbyte, CriSjChunk *ck);
    void (*unget_chunk)(Sj *sj, int id, CriSjChunk *ck);
    void (*put_chunk)(Sj *sj, int id, CriSjChunk *ck);
} SjVtbl;
struct Sj {
    SjVtbl *vt;
};

typedef struct AdxEnc AdxEnc;

typedef struct AdxtObject {
    char pad0[20];
    Sj *sji;
} AdxtObject;

int adxt_init_cnt = 0;
int adxt_init_reserved = 0; /* no function reads it */
int adxt_svr_id = 0;
int adxt_thrd_svr_sw = 1;
int adxt_output_mono = 0;
int adxt_fssvr_id = 0;
int adxt_vsync_cnt = 0;
AdxtObj adxt_obj[ADXT_MAX_OBJ] = {0};
char adxt_enc_ibuf[1024] = {0};
char adxt_enc_obuf[64] = {0};
static char *volatile adxt_build_ref;
extern int DAT_004a9b1c;

void ADXERR_CallErrFunc1(const char *message);
int ADXT_ExecServer();
int ADXT_ExecFsSvr();
int LSC_ExecServer();
void *memcpy(void *dst, const void *src, unsigned int n);
void ADXT_Init(void);
void ADXT_DestroyAll(void);
void ADXRNA_Finish(void);
void FUN_00260b30(void);
void ADXSTM_Finish(void);
void LSC_Finish(void);
void ADXCRS_Lock(void);
void SVM_DelCbSvr(int key, int value);
void SVM_Finish(void);
void ADXSJD_Finish(void);
void ADXERR_Finish(void);
void SJMEM_Finish(void);
void SJRBF_Finish(void);
void SJUNI_Finish(void);
void ADXCRS_Unlock(void);
void ADXSJE_Init(void);
void ADXSJE_Finish(void);
AdxEnc *ADXSJE_Create(int nch, Sj **out, Sj *in);
void ADXSJE_SetConfigSfa(AdxEnc *enc, int nch, int f92, int end);
void ADXSJE_Start(AdxEnc *enc);
void ADXSJE_ExecServer(void);
void ADXSJE_Stop(AdxEnc *enc);
void ADXSJE_Destroy(AdxEnc *enc);
Sj *SJRBF_Create(void *buf, int size, int f8);
Sj *SJMEM_Create(void *buf, int size);

void *memset(void *dst, int value, unsigned int size);
int ADXCRS_Init();
int SJUNI_Init();
int SJRBF_Init();
int SJMEM_Init();
int ADXERR_Init();
int ADXSTM_Init();
int ADXSJD_Init();
int FUN_00260a60();
int ADXRNA_Init();
int LSC_Init();
int SVM_Init();
int ADXRNA_EntryErrFunc();
int LSC_EntryErrFunc();
int ADXM_IsSetupThrd();
int SVM_SetCbSvrId();
int SVM_SetCbSvr();
int ADXT_SetDefSvrFreq();
void ADXT_ConfigVsyncSvr(int value) {
    adxt_thrd_svr_sw = value;
}

void adxini_rnaerr_cbfn(void *unused, const char *message) {
    ADXERR_CallErrFunc1(message);
}

void adxini_lscerr_cbfn(void *unused, const char *message) {
    ADXERR_CallErrFunc1(message);
}

void ADXT_VsyncProc(void) {
    adxt_vsync_cnt += 1;
    ADXT_ExecServer();
}

int adxt_exec_main_thrd(void *arg) {
    LSC_ExecServer();
    return 0;
}

int adxt_exec_tsvr(void *arg);
int adxt_exec_fssvr(void *arg);

int adxt_exec_main_nothrd(void *arg) {
    adxt_exec_tsvr(0);
    adxt_exec_fssvr(0);
    adxt_exec_main_thrd(0);
    return 0;
}

int adxt_exec_tsvr(void *arg) {
    ADXT_ExecServer();
    return 0;
}

int adxt_exec_fssvr(void *arg) {
    ADXT_ExecFsSvr();
    return 0;
}

void ADXT_Init(void)
{
    adxt_build_ref = "\nADXT/PS2EE Ver.9.31s281 Build:Oct  6 2004 11:47:30\n";
    if (adxt_init_cnt == 0) {
        ADXCRS_Init();
        ADXCRS_Lock();
        SJUNI_Init();
        SJRBF_Init();
        SJMEM_Init();
        ADXERR_Init();
        ADXSTM_Init();
        ADXSJD_Init();
        FUN_00260a60();
        ADXRNA_Init();
        LSC_Init();
        SVM_Init();
        ADXRNA_EntryErrFunc(adxini_rnaerr_cbfn, 0);
        LSC_EntryErrFunc(adxini_lscerr_cbfn, 0);
        memset(adxt_obj, 0, sizeof(adxt_obj));
        if (ADXM_IsSetupThrd() == 1 && adxt_thrd_svr_sw == 1) {
            SVM_SetCbSvrId(2, 1, adxt_exec_tsvr, 0);
            adxt_fssvr_id = SVM_SetCbSvr(4, adxt_exec_fssvr, 0);
            adxt_svr_id = SVM_SetCbSvr(5, adxt_exec_main_thrd, 0);
        } else {
            adxt_svr_id = SVM_SetCbSvr(5, adxt_exec_main_nothrd, 0);
        }
        *(volatile int *)&adxt_vsync_cnt = 0;
        adxt_output_mono = 0;
        ADXT_SetDefSvrFreq(60);
        ADXCRS_Unlock();
    }
    adxt_init_cnt++;
}

void ADXT_ResetLibrary(void) {
    adxt_init_cnt = 0;
    ADXT_Init();
}

void ADXT_Finish(void) {
    if (--adxt_init_cnt == 0) {
        DAT_004a9b1c = 0;
        ADXT_DestroyAll();
        ADXRNA_Finish();
        FUN_00260b30();
        ADXSTM_Finish();
        LSC_Finish();
        ADXCRS_Lock();
        SVM_DelCbSvr(2, 1);
        SVM_DelCbSvr(4, adxt_fssvr_id);
        SVM_DelCbSvr(5, adxt_svr_id);
        SVM_Finish();
        ADXSJD_Finish();
        ADXERR_Finish();
        SJMEM_Finish();
        SJRBF_Finish();
        SJUNI_Finish();
        ADXCRS_Unlock();
        DAT_004a9b1c = 1;
    }
}

void FUN_00263548(AdxtObject *adxt, int nch, int f92, int end)
{
    Sj *out[2];
    CriSjChunk ckIn;
    CriSjChunk ckOut;
    Sj *in;
    Sj *dst;
    AdxEnc *enc;
    ADXSJE_Init();
    in = SJRBF_Create(adxt_enc_ibuf, 1024, 0);
    out[0] = SJMEM_Create(adxt_enc_obuf, 32);
    out[1] = SJMEM_Create(adxt_enc_obuf + 32, 32);
    dst = adxt->sji;
    enc = ADXSJE_Create(2, out, in);
    ADXSJE_SetConfigSfa(enc, nch, f92, end);
    ADXSJE_Start(enc);
    ADXSJE_ExecServer();
    in->vt->get_chunk(in, 1, 1024, &ckIn);
    if (ckIn.len == 0) {
        for (;;) {
        }
    }
    dst->vt->get_chunk(dst, 0, ckIn.len, &ckOut);
    if (ckOut.len < ckIn.len) {
        for (;;) {
        }
    }
    memcpy(ckOut.ptr, ckIn.ptr, ckIn.len);
    in->vt->put_chunk(in, 0, &ckIn);
    dst->vt->put_chunk(dst, 1, &ckOut);
    ADXSJE_Stop(enc);
    ADXSJE_Destroy(enc);
    in->vt->destroy(in);
    out[1]->vt->destroy(out[1]);
    out[0]->vt->destroy(out[0]);
    ADXSJE_Finish();
}
