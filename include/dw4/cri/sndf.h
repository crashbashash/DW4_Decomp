#ifndef DW4_CRI_SNDF_H
#define DW4_CRI_SNDF_H

#include "dw4/cri/cri_sndf.h"

struct _sif_client_data;

typedef struct SndfQueueEntry {
    unsigned short kind;
    unsigned short arg;
    int a, b, c, d;
} SndfQueueEntry;

typedef struct SndfSlot {
    unsigned char used;
    unsigned char playing;
    char pad2[2];
} SndfSlot;

typedef struct SndfTransfer {
    char pad0[2];
    unsigned char state;
    char pad3[5];
    unsigned int bufferSize;
    char pad12[4];
    void *iopBuffer;  /* IOP heap block; a pointer, so its loads get their own alias set */
    char pad20[4];
    int spuAddr;
    char pad28[4];
    unsigned int remaining;
    char pad36[12];
    char *data;
} SndfTransfer;

typedef struct SndfBank {
    char pad0[12];
    int size;
    unsigned int headerSize;
    char pad20[4];
    unsigned int waveSize;
    int waveOffset;
} SndfBank;

/* The EE side of SNDF: the command queue the server call sends each frame, the sound slots, and the
 * per-port state of the bank uploads. */
typedef struct SndfContext {
    char pad0[128];
    unsigned char portOpen[32];
    int iopBase;  /* IOP address of the first port's table area, from command 0x100 */
    SndfQueueEntry ring[128];
    unsigned char count;
    unsigned char writeIndex;
    unsigned char readIndex;
    signed char sending;
    unsigned char sizesSet;
    char pad2729[3];
    int mode;
    int reserved;
    int transIdle;  /* the SPU voice transfer status: 1 when the last block has arrived */
    int statusResult;
    SndfSlot slots[24];
    int transferState[32];
    int transferMode[32];
    int transferResult[32];
    int transferPort[32];
    SndfTransfer transfers[32];
    int (*transferFunc)(int channel);
    void (*eventFunc)(int arg, int event);
    SndfTables tables;
} SndfContext;

typedef struct SndfMessage {
    int word[4];
} SndfMessage;

typedef struct SndfOutbox {
    SndfQueueEntry ring[128];
    unsigned int count;
    char pad2564[60];
} SndfOutbox;

typedef struct SndfVoice {
    char pad0[9];
    unsigned char f9;
    unsigned char f10;
    unsigned char f11;
    char pad12[4];
} SndfVoice;

typedef struct SndfProgram {
    unsigned char index;
    char pad1[3];
} SndfProgram;

typedef struct SndfParam {
    unsigned char a;
    unsigned char b;
    char pad2[2];
} SndfParam;

typedef struct SndfStream {
    char pad0[12];
    unsigned char flags;
    char pad13;
    unsigned char channel;
    char pad15[25];
} SndfStream;

typedef struct SndfPort {
    unsigned char f0;
    unsigned char state;
    unsigned char f2;
    unsigned char f3;
} SndfPort;

/* The status block the IOP side writes into EE memory each pass. */
typedef struct SndfStatus {
    unsigned char msgQueued;  /* messages from the EE still waiting on the IOP */
    unsigned char slotsRead;
    unsigned short mask;
    int procTime;  /* microseconds the IOP server's last pass took */
    unsigned char outputMode;
    unsigned char iopMsgQueued;  /* messages the IOP side queued itself */
    char pad10[2];
    SndfVoice voices[32];
    SndfProgram programs[32][16];
    SndfParam params[61];
    SndfStream streams[16];
    char pad3456[12];
    SndfSlot slots[24];
    SndfPort ports[256];
    unsigned char voiceCount[32];
    char pad4620[52];
} SndfStatus;

extern int sndf_rpc_init_flag;
extern char *sndf_version;
extern int sndf_rpc_busy;
extern int sndf_initialized;
extern int sndf_started;
extern int sndf_dma_channel;
extern SndfContext *sndf_ctx;
extern int sndf_pan_remap[180];  /* pan position remap of output mode 2 (the 0xA0002900 message) */
extern int sndf_rpc_buf[64];
extern SndfOutbox sndf_svr_sendbuf;
extern int sndf_svr_busy;
extern SndfMessage sndf_svr_recvbuf;
extern struct _sif_client_data sndf_cmd_client;  /* the IOP's SNDF command server */
extern struct _sif_client_data sndf_svr_client;  /* the IOP's SFSV server */
extern SndfStatus sndf_status;
extern SndfContext sndf_context;

unsigned int sceSifQueryMaxFreeMemSize(void);
int sndf_CallRpc(int cmd, int *args, int n, int size);
void sndf_InitContext(void);
int sndf_GetPortArea(unsigned int channel, int *tblAddr, int *spuAddr);
int sndf_PushCommand(unsigned short kind, unsigned short arg, int a, int b, int c, int d);
void sndf_ExecTransfer(unsigned int channel);
int sndf_SendMessage(unsigned int message);
void sndf_SvrCallback(void *reply);

#define SWAP32_A(x) (((x) << 24) | (((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00) | ((x) >> 24))
#define SWAP32_C(x) ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

#endif
