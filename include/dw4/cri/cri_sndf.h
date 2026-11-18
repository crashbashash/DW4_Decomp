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

int SNDF_Init(int *prm);
int SNDF_Finish(void);
int SNDF_Start(void);
int SNDF_Stop(void);
int SNDF_SetPortSizes(SndfTables *tables);
int SNDF_LoadBank(unsigned int channel, struct SndfBank *bank);
int SNDF_StartTransfer(unsigned int channel, struct SndfBank *bank);
int SNDF_LoadIopBank(unsigned int channel, int iopAddr);
int SNDF_OpenPort(unsigned int channel);
int SNDF_FreePort(unsigned int channel);
int SNDF_SendSysMessage(unsigned int message);
int SNDF_GetControl(unsigned int channel, int kind);
int SNDF_GetCtrlChange(unsigned int channel, int part, int kind);
int SNDF_GetPlayStatus(unsigned int channel);
int SNDF_GetEvent(void);
int SNDF_GetErrorMessage(void);
int SNDF_GetProcTime(void);
void SNDF_GetPortSizes(int *tblSize, int *pcmSize);
void SNDF_GetEffect(unsigned char *bank, unsigned char *preset);
void SNDF_GetVoiceCount(int *first, int *second, int *third, int *fourth);
void SNDF_GetQueueCount(int *eeQueued, int *iopQueued);
void SNDF_ClearQueue(void);
void SNDF_SetCallback(void (*func)(int arg, int event));
int SNDF_GetOutputMode(void);
int SNDF_GetSoundStatus(int id);
int SNDF_SeqCommand(unsigned int cmd, unsigned char id, int value);
int SNDF_GetTransferStatus(unsigned int channel);
void SNDF_ExecServer(void);
int SNDF_SendControl(unsigned int channel, unsigned int cmd, int value);
int SNDF_SetMasterParam(unsigned int base, unsigned int value);

#ifdef __cplusplus
}
#endif

#endif
