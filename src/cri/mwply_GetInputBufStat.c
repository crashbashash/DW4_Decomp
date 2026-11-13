/* Reports the player's SFD input buffer: the first chunk's address and length and the length
 * of the tail. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/sfdsj.h"

void SFD_GetInputBufStat(void *sfd, SfdBufStat *stat);

void mwply_GetInputBufStat(MwsfdPly *ply, char **data, int *len, int *tailLen) {
    SfdBufStat stat;

    SFD_GetInputBufStat(ply->sfd, &stat);
    *data = stat.ck0.data;
    *len = stat.ck0.len;
    *tailLen = stat.tailLen;
}
