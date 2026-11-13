/* The composition mode logged for the current picture (ring slot logPos % 8); 17 before any is logged. */
#include "dw4/cri/mwply.h"

int mwply_GetLogCompoMode(MwsfdPly *ply, int slot);

int mwply_GetCurPicCompoMode(MwsfdPly *ply)
{
    int slot = ply->logPos % 8;

    if (ply->log[slot].valid == 0)
        return 17;
    return mwply_GetLogCompoMode(ply, slot);
}
