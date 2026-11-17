#include "dw4/cri/cri_adxt.h"
#include <string.h>
#include "dw4/cri/svm.h"
#include "dw4/cri/adx_ps2.h"
#include "dw4/cri/adxrna.h"
#include "dw4/cri/adxsjd.h"
#include "dw4/cri/adxstm.h"
#include "dw4/cri/adxcrs.h"
#include "dw4/cri/adxerrs.h"
#include "dw4/cri/sj.h"
#include "dw4/cri/lsc.h"
#include "dw4/cri/adxenc.h"
#include "dw4/cri/cri_adxf.h"
#include "dw4/cri/dtx.h"

typedef struct AdxEnc AdxEnc;

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

void ADXT_ConfigVsyncSvr(int value) {
    adxt_thrd_svr_sw = value;
}

void adxini_rnaerr_cbfn(void *unused, char *message) {
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
        ADXF_Init();
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
        dtx_send_sw = 0;
        ADXT_DestroyAll();
        ADXRNA_Finish();
        ADXF_Finish();
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
        dtx_send_sw = 1;
    }
}

void ADXT_InsertHdrSfa(AdxtObj *adxt, int nch, int sfreq, int nsmpl)
{
    SfdSj *out[2];
    SfdSjChunk ckIn;
    SfdSjChunk ckOut;
    SfdSj *in;
    SfdSj *dst;
    AdxEnc *enc;
    ADXSJE_Init();
    in = SJRBF_Create(adxt_enc_ibuf, 1024, 0);
    out[0] = SJMEM_Create(adxt_enc_obuf, 32);
    out[1] = SJMEM_Create(adxt_enc_obuf + 32, 32);
    dst = adxt->sji;
    enc = ADXSJE_Create(2, out, in);
    ADXSJE_SetConfigSfa(enc, nch, sfreq, nsmpl);
    ADXSJE_Start(enc);
    ADXSJE_ExecServer();
    in->vtbl->getChunk(in, 1, 1024, &ckIn);
    if (ckIn.len == 0) {
        for (;;) {
        }
    }
    dst->vtbl->getChunk(dst, 0, ckIn.len, &ckOut);
    if (ckOut.len < ckIn.len) {
        for (;;) {
        }
    }
    memcpy(ckOut.data, ckIn.data, ckIn.len);
    in->vtbl->putChunk(in, 0, &ckIn);
    dst->vtbl->putChunk(dst, 1, &ckOut);
    ADXSJE_Stop(enc);
    ADXSJE_Destroy(enc);
    in->vtbl->destroy(in);
    out[1]->vtbl->destroy(out[1]);
    out[0]->vtbl->destroy(out[0]);
    ADXSJE_Finish();
}
