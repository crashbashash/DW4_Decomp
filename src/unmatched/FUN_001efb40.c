typedef struct WaitSemaParam {
    int count;
    int maxCount;
    int initCount;
    int waitThreads;
    unsigned int attr;
    unsigned int option;
} WaitSemaParam;

int CreateSema(WaitSemaParam *param);
void FUN_001efce0(void);
void FUN_001eff40(void);
void FUN_001ef9b0(int channel);
extern WaitSemaParam DAT_00490d00;
extern WaitSemaParam DAT_00490d20;
extern int DAT_00490b60;
extern int DAT_00490c70;
extern int DAT_00490c74;
extern int DAT_00490c78;
extern int DAT_00490c7c;
extern int DAT_00490c80;
extern int DAT_00490c84;
extern int DAT_00490cc0;
extern int DAT_00569030;
extern int DAT_00569090;
extern int DAT_00569094;
extern int DAT_00569098;
extern unsigned char DAT_005690a0[4];
extern unsigned char GPR_00554bbc;
extern int DAT_00569190;

/* matching construct: a small sweep of spellings */
void FUN_001efb40(void)
{
    WaitSemaParam completion = DAT_00490d00;
    WaitSemaParam lock = DAT_00490d20;

    if (DAT_00490b60 != 0) {
        DAT_00569030 = CreateSema(&completion);
        DAT_00569090 = 0;
        DAT_00569094 = CreateSema(&lock);
        DAT_00569098 = CreateSema(&lock);
    }
    DAT_00490c74 = 64;
    DAT_00490c7c = 320;
    DAT_00490c84 = 96;
    GPR_00554bbc = 0;
    DAT_005690a0[0] = 0;
    DAT_005690a0[1] = 0;
    DAT_005690a0[2] = 0;
    if (DAT_00490c70 == -1) DAT_00490c70 = 256;
    if (DAT_00490c78 == -1) DAT_00490c78 = 2048;
    if (DAT_00490c80 == -1) DAT_00490c80 = 256;
    FUN_001efce0();
    FUN_001eff40();
    FUN_001ef9b0(1);
    FUN_001ef9b0(2);
    if (DAT_00490c70 != 0 && DAT_00490cc0 != 0) {
        FUN_001ef9b0(0);
    } else {
        DAT_00569190 = -1;
    }
    *(int *)0x1000e000 = 1;
}
