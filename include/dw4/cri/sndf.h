#ifndef DW4_CRI_SNDF_H
#define DW4_CRI_SNDF_H

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

typedef struct SndfTables {
    int first[32];
    int second[32];
} SndfTables;

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

typedef struct SifDmaData {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} SifDmaData;

typedef struct SndfContext {
    char pad0[128];
    unsigned char channelOn[32];
    int base;
    SndfQueueEntry ring[128];
    unsigned char count;
    unsigned char writeIndex;
    unsigned char readIndex;
    signed char sending;
    unsigned char busy;
    char pad2729[3];
    int mode;
    int f2736;
    int open;
    int handle;
    SndfSlot slots[24];
    int state[32];
    int f2972[32];
    int error[32];
    int f3228[32];
    SndfTransfer transfers[32];
    int (*f5020)(int channel);
    void (*notify)(int a, int b);
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

typedef struct SifClientData {
    char pad0[36];
    void *serve;
} SifClientData;

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

typedef struct SndfStatus {
    unsigned char f0;
    unsigned char f1;
    unsigned short mask;
    int f4;
    unsigned char f8;
    unsigned char f9;
    char pad10[2];
    SndfVoice voices[32];
    SndfProgram programs[32][16];
    SndfParam params[61];
    SndfStream streams[16];
    char pad3456[12];
    SndfSlot slots[24];
    SndfPort ports[256];
    unsigned char f4588[32];
} SndfStatus;

extern int DAT_005717a0;
extern char *sndf_version;
extern int DAT_004bb100;
extern int DAT_004bb104;
extern int DAT_004bb108;
extern int DAT_004bb110;
extern SndfContext *sndf_ctx;
extern int DAT_004bb118[];
extern int DAT_00570c00[];
extern SndfOutbox DAT_00570d00;
extern SndfMessage DAT_00571740;
extern int DAT_00571700;
extern SifClientData DAT_00571750;
extern SifClientData DAT_00571778;
extern SndfStatus sndf_status;
extern SndfContext DAT_00572a00;

int sceSifCallRpc();
int sceSifCheckStatRpc();
int sceSifInitRpc();
int sceSifBindRpc();
void InvalidDCache(char *start, char *end);
void memset();
int sndf_CallRpc(int cmd, int *args, int n, int size);
void FUN_00280e38(void);
int SNDF_StartTransfer(unsigned int channel, SndfBank *bank);
void SyncDCache(char *start, char *end);
int sceSifDmaStat(unsigned int id);
unsigned int sceSifSetDma(SifDmaData *sdd, int len);
unsigned int sceSifQueryMaxFreeMemSize(void);
void *sceSifAllocIopHeap(int size);
int sceSifFreeIopHeap(void *addr);
int sceSdRemote(int arg, int command, ...);
int FUN_00281420(unsigned int channel, int *start, int *size);
int sndf_PushCommand(unsigned short kind, unsigned short arg, int a, int b, int c, int d);
int SNDF_GetTransferStatus(unsigned int channel);
void FUN_00281df0(unsigned int channel);
int sndf_SendMessage(unsigned int message);
void *memcpy();
void FUN_00281d80(SndfMessage *message);

#define SWAP32_A(x) (((x) << 24) | (((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00) | ((x) >> 24))
#define SWAP32_C(x) ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

#endif
