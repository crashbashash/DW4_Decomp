/* CRI SNDF: the sound-data transfer library's public calls (starting and stopping it, and the server the
 * game runs each frame). */
#ifndef DW4_CRI_CRI_SNDF_H
#define DW4_CRI_CRI_SNDF_H

#ifdef __cplusplus
extern "C" {
#endif

int SNDF_Start(void);
int SNDF_Finish(void);
void SNDF_ExecServer(void);

#ifdef __cplusplus
}
#endif

#endif
