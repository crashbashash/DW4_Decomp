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
int sfd_CheckHn(SfdUsrHn *h);
int SFD_GetCond(SfdUsrHn *h, int option);
int FUN_002b0338(SfdUsrHn *h, int group, int event, int a, int b);
void FUN_002b0388(SfdUsrHn *h, int flag, int value);
int sftrn_GetFlagA(SfdUsrHn *h, int flag);
void FUN_002b03b8(SfdUsrHn *h, int flag, int value);
int sftrn_GetFlagB(SfdUsrHn *h, int flag);
int FUN_0029ea48(SfdUsrHn *h, int index);
int FUN_0029ea88(SfdUsrHn *h, int index);

int FUN_0029d188(SfdUsrHn *h);
void FUN_0029d1b8(SfdUsrHn *h);
void FUN_0029d228(SfdUsrHn *h);
void FUN_0029d2d8(SfdUsrIf *iface);

void FUN_0029cee8(SfdUsrHn *h, int a, int b) {
    if (sfd_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A1);
        return;
    }
    if (SFD_GetCond(h, 6) != 0) {
        h->iface->f4(h, a, b);
    }
}

int FUN_0029cf78(SfdUsrHn *h, int a) {
    if (sfd_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A2);
        return 0;
    }
    if (SFD_GetCond(h, 6) == 0) {
        return 0;
    }
    return h->iface->f8(h, a);
}

void FUN_0029cff0(SfdUsrHn *h, int a) {
    if (sfd_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A3);
        return;
    }
    if (SFD_GetCond(h, 6) != 0) {
        h->iface->f12(h, a);
    }
}

int FUN_0029d070(SfdUsrHn *h) {
    if (sfd_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF0001A4);
        return 0;
    }
    if (SFD_GetCond(h, 6) == 0) {
        return 0;
    }
    return h->iface->f16(h);
}

void FUN_0029d0e0(SfdUsrHn *h, int a) {
    void (*fn)(SfdUsrHn *, int);
    if (SFD_GetCond(h, 6) != 0) {
        fn = h->iface->f20;
        if (fn != 0) {
            fn(h, a);
        }
    }
}

int FUN_0029d138(void) {
    return 0;
}

int FUN_0029d140(void) {
    return 0;
}

void FUN_0029d148(SfdUsrHn *h) {
    if (SFD_GetCond(h, 6) != 0) {
        FUN_0029d188(h);
    }
}

int FUN_0029d188(SfdUsrHn *h) {
    FUN_0029d1b8(h);
    FUN_0029d228(h);
    return 0;
}

void FUN_0029d1b8(SfdUsrHn *h) {
    if (sftrn_GetFlagA(h, 7) != 1 && FUN_0029ea48(h, h->stream) == 1) {
        FUN_002b0388(h, 7, 1);
    }
}

void FUN_0029d228(SfdUsrHn *h) {
    if (sftrn_GetFlagB(h, 7) != 1 && FUN_0029ea88(h, h->stream) == 1) {
        FUN_002b03b8(h, 7, 1);
    }
}

int FUN_0029d298(SfdUsrHn *h) {
    int result = SFD_GetCond(h, 6);
    SfdUsrIf *iface = &h->ifaceStorage;
    if (result != 0) {
        h->iface = iface;
        FUN_0029d2d8(iface);
        result = 0;
    }
    return result;
}

void FUN_0029d2d8(SfdUsrIf *iface) {
}

int FUN_0029d2e0(void) {
    return 0;
}

int FUN_0029d2e8(SfdUsrHn *h) {
    if (SFD_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 5, 0, 0);
    }
}

int FUN_0029d330(SfdUsrHn *h) {
    if (SFD_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 6, 0, 0);
    }
}

int FUN_0029d378(SfdUsrHn *h) {
    if (SFD_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 7, 0, 0);
    }
}

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int FUN_0029d3c0(SfdUsrHn *h, int value) {
    if (SFD_GetCond(h, 6) != 0) {
        FUN_002b0338(h, 3, 8, value, 0);
    }
}

void FUN_0029d418(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void FUN_0029d438(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void FUN_0029d458(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

void FUN_0029d478(SfdUsrHn *h) {
    sfd_ReportError(h, 0xFF000A01);
}

int FUN_0029d498(void) {
    return 0;
}
