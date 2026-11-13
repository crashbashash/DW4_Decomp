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

#define PAD_TASK_STABLE 1

/* Actuator info: -1 asks for the count, otherwise `cmd` -1..2 picks one of the actuator's four bytes. */
int scePadInfoAct(int port, int slot, int actuator, int cmd) {
    PadDmaData *pad;
    if (padState[port][slot].open == 0) return 0;
    pad = padGetDmaStr(port, slot);
    if (pad->currentTask != PAD_TASK_STABLE) return 0;
    if (pad->modeConfig < 2) return 0;
    if (actuator == -1) return pad->nrOfActuators;
    if (actuator >= pad->nrOfActuators) return 0;
    switch (cmd) {
    case -1:
        return pad->actData[actuator][0];
    case 0:
        return pad->actData[actuator][1];
    case 1:
        return pad->actData[actuator][2];
    case 2:
        return pad->actData[actuator][3];
    }
    return 0;
}
