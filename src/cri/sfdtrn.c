#include "dw4/cri/sfd.h"
#include "dw4/cri/sfdply.h"


int sftrn_CallTrEntry(SfdTrnModules *modules, int k);
void sftrn_InitTrData(SfdTrnSlot *slot, SfdTrnFn *fns);
int sftrn_BuildAll(SfdPly *hn, SfdTrnConfig *config);
void sftrn_BuildSystem(SfdPly *hn, SfdTrnConfig *config);
void sftrn_BuildVideo(SfdPly *hn, SfdTrnConfig *config);
void sftrn_BuildAudio(SfdPly *hn, SfdTrnConfig *config);
void sftrn_BuildUsr(SfdPly *hn, SfdTrnConfig *config);
void sftrn_ConnTrnBuf0(SfdPly *hn, int from, int to);
void sftrn_ConnTrnBufV(SfdPly *hn, int from, int to);
void sftrn_ConnTrnBufA(SfdPly *hn, int from, int to);
void sftrn_ConnTrnBufU(SfdPly *hn, int from, int to);
void sftrn_ConnTrnBuf(char *ctx, int from, int slot, int to);
void sftrn_ConnBufTrn(char *ctx, int from, int to);

int SFTRN_Init(SfdTrnModules *dst, SfdTrnModules *src)
{
    *dst = *src;
    return sftrn_CallTrEntry(src, 0);
}

int SFTRN_Finish(SfdTrnModules *modules)
{
    return sftrn_CallTrEntry(modules, 1);
}

int sftrn_CallTrEntry(SfdTrnModules *modules, int k)
{
    SfdTrnFn **tbl = modules->fns;
    int i;
    int r = 0;
    for (i = 0; i < 15; i++) {
        SfdTrnFn *t = *tbl++;
        if (t == 0) break;
        r = t[k](0, 0, 0, 0);
        if (r != 0) break;
    }
    return r;
}

void SFTRN_InitHn(void *sfd, SfdTrnSlot *s, SfdCrePrm *prm, int arg)
{
    SfdPly *hn = sfd;
    SfdTrnConfig *config = prm->trnConfig;
    int i;
    for (i = 0; i < 9; i++) {
        s[i].hn.obj = 0;
        sftrn_InitTrData(&s[i], config->fns[i]);
    }
    if (sftrn_BuildAll(hn, config) != 0) {
        sfd_ReportError(hn, 0xFF000302);
    }
}

void sftrn_InitTrData(SfdTrnSlot *slot, SfdTrnFn *fns)
{
    int i;
    slot->termFlg = 0;
    slot->prepFlg = 0;
    slot->fns = fns;
    slot->bufIn = 8;
    /* The three nops in the retail loop are the EE short-loop padding the toolchain inserts, not source. */
    for (i = 2; i >= 0; i--) {
        slot->bufOut[i] = 8;
    }
    slot->readTot = -1;
}

int sftrn_BuildAll(SfdPly *hn, SfdTrnConfig *config)
{
    if (config->fns[1] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 0);
        sftrn_BuildSystem(hn, config);
    } else if (config->fns[2] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 1);
        sftrn_BuildVideo(hn, config);
        SFSET_SetCond(hn, SFD_COND_AUDIO, 0);
        hn->cond2[SFD_COND_AUDIO] = 0;
    } else if (config->fns[3] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 2);
        sftrn_BuildAudio(hn, config);
        SFSET_SetCond(hn, SFD_COND_VIDEO, 0);
        hn->cond2[SFD_COND_VIDEO] = 0;
    } else if (config->fns[8] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 7);
        sftrn_BuildUsr(hn, config);
        SFSET_SetCond(hn, SFD_COND_AUDIO, 0);
        SFSET_SetCond(hn, SFD_COND_VIDEO, 0);
        hn->cond2[SFD_COND_AUDIO] = 0;
        hn->cond2[SFD_COND_VIDEO] = 0;
    } else {
        return -1;
    }
    return 0;
}

void sftrn_BuildSystem(SfdPly *hn, SfdTrnConfig *config)
{
    sftrn_ConnBufTrn((char *)hn, 0, 1);
    if (config->fns[2] != 0) {
        sftrn_ConnTrnBufV(hn, 1, 1);
        sftrn_BuildVideo(hn, config);
    } else {
        SFSET_SetCond(hn, SFD_COND_VIDEO, 0);
        hn->cond2[SFD_COND_VIDEO] = 0;
    }
    if (config->fns[3] != 0) {
        sftrn_ConnTrnBufA(hn, 1, 2);
        sftrn_BuildAudio(hn, config);
    } else {
        SFSET_SetCond(hn, SFD_COND_AUDIO, 0);
        hn->cond2[SFD_COND_AUDIO] = 0;
    }
    if (config->fns[8] != 0) {
        sftrn_ConnTrnBufU(hn, 1, 7);
        sftrn_BuildUsr(hn, config);
    }
}

