/* The output handler of stream graph slot 6: the application reads the buffer channel the slot is
 * linked to through its GetRead and AddRead entries, gated by the time block; writing is not
 * supported (0xFF000701). */
#include "dw4/cri/sfd.h"
#include "dw4/cri/sfdply.h"


#define SFOUT_SLOT 6

int sfvom_IsTerm(SfdPly *hn);
int sfvom_IsPrepEnd(SfdPly *hn);
int sfvom_OutputServer(SfdPly *hn);
void sfvom_ChkTermFlg(SfdPly *hn);
void sfvom_ChkPrepFlg(SfdPly *hn);

int SFVOM_Init(void) {
    return 0;
}

int SFVOM_Finish(void) {
    return 0;
}

int SFVOM_ExecServer(SfdPly *hn) {
    int result;

    if (SFSET_GetCond(hn, 5) == 0) {
        return 0;
    }
    sfvom_ChkTermFlg(hn);
    result = sfvom_OutputServer(hn);
    sfvom_ChkPrepFlg(hn);
    return result;
}

void sfvom_ChkTermFlg(SfdPly *hn) {
    if (SFTRN_GetTermFlg(hn, SFOUT_SLOT) != 1 && SFBUF_GetTermFlg(hn, hn->trn[SFOUT_SLOT].bufIn) == 1
        && sfvom_IsTerm(hn) != 0) {
        SFTRN_SetTermFlg(hn, SFOUT_SLOT, 1);
    }
}

int sfvom_IsTerm(SfdPly *hn) {
    if (SFSET_GetCond(hn, 15) == 0) {
        return 1;
    }
    return SFTIM_IsVideoTerm(hn) != 0;
}

void sfvom_ChkPrepFlg(SfdPly *hn) {
    if (SFTRN_GetPrepFlg(hn, SFOUT_SLOT) != 1 && SFBUF_GetPrepFlg(hn, hn->trn[SFOUT_SLOT].bufIn) == 1
        && sfvom_IsPrepEnd(hn) != 0) {
        SFTRN_SetPrepFlg(hn, SFOUT_SLOT, 1);
    }
}

int sfvom_IsPrepEnd(SfdPly *hn) {
    return 1;
}

int sfvom_OutputServer(SfdPly *hn) {
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

void SFVOM_GetWrite(SfdPly *hn) {
    sfd_ReportError(hn, 0xFF000701);
}

void SFVOM_AddWrite(SfdPly *hn) {
    sfd_ReportError(hn, 0xFF000701);
}

/* Only while playing, and only data whose time has come. */
int SFVOM_GetRead(SfdPly *hn, SfdFrameInfo **data) {
    int result;

    if ((unsigned int)(hn->stat - 3) >= 2) {
        *data = 0;
        return 0;
    }
    result = SFBUF_VfrmGetRead(hn, hn->trn[SFOUT_SLOT].bufIn, data);
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

void SFVOM_AddRead(SfdPly *hn, SfdFrameInfo *frm) {
    SFBUF_VfrmAddRead(hn, hn->trn[SFOUT_SLOT].bufIn, frm);
}

int SFVOM_Seek(void) {
    return 0;
}
