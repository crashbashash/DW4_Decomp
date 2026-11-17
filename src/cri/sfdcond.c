#include "dw4/cri/sfd.h"

typedef struct SfdStat64 {
    long sum;
    long min;
    long max;
    int count;
    int pad28;
} SfdStat64;

typedef struct SfdReport {
    SfdStat64 stat[6];
} SfdReport;

typedef struct SfdHn {
    char pad0[72];
    int state;
    char pad76[120 - 76];
    int f120;
    char pad124[264 - 124];
    int f264;
    char f268[2316 - 268];
    SfdMvInf mvInf;
    char pad2380[2384 - 2380];
    SfdPlyInf plyInf;
    char pad2544[2564 - 2544];
    int cond[100];
    int cond2[100];
    char pad3364[13880 - 3364];
    SfdReport report;
} SfdHn;

typedef struct SfdEntryRef {
    char pad[7984];
    int *value;
} SfdEntryRef;

/* kept here: sfdcond.c, sfdlib.c and sfdply.c each read the library block through their own view, and the types disagree */
extern int sfd_lib[];
typedef struct SfdLib {
    int counter;
    int f4;
    int rate;
    char pad12[84 - 12];
    SfdHn *slots[8];
} SfdLib;

extern SfdLib DAT_004bea88;


void sfset_SetCondAll(int index, int value);
void sfset_SetUsrCond(SfdHn *hn, int index, int value);
int sfset_IsCondValid(SfdHn *hn, int index, int value);
void SFSET_GetTrHn(char *ctx, int index, int *out);

int SFD_GetSvrStat(void)
{
    return SFPLY_DecideSvrStat();
}

int SFD_GetHnStat(void *sfd)
{
    SfdHn *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        sfd_ReportError(0, 0xFF000111);
    }
    return hn->state;
}

int SFD_SetCond(void *sfd, int index, int value)
{
    SfdHn *hn = sfd;
    if (hn == 0) {
        sfset_SetCondAll(index, value);
        sfd_lib[index] = value;
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
    SfdHn **slots = DAT_004bea88.slots;
    int i;
    for (i = 0; i < 8; i++) {
        if (slots[i] != 0) {
            SFSET_SetCond(slots[i], index, value);
        }
    }
}

void SFSET_SetCond(void *sfd, int index, int value)
{
    SfdHn *hn = sfd;
    if (sfset_IsCondValid(hn, index, value) != 0) {
        hn->cond[index] = value;
    }
}

void sfset_SetUsrCond(SfdHn *hn, int index, int value)
{
    if (sfset_IsCondValid(hn, index, value) != 0) {
        hn->cond2[index] = value;
    }
}

int sfset_IsCondValid(SfdHn *hn, int index, int value)
{
    if (index == 6 && value == 1 && SFTRN_IsSetup(hn, 3) == 0) {
        return 0;
    }
    if (index == 5 && value == 1 && SFTRN_IsSetup(hn, 2) == 0) {
        return 0;
    }
    return 1;
}

int SFD_GetCond(void *sfd, int index, int *out)
{
    SfdHn *hn = sfd;
    if (hn == 0) {
        *out = sfd_lib[index];
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
    SfdHn *hn = sfd;
    return hn->cond[index];
}

int SFD_GetMvInf(void *sfd, SfdMvInf *out)
{
    SfdHn *hn = sfd;
    int r = SFLIB_CheckHn(hn);
    if (r != 0) {
        return sfd_ReportError(0, 0xFF000114);
    }
    *out = hn->mvInf;
    return r;
}

int SFD_GetPlyInf(void *sfd, SfdPlyInf *out)
{
    SfdHn *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000119);
    }
    *out = hn->plyInf;
    return 0;
}


int SFD_GetTmrInf(SfdHn *hn, SfdReport *report)
{
    int i;

    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00011A);
    }
    *report = hn->report;
    for (i = 1; i < 4; i++) {
        report->stat[0].sum += report->stat[i].sum;
        report->stat[0].min = (report->stat[i].min < report->stat[0].min) ? report->stat[i].min : report->stat[0].min;
        report->stat[0].max = (report->stat[0].max < report->stat[i].max) ? report->stat[i].max : report->stat[0].max;
        report->stat[0].count += report->stat[i].count;
    }
    return 0;
}

int SFD_GetTrHn(void *sfd, int index, int *out)
{
    SfdHn *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000117);
    }
    SFSET_GetTrHn((char *)hn, index, out);
    return 0;
}

void SFSET_GetTrHn(char *ctx, int index, int *out)
{
    int *value = ((SfdEntryRef *)(ctx + index * 0x44))->value;
    if (value == 0) {
        *out = 0;
        return;
    }
    *out = *value;
}

int SFD_GetSofdecHeader(SfdHn *hn, char **data, int *size)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00011C);
    }
    if (hn->f120 != 0) {
        *data = hn->f268;
        *size = hn->f264;
    } else {
        *data = 0;
        *size = 0;
    }
    return 0;
}
