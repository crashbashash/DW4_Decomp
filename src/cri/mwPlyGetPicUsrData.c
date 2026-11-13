/* Returns the player's current picture user data (pointer and size). */
#include "dw4/cri/mwply.h"

void mwPlyGetPicUsrData(MwsfdPly *ply, char **ud, int *udsize)
{
    char *data = ply->ud;
    int size = ply->udsize;

    *udsize = size;
    *ud = data;
}
