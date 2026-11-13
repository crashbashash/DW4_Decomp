typedef struct AdxRnaStream AdxRnaStream;
typedef struct AdxRnaStreamOps {
    void *slot[9];
    unsigned int (*query)(AdxRnaStream *stream, int which);
} AdxRnaStreamOps;
struct AdxRnaStream {
    AdxRnaStreamOps *ops;
};
typedef struct AdxRnaTrack {
    int f0;
    void *handle;
    AdxRnaStream *stream;
} AdxRnaTrack;
typedef struct AdxRnaTrackList {
    int f0;
    int f4;
    AdxRnaTrack *tracks[1];
} AdxRnaTrackList;
typedef struct AdxRna {
    int f0;
    int f4;
    int f8;
    AdxRnaTrackList *tracks;
} AdxRna;

extern char DAT_004ee378[];

int PS2RNA_SetupVoice();
int PS2RNA_Init();
int PS2RNA_SendOutMode();
int PS2RNA_StartAux();
int PS2RNA_StopAux();
int PS2RNA_SetAuxSw();
int PS2RNA_SetDualSw();
int PS2RNA_GetDualSw();
int PS2RNA_OpenPort();
int PS2RNA_ClosePort();
int PS2RNA_IsPortOpen();
int PS2RNA_Finish();
int PS2RNA_Create();
int PS2RNA_Destroy();
int PS2RNA_Start();
int PS2RNA_Stop();
int PS2RNA_SetTransSw();
int PS2RNA_SetPlaySw();
int PS2RNA_SetOutMode();
int PS2RNA_GetOutMode();
int PS2RNA_GetTime();
int PS2RNA_GetNumData();
int PS2RNA_GetNumRoom();
int PS2RNA_ExecServer();
int PS2RNA_SetStartSmpl();
int PS2RNA_SetNumChan();
int PS2RNA_SetSfreq();
int PS2RNA_SetOutVol();
int PS2RNA_SetOutPan();
int PS2RNA_SetOutBalance();
int PS2RNA_SetBitPerSmpl();
int PS2RNA_GetSfreq();
int PS2RNA_GetOutVol();
int PS2RNA_GetOutPan();
int PS2RNA_GetOutBalance();
int PS2RNA_GetBitPerSmpl();
int PS2RNA_DiscardData();
int PS2RNA_SetStmHdInfo();
unsigned int SJRMT_GetNumData(void *handle, int mode);
void ADXMSG_PrintErr(const char *format, ...);

void FUN_00265a20(void) {
    PS2RNA_SetupVoice();
}

unsigned int FUN_00265a38(AdxRna *rna, int ch)
{
    AdxRnaStream *s = rna->tracks->tracks[ch]->stream;
    return (unsigned int)s->ops->query(s, 1) >> 1;
}

unsigned int FUN_00265a78(AdxRna *rna, int index) {
    AdxRnaStream *stream = rna->tracks->tracks[index]->stream;
    return stream->ops->query(stream, 0) >> 1;
}

unsigned int FUN_00265ab8(AdxRna *rna, int index) {
    return SJRMT_GetNumData(rna->tracks->tracks[index]->handle, 1) >> 1;
}

unsigned int FUN_00265af0(AdxRna *rna, int index) {
    return SJRMT_GetNumData(rna->tracks->tracks[index]->handle, 0) >> 1;
}

void FUN_00265b28(void) {
    PS2RNA_SendOutMode();
}

void FUN_00265b40(void) {
    PS2RNA_StartAux();
}

void FUN_00265b58(void) {
    PS2RNA_StopAux();
}

void FUN_00265b70(AdxRna *rna) {
    PS2RNA_SetAuxSw(rna->tracks);
}

void FUN_00265b88(AdxRna *rna) {
    PS2RNA_SetDualSw(rna->tracks);
}

void FUN_00265ba0(AdxRna *rna)
{
    PS2RNA_GetDualSw(rna->tracks);
}

void FUN_00265bb8(void) {
    PS2RNA_OpenPort();
}

void FUN_00265bd0(void) {
    PS2RNA_ClosePort();
}

void FUN_00265be8(void) {
    PS2RNA_IsPortOpen();
}

void FUN_00265c00(void) {
    PS2RNA_Init();
}

void FUN_00265c18(void) {
    PS2RNA_Finish();
}

void FUN_00265c30(void)
{
}

void ADXRNA_Create(void) {
    PS2RNA_Create();
}

void ADXRNA_Destroy(void *handle) {
    PS2RNA_SetPlaySw(handle, 0);
    PS2RNA_SetTransSw(handle, 0);
    PS2RNA_Destroy(handle);
}

void FUN_00265c88(void) {
    PS2RNA_Start();
}

void FUN_00265ca0(void) {
    PS2RNA_Stop();
}

void ADXRNA_SetTransSw(void) {
    PS2RNA_SetTransSw();
}

void ADXRNA_SetPlaySw(void) {
    PS2RNA_SetPlaySw();
}

void ADXRNA_GetTime(void) {
    PS2RNA_GetTime();
}

void ADXRNA_GetNumData(void) {
    PS2RNA_GetNumData();
}

void ADXRNA_GetNumRoom(void) {
    PS2RNA_GetNumRoom();
}

void FUN_00265d30(void) {
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

void ADXRNA_SetNumChan(void) {
    PS2RNA_SetNumChan();
}

void ADXRNA_SetSfreq(void) {
    PS2RNA_SetSfreq();
}

void ADXRNA_SetOutVol(void) {
    PS2RNA_SetOutVol();
}

void ADXRNA_SetOutPan(void) {
    PS2RNA_SetOutPan();
}

void ADXRNA_SetOutBalance(void) {
    PS2RNA_SetOutBalance();
}

void ADXRNA_SetBitPerSmpl(void) {
    PS2RNA_SetBitPerSmpl();
}

void FUN_00265e28(void) {
    PS2RNA_GetSfreq();
}

void FUN_00265e40(void) {
    PS2RNA_GetOutVol();
}

void FUN_00265e58(void) {
    PS2RNA_GetOutPan();
}

void FUN_00265e70(void) {
    PS2RNA_GetOutBalance();
}

void FUN_00265e88(void) {
    PS2RNA_GetBitPerSmpl();
}

void ADXRNA_DiscardData(void) {
    PS2RNA_DiscardData();
}

void FUN_00265eb8(void)
{
}

void FUN_00265ec0(void)
{
}

void ADXRNA_SetOutMode(void) {
    PS2RNA_SetOutMode();
}

void ADXRNA_GetOutMode(void) {
    PS2RNA_GetOutMode();
}

void ADXRNA_SetTotalNumSmpl(void)
{
}

void FUN_00265f00(void)
{
}

int ADXRNA_SetStmHdInfo(void) {
    PS2RNA_SetStmHdInfo();
    return 0;
}
