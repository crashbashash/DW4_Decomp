/* osdsrc.c - the ExecPS2 kernel patch. Linked to run at 0x80074000, where libosd.c copies it, it replaces
 * the kernel's OSD configuration calls and its ExecPS2. */
#include "dw4/libkernl_patch.h"

typedef unsigned int u_int;
typedef unsigned char u_char;
typedef unsigned long u_long;

typedef struct {
    u_int spdifMode : 1;
    u_int screenType : 2;
    u_int videoOutput : 1;
    u_int japLanguage : 1;
    u_int ps1drvConfig : 8;
    u_int version : 3;
    struct {
        unsigned short language : 5;
        unsigned short timezoneOffset : 11;
    } locale;
} OsdConfigParam;

/* the system configuration the boot ROM keeps, read through the pointer at ROM offset 0x3c0 */
typedef union {
    u_long eegs;
    u_char data[40];
} SystemConfig;

/* a kernel thread's control block */
typedef struct Tcb {
    struct Tcb *next;
    struct Tcb *prev;
    int status;
    void *entry;
    void *stackTop;
    void *gp;
    short currentPriority;
    short initPriority;
    int waitType;
    int semaId;
    int wakeupCount;
    int attr;
    int option;
    void *entry2;
    int argc;
    char *args;
    void *stack;
    int stackSize;
    void *root;
    void *heapBase;
} Tcb;

#define MAX_THREADS 256
#define THS_DORMANT 16
#define SYSTEM_CONFIG_SIZE 38
#define CONFIG2_SIZE 128
#define EXECPS2_HOOK 0xffffc402
#define JAL_OPCODE 0x0c000000

#define I_STAT ((volatile u_int *)0x1000f000)
#define INTC_VBLANK_START 4

void kSetOsdConfigParam(OsdConfigParam *config);
void kGetOsdConfigParam(OsdConfigParam *config);
void kSetOsdConfigParam2(void *config, u_int size, u_int offset);
int kGetOsdConfigParam2(void *config, u_int size, u_int offset);
void *kExecPS2(void *entry, void *gp, int argc, char **argv);
static void ReadSystemConfig();

SystemConfig systemConfig = {0x40};

/* the kernel's own routines and variables this patch uses, at their addresses in the boot ROM's kernel */
int *currentThreadId = (int *)0x800125ec;
int *currentThreadStatus = (int *)0x800125f4;
int (*CancelWakeupThread)(int tid) = (void *)0x80004970;
int (*ChangeThreadPriority)(int tid, int priority) = (void *)0x80004288;
int (*InitPgifHandler)(void) = (void *)0x800021b0;
int (*InitSemaphores)(void) = (void *)0x80004e68;
int (*DeleteThread)(int tid) = (void *)0x80003f00;
int (*TerminateThread)(int tid) = (void *)0x80003e00;
Tcb *threads = (Tcb *)0x80017400;
void (*InitIntc)(int mask) = (void *)0x8000b8d0;
void (*InitTimer)(void) = (void *)0x8000b900;
void (*InitFpu)(void) = (void *)0x8000b7a8;
void (*InitScratchPad)(void) = (void *)0x8000b840;
void (*ResetEE)(int mask) = (void *)0x8000ad68;
void (*InitGs)(void) = (void *)0x8000aa60;
void (*SetGsCrt)(short interlace, short mode, short field) = (void *)0x8000a060;
void (*FlushDCache)(void) = (void *)0x80002a80;
void (*FlushICache)(void) = (void *)0x80002ac0;
char *(*AppendArg)(char *dst, const char *src) = (void *)0x80005560;
void *unusedKernelWord = (void *)0x80012600;
char *argBuffer = (char *)0x80012608;

SyscallEntry entries[5] = {
    {0x4a, kSetOsdConfigParam},
    {0x4b, kGetOsdConfigParam},
    {0x6e, kSetOsdConfigParam2},
    {0x6f, kGetOsdConfigParam2},
    {EXECPS2_HOOK, kExecPS2},
};

static OsdConfigParam osdConfig;
static u_char osdConfig2[CONFIG2_SIZE];

/* system call 91 while the patch is installed; for ExecPS2 the kernel wants the `jal` that calls the
 * replacement */
void *kGetEntryAddress(int number)
{
    u_int i;
    ReadSystemConfig(&systemConfig, SYSTEM_CONFIG_SIZE);
    for (i = 0; i < 5; i++) {
        if (number == entries[i].number) {
            if (number == EXECPS2_HOOK) {
                return (void *)((((u_int)entries[i].handler >> 2) & 0x3ffffff) | JAL_OPCODE);
            }
            return entries[i].handler;
        }
    }
    return 0;
}