void sftrn_BuildVideo(SfdPly *hn, SfdTrnConfig *config)
{
    sftrn_ConnBufTrn((char *)hn, 1, 2);
    sftrn_ConnTrnBuf0(hn, 2, 3);
    if (config->fns[4] != 0) {
        sftrn_ConnBufTrn((char *)hn, 3, 4);
        sftrn_ConnTrnBuf0(hn, 4, 5);
        sftrn_ConnBufTrn((char *)hn, 5, 6);
        return;
    }
    sftrn_ConnBufTrn((char *)hn, 3, 6);
}

void sftrn_BuildAudio(SfdPly *hn, SfdTrnConfig *config)
{
    sftrn_ConnBufTrn((char *)hn, 2, 3);
    sftrn_ConnTrnBuf0(hn, 3, 4);
    if (config->fns[5] != 0) {
        sftrn_ConnBufTrn((char *)hn, 4, 5);
        sftrn_ConnTrnBuf0(hn, 5, 6);
        sftrn_ConnBufTrn((char *)hn, 6, 7);
        return;
    }
    sftrn_ConnBufTrn((char *)hn, 4, 7);
}

void sftrn_BuildUsr(SfdPly *hn, SfdTrnConfig *config)
{
    sftrn_ConnBufTrn((char *)hn, 7, 8);
}

void sftrn_ConnTrnBuf0(SfdPly *hn, int from, int to)
{
    sftrn_ConnTrnBuf((char *)hn, from, 0, to);
}

void sftrn_ConnTrnBufV(SfdPly *hn, int from, int to)
{
    sftrn_ConnTrnBuf((char *)hn, from, 0, to);
}

void sftrn_ConnTrnBufA(SfdPly *hn, int from, int to)
{
    sftrn_ConnTrnBuf((char *)hn, from, 1, to);
}

void sftrn_ConnTrnBufU(SfdPly *hn, int from, int to)
{
    sftrn_ConnTrnBuf((char *)hn, from, 2, to);
}

void sftrn_ConnTrnBuf(char *ctx, int from, int slot, int to)
{
    int off44 = from * 0x44;
    ((SfdPly *)(ctx + off44))->trn[0].bufOut[slot] = to;
    /* matching construct: manual — advancing ctx in place reproduces retail's register reuse */
    ctx += to * 0x74;
    ((SfdPly *)ctx)->buf[0].inTr = from;
}

void sftrn_ConnBufTrn(char *ctx, int from, int to)
{
    /* matching construct: manual — byte offsets in int temporaries keep ctx as the first addu operand */
    int off44 = to * 0x44;
    int off74 = from * 0x74;
    ((SfdPly *)(ctx + off44))->trn[0].bufIn = from;
    ((SfdPly *)(ctx + off74))->buf[0].outTr = to;
}

int SFTRN_CallTrSetup(void *sfd, int k)
{
    SfdPly *hn = sfd;
    int i;
    int r = 0;
    SfdTrnSlot *s = hn->trn;
    for (i = 0; i < 9; i++) {
        SfdTrnFn *t = (s++)->fns;
        if (t == 0) continue;
        r = t[k](hn, 0, 0, 0);
        if (r != 0) break;
    }
    return r;
}

int SFTRN_CallTrtTrif(void *sfd, int index, int k, int a, int b)
{
    SfdPly *hn = sfd;
    SfdPly *p = (SfdPly *)((char *)hn + index * 0x44);
    SfdTrnFn *fns = p->trn[0].fns;
    if (fns == 0) {
        return 0;
    }
    return fns[k](hn, a, b, 0);
}

void SFTRN_SetPrepFlg(void *sfd, int index, int value)
{
    SfdPly *hn = sfd;
    hn = (SfdPly *)((char *)hn + index * 0x44);
    hn->trn[0].prepFlg = value;
}

int SFTRN_GetPrepFlg(void *sfd, int index)
{
    SfdPly *hn = sfd;
    hn = (SfdPly *)((char *)hn + index * 0x44);
    return hn->trn[0].prepFlg;
}

void SFTRN_SetTermFlg(void *sfd, int index, int value)
{
    SfdPly *hn = sfd;
    hn = (SfdPly *)((char *)hn + index * 0x44);
    hn->trn[0].termFlg = value;
}

int SFTRN_GetTermFlg(void *sfd, int index)
{
    SfdPly *hn = sfd;
    hn = (SfdPly *)((char *)hn + index * 0x44);
    return hn->trn[0].termFlg;
}

int SFTRN_IsSetup(void *sfd, int index)
{
    SfdPly *hn = sfd;
    hn = (SfdPly *)((char *)hn + index * 0x44);
    return hn->trn[0].fns != 0;
}
