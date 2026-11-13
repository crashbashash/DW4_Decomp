/* CRI PS2RNA (PS2RNA Ver.1.30): the ADX renderer whose voices play on the IOP. Each handle feeds its
 * channels from EE stream joints to IOP ones through DTR transfers; its settings are kept twice,
 * as set and as last sent, and the DTX send callback turns every difference into an IOP command.
 * With voices set up but none to play, the library is off and every entry point does nothing. */
#include "dw4/cri/sfdsj.h"

#define PS2RNA_MAX_OBJ 16
#define PS2RNA_MAX_PSJ 32
#define PS2RNA_MAX_NCH 2
#define PS2RNA_DEF_NVOICE 16
#define PS2RNA_DEF_IOP_WKSIZE 0x41000
#define PS2RNA_VOICE_IOP_WKSIZE 0x4100 /* PS2RNA_RMT_WKSIZE + PS2RNA_PSJ_BUFSIZE */
#define PS2RNA_RMT_WKSIZE 256           /* IOP work per SJRMT */
#define PS2RNA_UNI_WKSIZE 256           /* EE work per SJUNI */
#define PS2RNA_PSJ_BUFSIZE 0x4000       /* IOP buffer per voice */
#define PS2RNA_DEF_SFREQ 48000
#define PS2RNA_BIT_PER_SMPL 16
#define PS2RNA_MIN_OUTVOL (-999)
#define PS2RNA_MAX_OUTPAN 15

enum { SJ_LIN_FREE = 0 };

/* DTX remote procedures on the IOP side */
enum {
    PS2RNA_RPC_DESTROY = 9,
    PS2RNA_RPC_OUTMODE = 11,
    PS2RNA_RPC_INIT_PORT = 12,
    PS2RNA_RPC_FINISH_PORT = 13,
    PS2RNA_RPC_START_AUX = 14,
    PS2RNA_RPC_STOP_AUX = 15,
    PS2RNA_RPC_OPEN_PORT = 16,
    PS2RNA_RPC_CLOSE_PORT = 17
};

/* ps2rna_port_mode: which output ports the IOP reported */
enum { PS2RNA_PORT_BOTH = 2 };

/* One voice's stream path (24 bytes): IOP-side SJ, EE-side SJ and the SJX joining them. */
typedef struct Ps2RnaPsj {
    char used;          /* 0x00 */
    void *sjrmt;        /* 0x04 */
    SfdSj *sjuni;       /* 0x08 */
    void *sjx;          /* 0x0c */
    SfdSjChunk ck;      /* 0x10: the IOP buffer, handed to sjuni as free space */
} Ps2RnaPsj;

typedef struct DtrObj DtrObj;

/* A PS2RNA handle, 100 bytes. Each sent_ field holds what the IOP was last told. */
typedef struct Ps2Rna {
    signed char used;                   /* 0x00 */
    int maxnch;                         /* 0x04 */
    Ps2RnaPsj *psj[PS2RNA_MAX_NCH];     /* 0x08 */
    DtrObj *dtr[PS2RNA_MAX_NCH];        /* 0x10 */
    int pad24[2];
    int id;                             /* 0x20: the IOP handle */
    int pad36[3];
    int sfreq;                          /* 0x30 */
    int sent_sfreq;
    int outvol;                         /* 0x38: dB/10, -999 to 0 */
    int sent_outvol;
    int outpan[PS2RNA_MAX_NCH];         /* 0x40 */
    int sent_outpan[PS2RNA_MAX_NCH];
    signed char playsw;                 /* 0x50 */
    signed char sent_playsw;
    signed char nch;                    /* 0x52 */
    signed char sent_nch;
    signed char auxsw;                  /* 0x54 */
    signed char sent_auxsw;
    signed char dualsw;                 /* 0x56 */
    signed char sent_dualsw;
    signed char transsw;                /* 0x58 */
    signed char trans_stopped;          /* 0x59 */
    signed char sent_stopflag;          /* 0x5a */
    signed char stopflag;               /* 0x5b */
    int outbalance;                     /* 0x5c */
    int sent_outbalance;
} Ps2Rna;

