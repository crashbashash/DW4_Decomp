/* MWSFRNA: the MWSFD player's audio output. The output volume and pan of the movie's sound, passed
 * to SFD. */
#include "dw4/cri/mwply.h"

void SFD_SetOutPan(void *sfd, int ch, int pan);
int SFD_GetOutPan(void *sfd, int ch);
void SFD_SetOutVol(void *sfd, int vol);
int SFD_GetOutVol(void *sfd);

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
