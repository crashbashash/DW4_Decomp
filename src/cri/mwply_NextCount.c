/* Returns the player's counter advanced by one while it is below its limit, the counter itself
 * when it sits at the limit, and 0 when it has passed it. */
#include "dw4/cri/mwply.h"

int mwply_NextCount(MwsfdPly *ply)
{
    int limit = ply->limit;
    int count = ply->count;
    int next;

    if (count < limit)
        next = count + 1;
    else if (limit == count)
        next = count;
    else
        next = 0;
    return next;
}