void ADXMSG_PrintErr(const char *format, ...);
void *memset(void *dst, int value, unsigned int size);
void *sceSifAllocIopHeap(int size);
int sceSifFreeIopHeap(void *addr);
int CRICFG_Read(const char *name, int *value);
int DTX_CallUrpc(int fno, int *send, int nsend, int *recv, int nrecv);
void DTX_Destroy(void *dtx);
void DTX_Finish(void);
void DTR_ExecServer(void);
void DTR_Destroy(DtrObj *dtr);
void DTR_Stop(DtrObj *dtr);
void *SJRMT_Create(int mode, int work, int size);
void SJRMT_Destroy(void *sjrmt);
void SJRMT_Finish(void);
SfdSj *SJUNI_Create(int mode, char *work, int size);
void *SJX_Create(SfdSj *sjuni, void *sjrmt, int mode);
void SJX_Destroy(void *sjx);
void SJX_Finish(void);
void SJX_ExecServer(void);
void SJCRS_BeginSvr(void);
void SJCRS_EndSvr(void);

extern int ps2rna_nvoice;
extern int ps2rna_iop_wksize;
extern int ps2rna_setup_voice;
extern void *ps2rna_iop_heap;
extern int ps2rna_iop_work;
extern signed char ps2rna_iop_alloced;
extern void *ps2rna_rna_heap;
extern int ps2rna_nste;
extern int ps2rna_nmono;
extern int ps2rna_aux_on;
extern int ps2rna_outmode;
extern int ps2rna_sent_outmode;
extern int ps2rna_port_on[2];
extern int ps2rna_port_mode;
extern int ps2rna_init_cnt;
extern void *ps2rna_dtx_heap;
extern Ps2RnaPsj ps2rna_psj[PS2RNA_MAX_PSJ];
extern char ps2rna_psj_buf[PS2RNA_MAX_PSJ][PS2RNA_UNI_WKSIZE];
extern Ps2Rna ps2rna_obj[PS2RNA_MAX_OBJ];
extern void *ps2rna_dtx;
extern char PS2RNA_SetupVoice_Illigal_parameter_nste_d[];
extern char PS2RNA_SetupVoice_Illigal_parameter_nmono_d[];
extern char PS2RNA_SetupVoice_The_set_up_value_exceeded_maximum_MAX_d[];
extern char PS2RNA_E01112903_Failed_sceSifAllocIopHeap_in_ps2rna_init_psj[];
extern char PS2RNA_sceSifAllocIopHeap_d_ret_0x_08x[];
extern char E0110101_ps2rna_init_psj_wk_size_error[];
extern char E0110102_ps2rna_init_psj_can_t_creat_SJUNI_CreaetRmt[];
extern char E0110103_ps2rna_init_psj_wk_size_error[];
extern char E0110104_ps2rna_init_psj_can_t_creat_SJUNI_Creaet[];
extern char E0110105_ps2rna_init_psj_can_t_creat_SJX_Create[];
extern char BASE_SFREQ[];
extern char PS2RNA_Start_not_implemented[];
extern char PS2RNA_ClearBuf_not_implemented[];
extern char PS2RNA_SetPcmType_not_implemented[];
extern char PS2RNA_SetStartSmpl_not_implemented[];
extern char PS2RNA_SetBitPerSmpl_not_support_d_bps[];
extern char PS2RNA_GetStartSmpl_not_implemented[];
extern char PS2RNA_IsOverflow_not_implemented[];
extern char PS2RNA_ClearOverflow_not_implemented[];
extern char PS2RNA_DiscardData_not_implemented[];
extern char PS2RNA_SetTotalNumSmpl_not_implemented[];
extern char PS2RNA_SetStmHdInfo_not_implemented[];

#define PS2RNA_IS_OFF() (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0)

void ps2rna_exec_one(Ps2Rna *rna);

void PS2RNA_SetupVoice(int nste, int nmono)
{
    int nvoice;

    if (nste < 0) {
        ADXMSG_PrintErr(PS2RNA_SetupVoice_Illigal_parameter_nste_d, nste);
        return;
    }
    if (nmono < 0) {
        ADXMSG_PrintErr(PS2RNA_SetupVoice_Illigal_parameter_nmono_d, nmono);
        return;
    }
    nvoice = nste * 2 + nmono;
    if (nvoice > PS2RNA_MAX_PSJ) {
        ADXMSG_PrintErr(PS2RNA_SetupVoice_The_set_up_value_exceeded_maximum_MAX_d, PS2RNA_MAX_PSJ);
        return;
    }
    ps2rna_nvoice = nvoice;
    ps2rna_nste = nste;
    ps2rna_nmono = nmono;
    ps2rna_iop_wksize = nvoice * PS2RNA_VOICE_IOP_WKSIZE;
    ps2rna_setup_voice = 1;
}

