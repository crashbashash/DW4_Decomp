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
void FUN_00265c18(void);
void FUN_00260b30(void);
void ADXSTM_Finish(void);
void LSC_Finish(void);
void ADXCRS_Lock(void);
void SVM_DelCbSvr(int key, int value);
void SVM_Finish(void);
void FUN_00265f88(void);
void FUN_00260788(void);
void SJMEM_Finish(void);
void SJRBF_Finish(void);
void SJUNI_Finish(void);
void ADXCRS_Unlock(void);
void FUN_00269268(void);
void FUN_00269298(void);
AdxEnc *FUN_002692c8(int nch, Sj **out, Sj *in);
void FUN_00269878(AdxEnc *enc, int nch, int f92, int end);
void FUN_00269508(AdxEnc *enc);
void FUN_00269bd0(void);
void ADXENC_SetEnd(AdxEnc *enc);
void FUN_00269498(AdxEnc *enc);
Sj *SJRBF_Create(void *buf, int size, int f8);
Sj *SJMEM_Create(void *buf, int size);

void *memset(void *dst, int value, unsigned int size);
int ADXCRS_Init();
int SJUNI_Init();
int SJRBF_Init();
int SJMEM_Init();
int FUN_00260750();
int ADXSTM_Init();
int FUN_00265f58();
int FUN_00260a60();
int FUN_00265c00();
int LSC_Init();
int SVM_Init();
int FUN_00265c30();
int LSC_EntryErrFunc();
int ADXM_IsSetupThrd();
int SVM_SetCbSvrId();
int SVM_SetCbSvr();
int ADXT_SetDefSvrFreq();
void FUN_002631c8(int value) {
    adxt_thrd_svr_sw = value;
}

void FUN_002631d8(void *unused, const char *message) {
    ADXERR_CallErrFunc1(message);
}

void FUN_002631f0(void *unused, const char *message) {
    ADXERR_CallErrFunc1(message);
}

void FUN_00263208(void) {
    adxt_vsync_cnt += 1;
    ADXT_ExecServer();
}

int FUN_00263230(void *arg) {
    LSC_ExecServer();
    return 0;
}

int FUN_00263280(void *arg);
int FUN_002632a0(void *arg);

int FUN_00263250(void *arg) {
    FUN_00263280(0);
    FUN_002632a0(0);
    FUN_00263230(0);
    return 0;
}

int FUN_00263280(void *arg) {
    ADXT_ExecServer();
    return 0;
}

int FUN_002632a0(void *arg) {
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
        FUN_00260750();
        ADXSTM_Init();
        FUN_00265f58();
        FUN_00260a60();
        FUN_00265c00();
        LSC_Init();
        SVM_Init();
        FUN_00265c30(FUN_002631d8, 0);
        LSC_EntryErrFunc(FUN_002631f0, 0);
        memset(adxt_obj, 0, sizeof(adxt_obj));
        if (ADXM_IsSetupThrd() == 1 && adxt_thrd_svr_sw == 1) {
            SVM_SetCbSvrId(2, 1, FUN_00263280, 0);
            adxt_fssvr_id = SVM_SetCbSvr(4, FUN_002632a0, 0);
            adxt_svr_id = SVM_SetCbSvr(5, FUN_00263230, 0);
        } else {
            adxt_svr_id = SVM_SetCbSvr(5, FUN_00263250, 0);
        }
        *(volatile int *)&adxt_vsync_cnt = 0;
        adxt_output_mono = 0;
        ADXT_SetDefSvrFreq(60);
        ADXCRS_Unlock();
    }
    adxt_init_cnt++;
}

void FUN_00263450(void) {
    adxt_init_cnt = 0;
    ADXT_Init();
}

void ADXT_Finish(void) {
    if (--adxt_init_cnt == 0) {
        DAT_004a9b1c = 0;
        ADXT_DestroyAll();
        FUN_00265c18();
        FUN_00260b30();
        ADXSTM_Finish();
        LSC_Finish();
        ADXCRS_Lock();
        SVM_DelCbSvr(2, 1);
        SVM_DelCbSvr(4, adxt_fssvr_id);
        SVM_DelCbSvr(5, adxt_svr_id);
        SVM_Finish();
        FUN_00265f88();
        FUN_00260788();
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
    FUN_00269268();
    in = SJRBF_Create(adxt_enc_ibuf, 1024, 0);
    out[0] = SJMEM_Create(adxt_enc_obuf, 32);
    out[1] = SJMEM_Create(adxt_enc_obuf + 32, 32);
    dst = adxt->sji;
    enc = FUN_002692c8(2, out, in);
    FUN_00269878(enc, nch, f92, end);
    FUN_00269508(enc);
    FUN_00269bd0();
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
    ADXENC_SetEnd(enc);
    FUN_00269498(enc);
    in->vt->destroy(in);
    out[1]->vt->destroy(out[1]);
    out[0]->vt->destroy(out[0]);
    FUN_00269298();
}
