/* CRI ADXRNA: the ADX renderer interface, which on the PS2 forwards every call to PS2RNA. */
#include "dw4/cri/adxrna.h"
#include "dw4/cri/adxmsg.h"

extern char DAT_004ee378[];

void ADXPS2_SetupVoice(int nste, int nmono) {
    PS2RNA_SetupVoice(nste, nmono);
}

unsigned int ADXPS2_GetNumDataSjtmp(AdxtObj *adxt, int ch)
{
    SfdSj *sj = adxt->rna->psj[ch]->sjuni;
    return (unsigned int)sj->vtbl->getNumData(sj, SJ_LIN_DATA) >> 1;
}

unsigned int ADXPS2_GetNumRoomSjtmp(AdxtObj *adxt, int ch) {
    SfdSj *sj = adxt->rna->psj[ch]->sjuni;
    return (unsigned int)sj->vtbl->getNumData(sj, SJ_LIN_FREE) >> 1;
}

unsigned int ADXPS2_GetNumDataSjiop(AdxtObj *adxt, int ch) {
    return (unsigned int)SJRMT_GetNumData(adxt->rna->psj[ch]->sjrmt, SJ_LIN_DATA) >> 1;
}

unsigned int ADXPS2_GetNumRoomSjiop(AdxtObj *adxt, int ch) {
    return (unsigned int)SJRMT_GetNumData(adxt->rna->psj[ch]->sjrmt, SJ_LIN_FREE) >> 1;
}

void FUN_00265b28(int outmode) {
    PS2RNA_SendOutMode(outmode);
}

void FUN_00265b40(void) {
    PS2RNA_StartAux();
}

void FUN_00265b58(void) {
    PS2RNA_StopAux();
}

void ADXPS2_RestoreIopSnd(AdxtObj *adxt, int sw) {
    PS2RNA_SetAuxSw(adxt->rna, sw);
}

void ADXPS2_BeginDolbyDigital(AdxtObj *adxt, int sw) {
    PS2RNA_SetDualSw(adxt->rna, sw);
}

void ADXPS2_EndDolbyDigital(AdxtObj *adxt)
{
    PS2RNA_GetDualSw(adxt->rna);
}

void FUN_00265bb8(unsigned int port) {
    PS2RNA_OpenPort(port);
}

void FUN_00265bd0(unsigned int port) {
    PS2RNA_ClosePort(port);
}

int FUN_00265be8(unsigned int port) {
    return PS2RNA_IsPortOpen(port);
}

void ADXRNA_Init(void) {
    PS2RNA_Init();
}

void ADXRNA_Finish(void) {
    PS2RNA_Finish();
}

void ADXRNA_EntryErrFunc(AdxErrFunc func, void *obj)
{
}

Ps2Rna *ADXRNA_Create(SfdSj **sjo, int maxnch) {
    return PS2RNA_Create(sjo, maxnch);
}

void ADXRNA_Destroy(Ps2Rna *rna) {
    PS2RNA_SetPlaySw(rna, 0);
    PS2RNA_SetTransSw(rna, 0);
    PS2RNA_Destroy(rna);
}

void ADXRNA_Start(void) {
    PS2RNA_Start();
}

void ADXRNA_Stop(Ps2Rna *rna) {
    PS2RNA_Stop(rna);
}

void ADXRNA_SetTransSw(Ps2Rna *rna, int sw) {
    PS2RNA_SetTransSw(rna, sw);
}

void ADXRNA_SetPlaySw(Ps2Rna *rna, int sw) {
    PS2RNA_SetPlaySw(rna, sw);
}

void ADXRNA_GetTime(Ps2Rna *rna, int *ncount, int *tscale) {
    PS2RNA_GetTime(rna, ncount, tscale);
}

int ADXRNA_GetNumData(Ps2Rna *rna) {
    return PS2RNA_GetNumData(rna);
}

int ADXRNA_GetNumRoom(Ps2Rna *rna) {
    return PS2RNA_GetNumRoom(rna);
}

void ADXRNA_GetStat(void) {
    ADXMSG_PrintErr(DAT_004ee378);
    for (;;) {
    }
}

void ADXRNA_ExecServer(void) {
    PS2RNA_ExecServer();
}

void FUN_00265d80(void) {
    PS2RNA_SetStartSmpl();
}

void ADXRNA_SetNumChan(Ps2Rna *rna, int nch) {
    PS2RNA_SetNumChan(rna, nch);
}

void ADXRNA_SetSfreq(Ps2Rna *rna, int sfreq) {
    PS2RNA_SetSfreq(rna, sfreq);
}

void ADXRNA_SetOutVol(Ps2Rna *rna, int vol) {
    PS2RNA_SetOutVol(rna, vol);
}

void ADXRNA_SetOutPan(Ps2Rna *rna, int ch, int pan) {
    PS2RNA_SetOutPan(rna, ch, pan);
}

void ADXRNA_SetOutBalance(Ps2Rna *rna, int balance) {
    PS2RNA_SetOutBalance(rna, balance);
}

void ADXRNA_SetBitPerSmpl(Ps2Rna *rna, int bps) {
    PS2RNA_SetBitPerSmpl(rna, bps);
}

int FUN_00265e28(Ps2Rna *rna) {
    return PS2RNA_GetSfreq(rna);
}

int FUN_00265e40(Ps2Rna *rna) {
    return PS2RNA_GetOutVol(rna);
}

int ADXRNA_GetOutVol(Ps2Rna *rna, int ch) {
    return PS2RNA_GetOutPan(rna, ch);
}

int ADXRNA_GetOutPan(Ps2Rna *rna) {
    return PS2RNA_GetOutBalance(rna);
}

int ADXRNA_GetBitPerSmpl(void) {
    return PS2RNA_GetBitPerSmpl();
}

int ADXRNA_DiscardData(Ps2Rna *rna, int nsmpl) {
    return PS2RNA_DiscardData(rna, nsmpl);
}

void ADXRNA_ClearBuf(void)
{
}

void ADXRNA_SetPcmType(void)
{
}

void ADXRNA_SetOutMode(int mode) {
    PS2RNA_SetOutMode(mode);
}

int ADXRNA_GetOutMode(void) {
    return PS2RNA_GetOutMode();
}

void ADXRNA_SetTotalNumSmpl(Ps2Rna *rna, int nsmpl)
{
}

void ADXRNA_SetWavFname(void)
{
}

int ADXRNA_SetStmHdInfo(Ps2Rna *rna, char *info) {
    PS2RNA_SetStmHdInfo(rna, info);
    return 0;
}
