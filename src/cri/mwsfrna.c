/* MWSFRNA: the MWSFD player's audio output. The output volume and pan of the movie's sound, passed
 * to SFD. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/cri_mwsfd.h"
#include "dw4/cri/sfd.h"


void MWSFRNA_SetOutVol(MwsfdPly *ply, int vol)
{
    SFD_SetOutVol(ply->sfd, vol);
}

int MWSFRNA_GetOutVol(MwsfdPly *ply)
{
    return SFD_GetOutVol(ply->sfd);
}

void MWSFRNA_SetOutPan(MwsfdPly *ply, int ch, int pan)
{
    SFD_SetOutPan(ply->sfd, ch, pan);
}

int MWSFRNA_GetOutPan(MwsfdPly *ply, int ch)
{
    return SFD_GetOutPan(ply->sfd, ch);
}
