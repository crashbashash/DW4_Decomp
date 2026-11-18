#include "dw4/cri/sfdply.h"
#include "dw4/cri/sfd.h"


/* The supply module: the application writes the stream into the supply module's output channel
 * itself, so the handler only answers the write requests and marks the channel at each server call. */

int sfsup_Init(void) {
    return 0;
}

int sfsup_Finish(void) {
    return 0;
}

int sfsup_ExecServer(SfdPly *hn) {
    SFBUF_SetPrepFlg(hn, hn->trn[0].bufOut[0], 1);
    return 0;
}

int sfsup_Create(void) {
    return 0;
}

int sfsup_Destroy(void) {
    return 0;
}

int sfsup_Prep(void) {
    return 0;
}

int sfsup_Start(void) {
    return 0;
}

int sfsup_Stop(void) {
    return 0;
}

int sfsup_Pause(void) {
    return 0;
}

void sfsup_GetWrite(SfdPly *hn, SfdBufStat *stat) {
    SFBUF_RingGetWrite(hn, hn->trn[0].bufOut[0], stat);
}

void sfsup_AddWrite(SfdPly *hn, int len, int tail) {
    SFBUF_RingAddWrite(hn, hn->trn[0].bufOut[0], len, tail);
}

void sfsup_GetRead(SfdPly *hn) {
    sfd_ReportError(hn, 0xFF000501);
}

void sfsup_AddRead(SfdPly *hn) {
    sfd_ReportError(hn, 0xFF000501);
}

int sfsup_LoadRec(void) {
    return 0;
}