/* Allocates the IOP work once and builds one SJRMT/SJUNI/SJX path per voice; any failure hangs. */
void ps2rna_init_psj(void)
{
    Ps2RnaPsj *psj;
    int work;
    int i;

    if (ps2rna_setup_voice == 0) {
        ps2rna_nvoice = PS2RNA_DEF_NVOICE;
        ps2rna_iop_wksize = PS2RNA_DEF_IOP_WKSIZE;
    }
    if (ps2rna_iop_heap == 0) {
        ps2rna_iop_heap = sceSifAllocIopHeap(ps2rna_iop_wksize + 64);
        if (ps2rna_iop_heap == 0) {
            ADXMSG_PrintErr(PS2RNA_E01112903_Failed_sceSifAllocIopHeap_in_ps2rna_init_psj, ps2rna_iop_wksize + 64);
            for (;;) {
            }
        }
        ADXMSG_PrintErr(PS2RNA_sceSifAllocIopHeap_d_ret_0x_08x, ps2rna_iop_wksize + 64, ps2rna_iop_heap);
        ps2rna_iop_work = ((int)ps2rna_iop_heap + 64) & ~63;
        ps2rna_iop_alloced = 1;
    }
    memset(ps2rna_psj, 0, sizeof(ps2rna_psj));
    work = ps2rna_iop_work;
    for (i = 0; i < ps2rna_nvoice; i++) {
        psj = &ps2rna_psj[i];
        psj->used = 0;
        if (work & 63) {
            ADXMSG_PrintErr(E0110101_ps2rna_init_psj_wk_size_error);
            for (;;) {
            }
        }
        psj->sjrmt = SJRMT_Create(1, work, PS2RNA_RMT_WKSIZE);
        work += PS2RNA_RMT_WKSIZE;
        if (psj->sjrmt == 0) {
            ADXMSG_PrintErr(E0110102_ps2rna_init_psj_can_t_creat_SJUNI_CreaetRmt);
            for (;;) {
            }
        }
        if (work & 63) {
            ADXMSG_PrintErr(E0110103_ps2rna_init_psj_wk_size_error);
            for (;;) {
            }
        }
        psj->sjuni = SJUNI_Create(1, ps2rna_psj_buf[i], PS2RNA_UNI_WKSIZE);
        if (psj->sjuni == 0) {
            ADXMSG_PrintErr(E0110104_ps2rna_init_psj_can_t_creat_SJUNI_Creaet);
            for (;;) {
            }
        }
        psj->ck.len = PS2RNA_PSJ_BUFSIZE;
        psj->ck.data = (char *)work;
        psj->sjuni->vtbl->putChunk(psj->sjuni, SJ_LIN_FREE, &psj->ck);
        work += PS2RNA_PSJ_BUFSIZE;
        psj->sjx = SJX_Create(psj->sjuni, psj->sjrmt, 1);
        if (psj->sjx == 0) {
            ADXMSG_PrintErr(E0110105_ps2rna_init_psj_can_t_creat_SJX_Create);
            for (;;) {
            }
        }
    }
}

void ps2rna_finish_psj(void)
{
    Ps2RnaPsj *psj;
    int i;

    for (i = 0; i < ps2rna_nvoice; i++) {
        psj = &ps2rna_psj[i];
        if (psj->sjrmt != 0) {
            SJRMT_Destroy(psj->sjrmt);
        }
        if (psj->sjuni != 0) {
            psj->sjuni->vtbl->destroy(psj->sjuni);
        }
        if (psj->sjx != 0) {
            SJX_Destroy(psj->sjx);
        }
        memset(psj, 0, sizeof(*psj));
    }
    if (ps2rna_iop_alloced == 1) {
        sceSifFreeIopHeap(ps2rna_iop_heap);
        ps2rna_iop_heap = 0;
        ps2rna_iop_alloced = 0;
    }
}

