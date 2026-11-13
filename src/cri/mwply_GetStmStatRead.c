/* The read status of the player's file stream, or else of the stream of its link stream controller;
 * 0 without a handle or a stream. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/lsc.h"

int MWSTM_GetStatRead(void *stm);

int mwply_GetStmStatRead(MwsfdPly *ply) {
    void *stm;
    LscObj *lsc;

    if (ply == 0) {
        return 0;
    }
    stm = ply->stm;
    lsc = ply->lsc;
    if (stm == 0) {
        if (lsc == 0) {
            return 0;
        }
        return lsc->stm ? MWSTM_GetStatRead(lsc->stm) : 0;
    }
    return MWSTM_GetStatRead(stm);
}
