typedef struct SfdInfo64 {
    char c[64];
} SfdInfo64;

typedef struct SfdStatus160 {
    long words[20];
} SfdStatus160;

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
    SfdInfo64 info;
    char pad2380[2384 - 2380];
    SfdStatus160 status;
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

extern int sfd_lib[];
typedef struct SfdLib {
    int counter;
    int f4;
    int rate;
    char pad12[84 - 12];
    SfdHn *slots[8];
} SfdLib;

extern SfdLib DAT_004bea88;

int sfd_ReportError();
int SFLIB_CheckHn(SfdHn *hn);
int SFPLY_DecideSvrStat();
int FUN_002b03e8(SfdHn *hn, int check);

void sfset_SetCondAll(int index, int value);
void SFSET_SetCond(SfdHn *hn, int index, int value);
void sfset_SetUsrCond(SfdHn *hn, int index, int value);
int sfset_IsCondValid(SfdHn *hn, int index, int value);
int SFSET_GetCond(SfdHn *hn, int index);
void FUN_002adf48(char *ctx, int index, int *out);

void SFD_GetSvrStat(void)
{
    SFPLY_DecideSvrStat();
}

int SFD_GetHnStat(SfdHn *hn)
{
    if (SFLIB_CheckHn(hn) != 0) {
        sfd_ReportError(0, 0xFF000111);
    }
    return hn->state;
}

int SFD_SetCond(SfdHn *hn, int index, int value)
{
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

void SFSET_SetCond(SfdHn *hn, int index, int value)
{
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
    if (index == 6 && value == 1 && FUN_002b03e8(hn, 3) == 0) {
        return 0;
    }
    if (index == 5 && value == 1 && FUN_002b03e8(hn, 2) == 0) {
        return 0;
    }
    return 1;
}

int SFD_GetCondDef(SfdHn *hn, int index, int *out)
{
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

int SFSET_GetCond(SfdHn *hn, int index)
{
    return hn->cond[index];
}

int SFD_GetHnHdrInf(SfdHn *hn, SfdInfo64 *out)
{
    int r = SFLIB_CheckHn(hn);
    if (r != 0) {
        return sfd_ReportError(0, 0xFF000114);
    }
    *out = hn->info;
    return r;
}

int SFD_GetPlyInf(SfdHn *hn, SfdStatus160 *out)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000119);
    }
    *out = hn->status;
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

int SFD_GetTrHn(SfdHn *hn, int index, int *out)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000117, out);
    }
    FUN_002adf48((char *)hn, index, out);
    return 0;
}

void FUN_002adf48(char *ctx, int index, int *out)
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
