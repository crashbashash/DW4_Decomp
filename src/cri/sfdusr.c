typedef struct SfdUsrHn SfdUsrHn;

typedef struct SfdUsrIf {
    void (*init)(void);                              /* 0 */
    void (*f4)(SfdUsrHn *h, int a, int b);           /* 4 */
    int (*f8)(SfdUsrHn *h, int a);                   /* 8 */
    void (*f12)(SfdUsrHn *h, int a);                 /* 12 */
    int (*f16)(SfdUsrHn *h);                         /* 16 */
    void (*f20)(SfdUsrHn *h, int a);                 /* 20 */
} SfdUsrIf;

struct SfdUsrHn {
    char pad0[8460];
    SfdUsrIf *iface;          /* 8460 */
    char pad8464[4];
    int stream;               /* 8468 */
    char pad8472[5308];
    SfdUsrIf ifaceStorage;    /* 13780 */
};

int sfd_ReportError();
int SFLIB_CheckHn(SfdUsrHn *h);
int SFSET_GetCond(SfdUsrHn *h, int option);
int FUN_002b0338(SfdUsrHn *h, int group, int event, int a, int b);
void sftrn_SetFlagA(SfdUsrHn *h, int flag, int value);
int sftrn_GetFlagA(SfdUsrHn *h, int flag);
void sftrn_SetFlagB(SfdUsrHn *h, int flag, int value);
int sftrn_GetFlagB(SfdUsrHn *h, int flag);
int SFBUF_GetPrepFlg(SfdUsrHn *h, int index);
int SFBUF_GetTermFlg(SfdUsrHn *h, int index);

int sfaoap_OutputServer(SfdUsrHn *h);
void sfaoap_ChkPrepFlg(SfdUsrHn *h);
void sfaoap_ChkTermFlg(SfdUsrHn *h);
void sfaoap_InitInf(SfdUsrIf *iface);

void SFD_SetOutPan(SfdUsrHn *h, int a, int b) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A1);
        return;
    }
    if (SFSET_GetCond(h, 6) != 0) {
        h->iface->f4(h, a, b);
    }
}

int SFD_GetOutPan(SfdUsrHn *h, int a) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A2);
        return 0;
    }
    if (SFSET_GetCond(h, 6) == 0) {
        return 0;
    }
    return h->iface->f8(h, a);
}

void SFD_SetOutVol(SfdUsrHn *h, int a) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A3);
        return;
    }
    if (SFSET_GetCond(h, 6) != 0) {
        h->iface->f12(h, a);
    }
}

int SFD_GetOutVol(SfdUsrHn *h) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A4);
        return 0;
    }
    if (SFSET_GetCond(h, 6) == 0) {
        return 0;
    }
    return h->iface->f16(h);
}

void SFAOAP_SetSpeed(SfdUsrHn *h, int a) {
    void (*fn)(SfdUsrHn *, int);
    if (SFSET_GetCond(h, 6) != 0) {
        fn = h->iface->f20;
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

void SFAOAP_ExecServer(SfdUsrHn *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        sfaoap_OutputServer(h);
    }
}

int sfaoap_OutputServer(SfdUsrHn *h) {
    sfaoap_ChkPrepFlg(h);
    sfaoap_ChkTermFlg(h);
    return 0;
}

void sfaoap_ChkPrepFlg(SfdUsrHn *h) {
    if (sftrn_GetFlagA(h, 7) != 1 && SFBUF_GetPrepFlg(h, h->stream) == 1) {
        sftrn_SetFlagA(h, 7, 1);
    }
}

void sfaoap_ChkTermFlg(SfdUsrHn *h) {
    if (sftrn_GetFlagB(h, 7) != 1 && SFBUF_GetTermFlg(h, h->stream) == 1) {
        sftrn_SetFlagB(h, 7, 1);
    }
}

int SFAOAP_Create(SfdUsrHn *h) {
    int result = SFSET_GetCond(h, 6);
    SfdUsrIf *iface = &h->ifaceStorage;
    if (result != 0) {
        h->iface = iface;
        sfaoap_InitInf(iface);
        result = 0;
    }
    return result;
}

void sfaoap_InitInf(SfdUsrIf *iface) {
}

int SFAOAP_Destroy(void) {
    return 0;
}

int SFAOAP_Standby(SfdUsrHn *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 5, 0, 0);
    }
}

int SFAOAP_Start(SfdUsrHn *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 6, 0, 0);
    }
}

int SFAOAP_Stop(SfdUsrHn *h) {
    if (SFSET_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 7, 0, 0);
    }
}

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int SFAOAP_Pause(SfdUsrHn *h, int value) {
    if (SFSET_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 8, value, 0);
    }
}

void SFAOAP_GetWrite(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void SFAOAP_AddWrite(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void SFAOAP_GetRead(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void SFAOAP_AddRead(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

int SFAOAP_Seek(void) {
    return 0;
}
