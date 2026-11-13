/* MWSTM: the player's file stream, a thin layer over ADXSTM that reads a file or a sector range
 * of one into the player's SJ. */
#include "dw4/cri/adxstm.h"


int MWSTM_Init(void)
{
    return 0;
}

int MWSTM_InitStatic(void)
{
    return 0;
}

int mwstm_StubThird(void)
{
    return 0;
}

int MWSTM_FinishStatic(void)
{
    return 0;
}

int MWSTM_SetRdSct(AdxStmObj *stm, int nsct)
{
    if (stm == 0) {
        return 0;
    }
    ADXSTM_SetReqRdSize(stm, nsct);
    return 0;
}

int MWSTM_SetTrSct(void)
{
    return 0;
}

enum {
    MWSTM_SEEK_SET = 0,
    MWSTM_SEEK_CUR = 1,
    MWSTM_SEEK_END = 2
};

/* moves the read position by sectors, from the start, the current position or the file end */
int MWSTM_SeekSct(AdxStmObj *stm, int ofst, int whence)
{
    if (whence == MWSTM_SEEK_SET) {
        ADXSTM_Seek(stm, ofst);
    } else if (whence == MWSTM_SEEK_CUR) {
        ADXSTM_Seek(stm, ADXSTM_Tell(stm) + ofst);
    } else if (whence == MWSTM_SEEK_END) {
        ADXSTM_Seek(stm, (ADXSTM_GetFileLen(stm) + ADXSTM_SCT_LEN - 1) / ADXSTM_SCT_LEN + ofst);
    }
    return 0;
}

int MWSTM_Start(AdxStmObj *stm)
{
    ADXSTM_Start(stm);
    return 0;
}

int MWSTM_IsFsStatErr(AdxStmObj *stm)
{
    return ADXSTM_GetStat(stm) == ADXSTM_STAT_ERROR;
}

void MWSTM_ExecServer(void)
{
}

void MWSTM_SetFlowLimit(AdxStmObj *stm, int min, int max)
{
    if (stm != 0) {
        ADXSTM_SetBufSize(stm, min, max);
    }
}

void MWSTM_GetFlowLimit(AdxStmObj *stm, int *min, int *max)
{
    ADXSTM_GetBufSize(stm, min, max);
}

void MWSTM_GetFsizeByte(AdxStmObj *stm, int *len)
{
    *len = ADXSTM_GetFileLen(stm);
}

int MWSTM_GetStatRead(AdxStmObj *stm)
{
    return ADXSTM_GetStatRead(stm);
}

AdxStmObj *MWSTM_Create(SfdSj *sj)
{
    return ADXSTM_Create(sj, 0);
}

void MWSTM_Destroy(AdxStmObj *stm)
{
    ADXSTM_Destroy(stm);
}

void MWSTM_SetFname(AdxStmObj *stm, char *fname)
{
    ADXSTM_ReleaseFileNw(stm);
    ADXSTM_BindFileNw(stm, fname, 0, 0, ADXSTM_NO_MAXSCT);
    ADXSTM_SetEos(stm, ADXSTM_NO_MAXSCT);
}

void MWSTM_SetFileRange(AdxStmObj *stm, char *fname, void *dir, int ofst, int nsct)
{
    ADXSTM_ReleaseFileNw(stm);
    ADXSTM_BindFileNw(stm, fname, dir, ofst, nsct);
    ADXSTM_SetEos(stm, nsct);
}

int MWSTM_ReqStart(AdxStmObj *stm)
{
    return ADXSTM_Start(stm);
}

void MWSTM_ReqStop(AdxStmObj *stm)
{
    ADXSTM_StopNw(stm);
    ADXSTM_ReleaseFileNw(stm);
}

void MWSTM_Stop(AdxStmObj *stm)
{
    ADXSTM_Stop(stm);
    ADXSTM_ReleaseFile(stm);
}

int MWSTM_GetStat(AdxStmObj *stm)
{
    return ADXSTM_GetStat(stm);
}
