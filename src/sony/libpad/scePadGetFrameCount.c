typedef struct {
    unsigned char data[32];
    int actDirData[8];
    unsigned char actData[6][4];
    int frame;
    int findPadRetries;
    int length;
    unsigned char modeConfig;
    unsigned char modeInfo[6];
    unsigned char nrOfActuators;
    unsigned char reserved[6];
    unsigned char currentTask;
    unsigned char reserved2[13];
} PadDmaData;
typedef struct {
    PadDmaData *padData;
    int reserved[3];
    int open;
    int reserved2[2];
} PadPortState;
extern PadPortState padState[2][4];
PadDmaData *padGetDmaStr(int port, int slot);

int scePadGetFrameCount(int port, int slot) {
    if (padState[port][slot].open == 0) return 0;
    return padGetDmaStr(port, slot)->frame;
}