Ps2RnaPsj *ps2rna_get_psj(void)
{
    Ps2RnaPsj *psj = 0;
    int i;

    for (i = 0; i < ps2rna_nvoice; i++) {
        psj = &ps2rna_psj[i];
        if (psj->used == 0) {
            break;
        }
    }
    if (i == ps2rna_nvoice) {
        return 0;
    }
    psj->used = 1;
    return psj;
}

void ps2rna_release_psj(Ps2RnaPsj *psj)
{
    psj->used = 0;
}

/* The DTX receive callback: the IOP's reply is a spin count to wait out; no reply hangs. */
void ps2rna_dtx_recv(void *obj, int *reply)
{
    int n;

    if (reply == 0) {
        for (;;) {
        }
    }
    n = *reply;
    if (n > 0) {
        while (--n) {
        }
    }
}

void PS2RNA_SendOutMode(int outmode)
{
    int arg;

    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        arg = outmode;
        DTX_CallUrpc(PS2RNA_RPC_OUTMODE, &arg, 1, 0, 0);
    }
}

/* Tells the IOP the output rate (CRI CFG's BASE_SFREQ, else 48 kHz) and opens the ports it reports. */
void ps2rna_init_port(void)
{
    int value;
    int sfreq;
    int reply;
    int mode;

    if (PS2RNA_IS_OFF()) {
        return;
    }
    if (CRICFG_Read(BASE_SFREQ, &value) == 0) {
        sfreq = value;
    } else {
        sfreq = PS2RNA_DEF_SFREQ;
    }
    ps2rna_port_mode = mode = DTX_CallUrpc(PS2RNA_RPC_INIT_PORT, &sfreq, 1, &reply, 1);
    ps2rna_outmode = 0;
    ps2rna_sent_outmode = 0;
    if (mode == PS2RNA_PORT_BOTH) {
        ps2rna_port_on[0] = 1;
        ps2rna_port_on[1] = 1;
    } else {
        ps2rna_port_on[mode] = 1;
        ps2rna_port_on[mode == 0] = 0;
    }
}

int ps2rna_finish_port(void)
{
    int ret;

    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ret = DTX_CallUrpc(PS2RNA_RPC_FINISH_PORT, 0, 0, 0, 0);
        ps2rna_port_on[0] = 0;
        ps2rna_port_on[1] = 0;
        /* matching construct: hand search — the request result stays live in v0 (the pair is cleared through
           v1), so it is returned on this path; the inactive path falls off the end with no value */
        return ret;
    }
}

void PS2RNA_StartAux(void)
{
    if ((ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) && ps2rna_aux_on != 1) {
        DTX_CallUrpc(PS2RNA_RPC_START_AUX, 0, 0, 0, 0);
        ps2rna_aux_on = 1;
    }
}

void PS2RNA_StopAux(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        if (ps2rna_aux_on != 0) {
            DTX_CallUrpc(PS2RNA_RPC_STOP_AUX, 0, 0, 0, 0);
            ps2rna_aux_on = 0;
        }
    }
}

/* A handle's aux switch can only be turned on while aux output runs. */
void PS2RNA_SetAuxSw(Ps2Rna *rna, int sw)
{
    if (PS2RNA_IS_OFF()) {
        return;
    }
    if (rna->auxsw == sw) {
        return;
    }
    if (ps2rna_aux_on == 0 && sw == 1) {
        return;
    }
    rna->auxsw = sw;
}

void PS2RNA_SetDualSw(Ps2Rna *rna, int sw)
{
    if ((ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) && ps2rna_port_mode == PS2RNA_PORT_BOTH && rna->dualsw != sw) {
        rna->dualsw = sw;
    }
}

signed char PS2RNA_GetDualSw(Ps2Rna *rna)
{
    return rna->sent_dualsw;
}

void PS2RNA_OpenPort(unsigned int port)
{
    int arg[4];

    if (PS2RNA_IS_OFF()) {
        return;
    }
    if (port < 2 && ps2rna_port_on[port] != 1) {
        arg[0] = port;
        DTX_CallUrpc(PS2RNA_RPC_OPEN_PORT, arg, 1, 0, 0);
        ps2rna_port_on[port] = 1;
    }
}