void kGetOsdConfigParam(OsdConfigParam *config)
{
    config->spdifMode = osdConfig.spdifMode;
    config->screenType = osdConfig.screenType;
    config->videoOutput = osdConfig.videoOutput;
    config->japLanguage = osdConfig.japLanguage;
    config->ps1drvConfig = osdConfig.ps1drvConfig;
    config->version = osdConfig.version;
    config->locale = osdConfig.locale;
}

void kSetOsdConfigParam(OsdConfigParam *config)
{
    osdConfig.spdifMode = config->spdifMode;
    osdConfig.screenType = config->screenType;
    osdConfig.videoOutput = config->videoOutput;
    osdConfig.japLanguage = config->japLanguage;
    osdConfig.ps1drvConfig = config->ps1drvConfig;
    osdConfig.version = config->version;
    osdConfig.locale = config->locale;
}

static void ReadSystemConfig()
{
    u_char *rom;
    u_char *config;
    int i;
    rom = *(u_char **)0xbc0003c0;
    if (rom != 0) {
        rom += 0xbc000000;
        rom += 15;
        config = systemConfig.data;
        for (i = 0; i < SYSTEM_CONFIG_SIZE; i++) {
            config[i] = rom[i];
        }
    }
    if (((int)(systemConfig.eegs >> 6) & 7) == 0) {
        systemConfig.eegs &= ~(1UL << 40);
        systemConfig.eegs &= ~(3UL << 42);
        systemConfig.eegs &= ~(15UL << 44);
    }
}

/* GetOsdConfigParam2: copies `size` bytes from `offset` of the 128-byte extended configuration, clipped to its
 * end, and returns the system configuration's 4-bit field at bit 44 when its 3-bit field at bit 6 is nonzero */
int kGetOsdConfigParam2(void *config, u_int size, u_int offset)
{
    u_int i, j;
    if (size + offset > CONFIG2_SIZE) {
        if (offset < CONFIG2_SIZE) {
            size = CONFIG2_SIZE - offset;
        } else {
            offset = CONFIG2_SIZE;
            size = 0;
        }
    }
    for (i = 0, j = offset; j < size + offset; i++, j++) {
        ((u_char *)config)[i] = osdConfig2[j];
    }
    if (((int)(systemConfig.eegs >> 6) & 7) == 0) {
        return 0;
    }
    return (int)(systemConfig.eegs >> 44) & 0xf;
}

/* SetOsdConfigParam2: the store side of GetOsdConfigParam2, with the same clip */
void kSetOsdConfigParam2(void *config, u_int size, u_int offset)
{
    u_int i, j;
    if (size + offset > CONFIG2_SIZE) {
        if (offset < CONFIG2_SIZE) {
            size = CONFIG2_SIZE - offset;
        } else {
            offset = CONFIG2_SIZE;
            size = 0;
        }
    }
    for (i = 0, j = offset; j < size + offset; i++, j++) {
        osdConfig2[j] = ((u_char *)config)[i];
    }
}

static void ResetPeripherals(void)
{
    *I_STAT = INTC_VBLANK_START;
    while ((*I_STAT & INTC_VBLANK_START) == 0) {
    }
    *I_STAT = INTC_VBLANK_START;
    InitGs();
    SetGsCrt(1, 2, 1);
    InitIntc(0xdffd);
    InitTimer();
    ResetEE(0x7f);
    InitFpu();
    InitScratchPad();
}

void *kExecPS2(void *entry, void *gp, int argc, char **argv)
{
    int tid, i;
    char *args;

    tid = *currentThreadId;
    CancelWakeupThread(tid);
    ChangeThreadPriority(tid, 0);
    for (i = 1; i < MAX_THREADS; i++) {
        if (threads[i].status != 0 && i != tid) {
            if (threads[i].status == THS_DORMANT) {
                DeleteThread(i);
            } else {
                TerminateThread(i);
                DeleteThread(i);
            }
        }
    }
    InitSemaphores();
    InitPgifHandler();
    *currentThreadStatus = 0;
    ResetPeripherals();
    args = argBuffer;
    for (i = 0; i < argc; i++) {
        args = AppendArg(args, argv[i]);
    }
    threads[tid].entry = entry;
    threads[tid].entry2 = entry;
    threads[tid].gp = gp;
    threads[tid].initPriority = 0;
    threads[tid].currentPriority = 0;
    threads[tid].wakeupCount = 0;
    threads[tid].waitType = 0;
    threads[tid].semaId = 0;
    threads[tid].argc = argc;
    threads[tid].args = argBuffer;
    FlushICache();
    FlushDCache();
    return entry;
}
