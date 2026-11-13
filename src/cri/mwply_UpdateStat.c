/* Server step of a player: starts a pending file read, checks whether preparation has finished,
 * and once SFD plays (its state 4 or 6) marks the player playing and applies the composition mode. */
#include "dw4/cri/mwply.h"

int MWSTM_ReqStart(MwsfdPly *ply);
void mwply_CheckPrepared(MwsfdPly *ply);
int SFD_GetHnStat(void *sfd);
void mwply_ApplyCompoMode(MwsfdPly *ply);

void mwply_UpdateStat(MwsfdPly *ply) {
    int stmReq = ply->stmReq;
    void *sfd = ply->sfd;
    int st;

    if (stmReq == 1 && MWSTM_ReqStart(ply) == stmReq) {
        ply->stmReq = 0;
    }
    mwply_CheckPrepared(ply);
    st = SFD_GetHnStat(sfd);
    if (st == 4 || st == 6) {
        ply->stat = 2;
        mwply_ApplyCompoMode(ply);
    }
}