void PS2RNA_ClosePort(unsigned int port)
{
    int arg[4];

    if (PS2RNA_IS_OFF()) {
        return;
    }
    if (port < 2 && ps2rna_port_on[port] != 0) {
        arg[0] = port;
        DTX_CallUrpc(PS2RNA_RPC_CLOSE_PORT, arg, 1, 0, 0);
        ps2rna_port_on[port] = 0;
    }
}

int PS2RNA_IsPortOpen(unsigned int port)
{
    int on;

    on = 0;
    if (port < 2) {
        on = ps2rna_port_on[port];
    }
    return on;
}

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the last call into a sibling call */
int PS2RNA_Finish(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        if (--ps2rna_init_cnt == 0) {
            sceSifFreeIopHeap(ps2rna_rna_heap);
            ps2rna_rna_heap = 0;
            DTX_Destroy(ps2rna_dtx);
            ps2rna_dtx = 0;
            sceSifFreeIopHeap(ps2rna_dtx_heap);
            ps2rna_dtx_heap = 0;
            ps2rna_finish_psj();
            ps2rna_finish_port();
            DTX_Finish();
            SJX_Finish();
            SJRMT_Finish();
        }
    }
}

void PS2RNA_Destroy(Ps2Rna *rna)
{
    int arg[4];
    int i;

    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        for (i = 0; i < rna->maxnch; i++) {
            if (rna->dtr[i] != 0) {
                DTR_Destroy(rna->dtr[i]);
            }
        }
        arg[0] = rna->id;
        DTX_CallUrpc(PS2RNA_RPC_DESTROY, arg, 1, 0, 0);
        for (i = 0; i < rna->maxnch; i++) {
            if (rna->psj[i] != 0) {
                ps2rna_release_psj(rna->psj[i]);
            }
        }
    }
    rna->used = 0;
}

void PS2RNA_Start(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ADXMSG_PrintErr(PS2RNA_Start_not_implemented);
    }
}

void PS2RNA_SetTransSw(Ps2Rna *rna, int sw);
void PS2RNA_SetPlaySw(Ps2Rna *rna, int sw);

void PS2RNA_Stop(Ps2Rna *rna)
{
    if (PS2RNA_IS_OFF()) {
        return;
    }
    PS2RNA_SetTransSw(rna, 0);
    PS2RNA_SetPlaySw(rna, 0);
}

void PS2RNA_SetTransSw(Ps2Rna *rna, int sw)
{
    int nch = rna->nch;
    int i;

    if (PS2RNA_IS_OFF()) {
        return;
    }
    rna->transsw = sw;
    if (sw == 1) {
        return;
    }
    for (i = 0; i < nch; i++) {
        DTR_Stop(rna->dtr[i]);
        rna->trans_stopped = 1;
        rna->transsw = 0;
    }
}

void PS2RNA_SetPlaySw(Ps2Rna *rna, int sw)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        rna->playsw = sw;
    }
}

void PS2RNA_SetOutMode(int outmode)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ps2rna_outmode = outmode;
    }
}

int PS2RNA_GetOutMode(void)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    return ps2rna_outmode;
}

void PS2RNA_SetStopFlag(Ps2Rna *rna, int flag)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        rna->stopflag = flag;
    }
}

void PS2RNA_ClearBuf(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ADXMSG_PrintErr(PS2RNA_ClearBuf_not_implemented);
    }
}

void PS2RNA_SetPcmType(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ADXMSG_PrintErr(PS2RNA_SetPcmType_not_implemented);
    }
}

void PS2RNA_GetTime(Ps2Rna *rna, int *ncount, int *tscale)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        *ncount = 0;
        *tscale = PS2RNA_DEF_SFREQ;
    }
}

int PS2RNA_GetNumData(Ps2Rna *rna)
{
    SfdSj *sjuni;

    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    sjuni = rna->psj[0]->sjuni;
    return (PS2RNA_PSJ_BUFSIZE - sjuni->vtbl->getNumData(sjuni, SJ_LIN_FREE)) / 2;
}

int PS2RNA_GetNumRoom(Ps2Rna *rna)
{
    SfdSj *sjuni;

    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    sjuni = rna->psj[0]->sjuni;
    return sjuni->vtbl->getNumData(sjuni, SJ_LIN_FREE) / 2;
}

