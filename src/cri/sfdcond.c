#include "dw4/cri/sfd.h"
#include "dw4/cri/sfdply.h"

void sfset_SetCondAll(int index, int value);
void sfset_SetUsrCond(SfdPly *hn, int index, int value);
int sfset_IsCondValid(SfdPly *hn, int index, int value);
void SFSET_GetTrHn(char *ctx, int index, int *out);

int SFD_GetSvrStat(void)
{
    return SFPLY_DecideSvrStat();
}

int SFD_GetHnStat(void *sfd)
{
    SfdPly *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        sfd_ReportError(0, 0xFF000111);
    }
    return hn->stat;
}

int SFD_SetCond(void *sfd, int index, int value)
{
    SfdPly *hn = sfd;
    if (hn == 0) {
        sfset_SetCondAll(index, value);
        sfd_lib.cond[index] = value;
    } else {
        if (SFLIB_CheckHn(hn) != 0) {
            return sfd_ReportError(0, 0xFF000112);
        }
        SFSET_SetCond(hn, index, value);
        sfset_SetUsrCond(hn, index, value);
    }
    return 0;
}

void sfset_SetCondAll(int index, int value)
{
    SfdPly **slots = sfd_lib.hn;
    int i;
    for (i = 0; i < 8; i++) {
        if (slots[i] != 0) {
            SFSET_SetCond(slots[i], index, value);
        }
    }
}

void SFSET_SetCond(void *sfd, int index, int value)
{
    SfdPly *hn = sfd;
    if (sfset_IsCondValid(hn, index, value) != 0) {
        hn->cond[index] = value;
    }
}

void sfset_SetUsrCond(SfdPly *hn, int index, int value)
{
    if (sfset_IsCondValid(hn, index, value) != 0) {
        hn->cond2[index] = value;
    }
}

int sfset_IsCondValid(SfdPly *hn, int index, int value)
{
    if (index == SFD_COND_AUDIO && value == 1 && SFTRN_IsSetup(hn, 3) == 0) {
        return 0;
    }
    if (index == SFD_COND_VIDEO && value == 1 && SFTRN_IsSetup(hn, 2) == 0) {
        return 0;
    }
    return 1;
}

int SFD_GetCond(void *sfd, int index, int *out)
{
    SfdPly *hn = sfd;
    if (hn == 0) {
        *out = sfd_lib.cond[index];
    } else {
        /* matching construct: manual — both paths fall through to one `return 0` */
        if (SFLIB_CheckHn(hn) != 0) {
            return sfd_ReportError(0, 0xFF000113);
        }
        *out = SFSET_GetCond(hn, index);
    }
    return 0;
}

int SFSET_GetCond(void *sfd, int index)
{
    SfdPly *hn = sfd;
    return hn->cond[index];
}

int SFD_GetMvInf(void *sfd, SfdMvInf *out)
{
    SfdPly *hn = sfd;
    int r = SFLIB_CheckHn(hn);
    if (r != 0) {
        return sfd_ReportError(0, 0xFF000114);
    }
    *out = hn->mvInf;
    return r;
}

int SFD_GetPlyInf(void *sfd, SfdPlyInf *out)
{
    SfdPly *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000119);
    }
    *out = hn->plyInf;
    return 0;
}


int SFD_GetTmrInf(SfdPly *hn, SfdTmrInf *inf)
{
    int i;

    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00011A);
    }
    *inf = hn->tmr;
    for (i = 1; i < 4; i++) {
        inf->tsum[0].sum += inf->tsum[i].sum;
        inf->tsum[0].min = (inf->tsum[i].min < inf->tsum[0].min) ? inf->tsum[i].min : inf->tsum[0].min;
        inf->tsum[0].max = (inf->tsum[0].max < inf->tsum[i].max) ? inf->tsum[i].max : inf->tsum[0].max;
        inf->tsum[0].count += inf->tsum[i].count;
    }
    return 0;
}

int SFD_GetTrHn(void *sfd, int index, int *out)
{
    SfdPly *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000117);
    }
    SFSET_GetTrHn((char *)hn, index, out);
    return 0;
}

void SFSET_GetTrHn(char *ctx, int index, int *out)
{
    int *value = ((SfdPly *)(ctx + index * 0x44))->trn[0].hn.obj;
    if (value == 0) {
        *out = 0;
        return;
    }
    *out = *value;
}

int SFD_GetSofdecHeader(SfdPly *hn, char **data, int *size)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00011C);
    }
    if (hn->hdr.valid != 0) {
        *data = hn->hdr.data;
        *size = hn->hdr.size;
    } else {
        *data = 0;
        *size = 0;
    }
    return 0;
}
