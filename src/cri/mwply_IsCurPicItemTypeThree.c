/* The item-type-3 flag logged for the current picture (ring slot logPos % 8); 0 before any is logged. */
#include "dw4/cri/mwply.h"

int mwply_GetLogItemTypeThree(MwsfdPly *ply, int slot);

int mwply_IsCurPicItemTypeThree(MwsfdPly *ply)
{
    int slot = ply->logPos % 8;

    if (ply->log[slot].valid == 0)
        return 0;
    return mwply_GetLogItemTypeThree(ply, slot);
}
