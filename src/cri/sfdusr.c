#include "dw4/cri/sfd.h"
#include "dw4/cri/sfdply.h"


int sfaoap_OutputServer(SfdPly *h);
void sfaoap_ChkPrepFlg(SfdPly *h);
void sfaoap_ChkTermFlg(SfdPly *h);
void sfaoap_InitInf(SfdAoap *iface);

void SFD_SetOutPan(void *sfd, int a, int b) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A1);
        return;
    }
    if (SFSET_GetCond(h, 6) != 0) {
        h->trn[7].hn.aoap->setOutPan(h, a, b);
    }
}

int SFD_GetOutPan(void *sfd, int a) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A2);
        return 0;
    }
    if (SFSET_GetCond(h, 6) == 0) {
        return 0;
    }
    return h->trn[7].hn.aoap->getOutPan(h, a);
}

void SFD_SetOutVol(void *sfd, int a) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A3);
        return;
    }
    if (SFSET_GetCond(h, 6) != 0) {
        h->trn[7].hn.aoap->setOutVol(h, a);
    }
}

int SFD_GetOutVol(void *sfd) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A4);
        return 0;
    }
    if (SFSET_GetCond(h, 6) == 0) {
        return 0;
    }
    return h->trn[7].hn.aoap->getOutVol(h);
}

void SFAOAP_SetSpeed(void *sfd, int a) {
    SfdPly *h = sfd;
    void (*fn)(SfdPly *, int);
    if (SFSET_GetCond(h, 6) != 0) {
        fn = h->trn[7].hn.aoap->setSpeed;
        if (fn != 0) {
            fn(h, a);
        }
    }
}

int SFAOAP_Init(void) {
    return 0;
}

int SFAOAP_Finish(void) {
    return 0;
}

void SFAOAP_ExecServer(SfdPly *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        sfaoap_OutputServer(h);
    }
}

int sfaoap_OutputServer(SfdPly *h) {
    sfaoap_ChkPrepFlg(h);
    sfaoap_ChkTermFlg(h);
    return 0;
}

void sfaoap_ChkPrepFlg(SfdPly *h) {
    if (SFTRN_GetPrepFlg(h, 7) != 1 && SFBUF_GetPrepFlg(h, h->trn[7].bufIn) == 1) {
        SFTRN_SetPrepFlg(h, 7, 1);
    }
}

void sfaoap_ChkTermFlg(SfdPly *h) {
    if (SFTRN_GetTermFlg(h, 7) != 1 && SFBUF_GetTermFlg(h, h->trn[7].bufIn) == 1) {
        SFTRN_SetTermFlg(h, 7, 1);
    }
}

int SFAOAP_Create(SfdPly *h) {
    int result = SFSET_GetCond(h, 6);
    SfdAoap *iface = &h->aoap;
    if (result != 0) {
        h->trn[7].hn.aoap = iface;
        sfaoap_InitInf(iface);
        result = 0;
    }
    return result;
}

void sfaoap_InitInf(SfdAoap *iface) {
}

int SFAOAP_Destroy(void) {
    return 0;
}

int SFAOAP_Standby(SfdPly *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        SFTRN_CallTrtTrif(h, 3, 5, 0, 0);
    }
}

int SFAOAP_Start(SfdPly *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        SFTRN_CallTrtTrif(h, 3, 6, 0, 0);
    }
}

int SFAOAP_Stop(SfdPly *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        SFTRN_CallTrtTrif(h, 3, 7, 0, 0);
    }
}

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int SFAOAP_Pause(SfdPly *h, int value) {
    if (SFSET_GetCond(h, 6) != 0) {
        SFTRN_CallTrtTrif(h, 3, 8, value, 0);
    }
}

void SFAOAP_GetWrite(SfdPly *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void SFAOAP_AddWrite(SfdPly *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void SFAOAP_GetRead(SfdPly *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void SFAOAP_AddRead(SfdPly *h) {
    sfd_ReportError(h, 0xFF000A01);
}

int SFAOAP_Seek(void) {
    return 0;
}
