/* The output handler of stream graph slot 6: the application reads the buffer channel the slot is
 * linked to through its GetRead and AddRead entries, gated by the time block; writing is not
 * supported (0xFF000701). */

int sfd_ReportError();
int SFD_GetCond();
int sfbuf_GetRead();
int sfbuf_AddRead();
int sfbuf_GetFlagA();
int sfbuf_GetFlagB();
int sftim_IsSpanReached();
int sftim_IsReady();
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

int sfout_IsWriteReady(SfoutHn *hn);
int sfout_IsReadReady(SfoutHn *hn);
int sfout_Exec(SfoutHn *hn);
void sfout_UpdateWrite(SfoutHn *hn);
void sfout_UpdateRead(SfoutHn *hn);

int sfout_InitFn(void) {
    return 0;
}

int sfout_FinishFn(void) {
    return 0;
}

int sfout_ExecServer(SfoutHn *hn) {
    int result;

    if (SFD_GetCond(hn, 5) == 0) {
        return 0;
    }
    sfout_UpdateWrite(hn);
    result = sfout_Exec(hn);
    sfout_UpdateRead(hn);
    return result;
}

void sfout_UpdateWrite(SfoutHn *hn) {
    if (sftrn_GetFlagB(hn, SFOUT_SLOT) != 1 && sfbuf_GetFlagB(hn, hn->trn[SFOUT_SLOT].from) == 1
        && sfout_IsWriteReady(hn) != 0) {
        sftrn_SetFlagB(hn, SFOUT_SLOT, 1);
    }
}

int sfout_IsWriteReady(SfoutHn *hn) {
    if (SFD_GetCond(hn, 15) == 0) {
        return 1;
    }
    return sftim_IsReady(hn) != 0;
}

void sfout_UpdateRead(SfoutHn *hn) {
    if (sftrn_GetFlagA(hn, SFOUT_SLOT) != 1 && sfbuf_GetFlagA(hn, hn->trn[SFOUT_SLOT].from) == 1
        && sfout_IsReadReady(hn) != 0) {
        sftrn_SetFlagA(hn, SFOUT_SLOT, 1);
    }
}

int sfout_IsReadReady(SfoutHn *hn) {
    return 1;
}

int sfout_Exec(SfoutHn *hn) {
    return 0;
}

int sfout_CreateFn(void) {
    return 0;
}

int sfout_DestroyFn(void) {
    return 0;
}

int sfout_StartFn(void) {
    return 0;
}

int sfout_StopFn(void) {
    return 0;
}

int sfout_PauseFn(void) {
    return 0;
}

int sfout_SeekFn(void) {
    return 0;
}

void sfout_GetWriteFn(SfoutHn *hn) {
    sfd_ReportError(hn, 0xFF000701);
}

void sfout_AddWriteFn(SfoutHn *hn) {
    sfd_ReportError(hn, 0xFF000701);
}

/* Only while playing, and only data whose time has come. */
int sfout_GetReadFn(SfoutHn *hn, int *data) {
    int result;

    if ((unsigned int)(hn->stat - 3) >= 2) {
        *data = 0;
        return 0;
    }
    result = sfbuf_GetRead(hn, hn->trn[SFOUT_SLOT].from, data);
    if (result != 0) {
        return result;
    }
    result = sftim_IsSpanReached(hn, *data);
    if (result == 0) {
        *data = 0;
        return result;
    }
    return 0;
}

void sfout_AddReadFn(SfoutHn *hn, int size) {
    sfbuf_AddRead(hn, hn->trn[SFOUT_SLOT].from, size);
}

int sfout_TermFn(void) {
    return 0;
}
