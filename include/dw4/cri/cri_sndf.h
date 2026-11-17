/* CRI SNDF: the sound-data transfer library's public calls (starting and stopping it, the server the game
 * runs each frame, the per-port bank transfers and the control messages). */
#ifndef DW4_CRI_CRI_SNDF_H
#define DW4_CRI_CRI_SNDF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Per port, the IOP space a bank needs: its table size and its PCM size. */
typedef struct SndfTables {
    int tblSize[32];
    int pcmSize[32];
} SndfTables;

struct SndfBank;

int SNDF_Start(void);
int SNDF_Finish(void);
void SNDF_ExecServer(void);
int SNDF_SetPortSizes(SndfTables *tables);
int SNDF_StartTransfer(unsigned int channel, struct SndfBank *bank);
int SNDF_FreePort(unsigned int channel);
int SNDF_SeqCommand(unsigned int cmd, unsigned char id, int value);
int SNDF_GetTransferStatus(unsigned int channel);
int SNDF_SendControl(unsigned int channel, unsigned int cmd, int value);
int SNDF_SetMasterParam(unsigned int base, unsigned int value);

#ifdef __cplusplus
}
#endif

#endif
