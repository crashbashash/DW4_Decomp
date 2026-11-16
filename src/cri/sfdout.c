/* The output handler of stream graph slot 6: the application reads the buffer channel the slot is
 * linked to through its GetRead and AddRead entries, gated by the time block; writing is not
 * supported (0xFF000701). */

int sfd_ReportError();
int SFSET_GetCond();
int SFBUF_VfrmGetRead();
int SFBUF_VfrmAddRead();
int SFBUF_GetPrepFlg();
int SFBUF_GetTermFlg();
int SFTIM_IsGetFrmTime();
int SFTIM_IsVideoTerm();
int sftrn_SetFlagA();
int sftrn_SetFlagB();
int sftrn_GetFlagA();
int sftrn_GetFlagB();

#define SFOUT_SLOT 6

/* One 0x44-byte entry of the stream graph at handle +7976. */
typedef struct SfoutTrn {
    char pad0[16];
    int from;         /* the buffer channel the slot reads */
    char pad20[0x44 - 20];
} SfoutTrn;

typedef struct SfoutHn {
    char pad0[72];
    int stat;         /* 3 and 4: playing */
    char pad76[7976 - 76];
    SfoutTrn trn[9];
} SfoutHn;

int sfvom_IsTerm(SfoutHn *hn);
int sfvom_IsPrepEnd(SfoutHn *hn);
int sfvom_OutputServer(SfoutHn *hn);
void sfvom_ChkTermFlg(SfoutHn *hn);
void sfvom_ChkPrepFlg(SfoutHn *hn);

int SFVOM_Init(void) {
    return 0;
}

int SFVOM_Finish(void) {
    return 0;
}

int SFVOM_ExecServer(SfoutHn *hn) {
    int result;

    if (SFSET_GetCond(hn, 5) == 0) {
        return 0;
    }
    sfvom_ChkTermFlg(hn);
    result = sfvom_OutputServer(hn);
    sfvom_ChkPrepFlg(hn);
    return result;
}

void sfvom_ChkTermFlg(SfoutHn *hn) {
    if (sftrn_GetFlagB(hn, SFOUT_SLOT) != 1 && SFBUF_GetTermFlg(hn, hn->trn[SFOUT_SLOT].from) == 1
        && sfvom_IsTerm(hn) != 0) {
        sftrn_SetFlagB(hn, SFOUT_SLOT, 1);
    }
}

int sfvom_IsTerm(SfoutHn *hn) {
    if (SFSET_GetCond(hn, 15) == 0) {
        return 1;
    }
    return SFTIM_IsVideoTerm(hn) != 0;
}

void sfvom_ChkPrepFlg(SfoutHn *hn) {
    if (sftrn_GetFlagA(hn, SFOUT_SLOT) != 1 && SFBUF_GetPrepFlg(hn, hn->trn[SFOUT_SLOT].from) == 1
        && sfvom_IsPrepEnd(hn) != 0) {
        sftrn_SetFlagA(hn, SFOUT_SLOT, 1);
    }
}

int sfvom_IsPrepEnd(SfoutHn *hn) {
    return 1;
}

int sfvom_OutputServer(SfoutHn *hn) {
    return 0;
}

int SFVOM_Create(void) {
    return 0;
}

int SFVOM_Destroy(void) {
    return 0;
}

int SFVOM_Standby(void) {
    return 0;
}

int SFVOM_Start(void) {
    return 0;
}

int SFVOM_Stop(void) {
    return 0;
}

int SFVOM_Pause(void) {
    return 0;
}

void SFVOM_GetWrite(SfoutHn *hn) {
    sfd_ReportError(hn, 0xFF000701);
}

void SFVOM_AddWrite(SfoutHn *hn) {
    sfd_ReportError(hn, 0xFF000701);
}

/* Only while playing, and only data whose time has come. */
int SFVOM_GetRead(SfoutHn *hn, int *data) {
    int result;

    if ((unsigned int)(hn->stat - 3) >= 2) {
        *data = 0;
        return 0;
    }
    result = SFBUF_VfrmGetRead(hn, hn->trn[SFOUT_SLOT].from, data);
    if (result != 0) {
        return result;
    }
    result = SFTIM_IsGetFrmTime(hn, *data);
    if (result == 0) {
        *data = 0;
        return result;
    }
    return 0;
}

void SFVOM_AddRead(SfoutHn *hn, int size) {
    SFBUF_VfrmAddRead(hn, hn->trn[SFOUT_SLOT].from, size);
}

int SFVOM_Seek(void) {
    return 0;
}
