#include "dw4/cri/sfdhn.h"

int sfd_ReportError(SfdHandle *hn, int code);
int sfbuf_SetFlagA(SfdHandle *hn, int ch, int value);
void sfbuf_GetWriteStat(SfdHandle *hn, int ch, SfdBufStat *stat);
void sfbuf_AddWriteLen(SfdHandle *hn, int ch, int len, int tail);

/* The supply module: the application writes the stream into the supply module's output channel
 * itself, so the handler only answers the write requests and marks the channel at each server call. */

int sfsup_Init(void) {
    return 0;
}

int sfsup_Finish(void) {
    return 0;
}

int sfsup_ExecServer(SfdHandle *hn) {
    sfbuf_SetFlagA(hn, hn->sup.outputs[0], 1);
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

void sfsup_GetWrite(SfdHandle *hn, SfdBufStat *stat) {
    sfbuf_GetWriteStat(hn, hn->sup.outputs[0], stat);
}

void sfsup_AddWrite(SfdHandle *hn, int len, int tail) {
    sfbuf_AddWriteLen(hn, hn->sup.outputs[0], len, tail);
}

void sfsup_GetRead(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000501);
}

void sfsup_AddRead(SfdHandle *hn) {
    sfd_ReportError(hn, 0xFF000501);
}

int sfsup_LoadRec(void) {
    return 0;
}
