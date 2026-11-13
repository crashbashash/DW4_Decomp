/* The header info word logged for the current picture (ring slot logPos % 8); 0 before any is logged. */
#include "dw4/cri/mwply.h"

int mwply_GetLogHdrInfo(MwsfdPly *ply, int slot);

int mwply_GetCurPicHdrInfo(MwsfdPly *ply)
{
    int slot = ply->logPos % 8;

    if (ply->log[slot].valid == 0)
        return 0;
    return mwply_GetLogHdrInfo(ply, slot);
}