void PS2RNA_ExecServer(void)
{
    int i;

    if (PS2RNA_IS_OFF()) {
        return;
    }
    SJCRS_BeginSvr();
    for (i = 0; i < PS2RNA_MAX_OBJ; i++) {
        if (ps2rna_obj[i].used == 1) {
            ps2rna_exec_one(&ps2rna_obj[i]);
        }
    }
    SJCRS_EndSvr();
    DTR_ExecServer();
    SJX_ExecServer();
}

void PS2RNA_SetStartSmpl(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ADXMSG_PrintErr(PS2RNA_SetStartSmpl_not_implemented);
    }
}

void PS2RNA_SetNumChan(Ps2Rna *rna, int nch)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        rna->nch = nch;
    }
}

void PS2RNA_SetSfreq(Ps2Rna *rna, int sfreq)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        rna->sfreq = sfreq;
    }
}

void PS2RNA_SetOutVol(Ps2Rna *rna, int vol)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        if (vol > 0) {
            vol = 0;
        }
        if (vol < PS2RNA_MIN_OUTVOL) {
            vol = PS2RNA_MIN_OUTVOL;
        }
        rna->outvol = vol;
    }
}

void PS2RNA_SetOutPan(Ps2Rna *rna, int ch, int pan)
{
    int clamped;

    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        clamped = -PS2RNA_MAX_OUTPAN;
        if (pan >= -PS2RNA_MAX_OUTPAN) {
            clamped = pan;
        }
        if (clamped > PS2RNA_MAX_OUTPAN) {
            clamped = PS2RNA_MAX_OUTPAN;
        }
        rna->outpan[ch] = clamped;
    }
}

void PS2RNA_SetOutBalance(Ps2Rna *rna, int balance)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        rna->outbalance = balance;
    }
}

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the report call into a sibling call */
int PS2RNA_SetBitPerSmpl(Ps2Rna *rna, int bps)
{
    if ((ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) && bps != PS2RNA_BIT_PER_SMPL) {
        ADXMSG_PrintErr(PS2RNA_SetBitPerSmpl_not_support_d_bps, bps);
    }
}

int PS2RNA_GetStartSmpl(void)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    ADXMSG_PrintErr(PS2RNA_GetStartSmpl_not_implemented);
    return 0;
}

int PS2RNA_GetSfreq(Ps2Rna *rna)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    return rna->sfreq;
}

int PS2RNA_GetOutVol(Ps2Rna *rna)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    return rna->outvol;
}

int PS2RNA_GetOutPan(Ps2Rna *rna, int ch)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    return rna->outpan[ch];
}

int PS2RNA_GetOutBalance(Ps2Rna *rna)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    return rna->outbalance;
}

int PS2RNA_GetBitPerSmpl(void)
{
    if (PS2RNA_IS_OFF()) {
        return PS2RNA_BIT_PER_SMPL;
    }
    return PS2RNA_BIT_PER_SMPL;
}

int PS2RNA_IsOverflow(void)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    ADXMSG_PrintErr(PS2RNA_IsOverflow_not_implemented);
    return 0;
}

void PS2RNA_ClearOverflow(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ADXMSG_PrintErr(PS2RNA_ClearOverflow_not_implemented);
    }
}

void PS2RNA_ExecHndl(void)
{
}

int PS2RNA_DiscardData(void)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    ADXMSG_PrintErr(PS2RNA_DiscardData_not_implemented);
    return 0;
}

void PS2RNA_SetTotalNumSmpl(void)
{
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        ADXMSG_PrintErr(PS2RNA_SetTotalNumSmpl_not_implemented);
    }
}

int PS2RNA_SetStmHdInfo(void)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    ADXMSG_PrintErr(PS2RNA_SetStmHdInfo_not_implemented);
    return 0;
}

SfdSj *PS2RNA_GetSjUni(Ps2Rna *rna, int ch)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    return rna->psj[ch]->sjuni;
}

void *PS2RNA_GetSjRmt(Ps2Rna *rna, int ch)
{
    if (PS2RNA_IS_OFF()) {
        return 0;
    }
    return rna->psj[ch]->sjrmt;
}
