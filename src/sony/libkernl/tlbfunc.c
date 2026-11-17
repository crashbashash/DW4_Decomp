/* tlbfunc.c - the TLB: the refill and debug exception hooks, the kernel patch that adds the TLB system
 * calls, and the initial TLB of a 32 MB machine. */
#include "dw4/sony/libkernl.h"

/* EE exception codes routed through _kTLBException and _kDebugException */
#define EXC_TLB_MOD 1
#define EXC_TLB_COUNT 3
#define EXC_COUNT 13

#define TLB_ENTRIES 48
#define TLB_USER_FIRST 13
#define TLB_USER_COUNT (TLB_ENTRIES - TLB_USER_FIRST)

/* where the TLB patch is copied in kernel memory */
#define TLB_PATCH_ADDR ((void *)0x80075000)
#define TLB_PATCH_SIZE 0x330

#define EXTENDED_MEMORY 0x02000000

typedef unsigned int u_int;

/* one TLB entry: PageMask, EntryHi, EntryLo0, EntryLo1 */
typedef u_int TlbEntry[4];

typedef struct {
    int nkernel;
    int ndefault;
    int nextend;
    int wired;
    TlbEntry *kernel;
    TlbEntry *deflt;
    TlbEntry *extend;
} TlbInfo;

void *SetVTLBRefillHandler(int cause, void *handler);
void *SetVCommonHandler(int cause, void *handler);
void _kTLBException(void);
void _kExitTLBHandler(void);
void _kDebugException(void);
int GetMemorySize(void);
int _InitTLB(void);

static int kCopy(int *dst, int *src, unsigned int size);
static int InitTLB32MB(void);

/* the kernel code that adds the TLB system calls (src/sony/libkernl/kpatch/tlbsrc.c) */
static unsigned char tlbsrc[TLB_PATCH_SIZE] = {
#include "tlbsrc.inc"
};

void *_kTLBRefillHandler = 0;
void *_kDebugHandler[16] = {0};
char *_kExecArg = 0;

/* the calls InitTLBFunctions installs: Copy's kernel side, the patch's lookup as call 91, the TLB handler's
 * exit, then the patch's own calls, each at the address the patch's lookup gives */
static SyscallEntry SysEntry_tlbfunc[8] = {
    {0x5a, kCopy},
    {0x5b, TLB_PATCH_ADDR},
    {0x54, _kExitTLBHandler},
    {0x55, 0},
    {0x56, 0},
    {0x57, 0},
    {0x58, 0},
    {0x59, 0},
};

/* the scratchpad, the kernel's page and the hardware registers: wired */
static TlbEntry kernelTLB[13] = {
    {0x00000000, 0x70000000, 0x80000007, 0x00000007},
    {0x00006000, 0xffff8000, 0x00001e1f, 0x00001f1f},
    {0x00000000, 0x10000000, 0x00400017, 0x00400053},
    {0x00000000, 0x10002000, 0x00400097, 0x004000d7},
    {0x00000000, 0x10004000, 0x00400117, 0x00400157},
    {0x00000000, 0x10006000, 0x00400197, 0x004001d7},
    {0x00000000, 0x10008000, 0x00400217, 0x00400257},
    {0x00000000, 0x1000a000, 0x00400297, 0x004002d7},
    {0x00000000, 0x1000c000, 0x00400313, 0x00400357},
    {0x00000000, 0x1000e000, 0x00400397, 0x004003d7},
    {0x0001e000, 0x11000000, 0x00440017, 0x00440415},
    {0x0001e000, 0x12000000, 0x00480017, 0x00480415},
    {0x01ffe000, 0x1e000000, 0x00780017, 0x007c0017},
};

/* main memory from 0x80000 to 32 MB, cached at 0x00080000 and uncached at 0x20080000 */
static TlbEntry defaultTLB[18] = {
    {0x0007e000, 0x00080000, 0x0000201f, 0x0000301f},
    {0x0007e000, 0x00100000, 0x0000401f, 0x0000501f},
    {0x0007e000, 0x00180000, 0x0000601f, 0x0000701f},
    {0x001fe000, 0x00200000, 0x0000801f, 0x0000c01f},
    {0x001fe000, 0x00400000, 0x0001001f, 0x0001401f},
    {0x001fe000, 0x00600000, 0x0001801f, 0x0001c01f},
    {0x007fe000, 0x00800000, 0x0002001f, 0x0003001f},
    {0x007fe000, 0x01000000, 0x0004001f, 0x0005001f},
    {0x007fe000, 0x01800000, 0x0006001f, 0x0007001f},
    {0x0007e000, 0x20080000, 0x00002017, 0x00003017},
    {0x0007e000, 0x20100000, 0x00004017, 0x00005017},
    {0x0007e000, 0x20180000, 0x00006017, 0x00007017},
    {0x001fe000, 0x20200000, 0x00008017, 0x0000c017},
    {0x001fe000, 0x20400000, 0x00010017, 0x00014017},
    {0x001fe000, 0x20600000, 0x00018017, 0x0001c017},
    {0x007fe000, 0x20800000, 0x00020017, 0x00030017},
    {0x007fe000, 0x21000000, 0x00040017, 0x00050017},
    {0x007fe000, 0x21800000, 0x00060017, 0x00070017},
};

/* the same memory uncached accelerated at 0x30100000, mapped by InitTLB32MB */
static TlbEntry extendTLB[8] = {
    {0x0007e000, 0x30100000, 0x0000403f, 0x0000503f},
    {0x0007e000, 0x30180000, 0x0000603f, 0x0000703f},
    {0x001fe000, 0x30200000, 0x0000803f, 0x0000c03f},
    {0x001fe000, 0x30400000, 0x0001003f, 0x0001403f},
    {0x001fe000, 0x30600000, 0x0001803f, 0x0001c03f},
    {0x007fe000, 0x30800000, 0x0002003f, 0x0003003f},
    {0x007fe000, 0x31000000, 0x0004003f, 0x0005003f},
    {0x007fe000, 0x31800000, 0x0006003f, 0x0007003f},
};

TlbInfo TLBInfo = {13, 18, 8, 0, kernelTLB, defaultTLB, extendTLB};

void *SetTLBHandler(void *handler)
{
    _kTLBRefillHandler = handler;
    SetVTLBRefillHandler(1, _kTLBException);
    SetVTLBRefillHandler(2, _kTLBException);
    SetVTLBRefillHandler(3, _kTLBException);
    return handler;
}

/* Route EE exception `cause` to `handler` through the common debug entry; returns the handler it replaces. */
void *SetDebugHandler(int cause, void *handler)
{
    void *old;
    if ((unsigned int)(cause - EXC_TLB_MOD) >= EXC_COUNT) {
        return (void *)0xffffffff;
    }
    old = _kDebugHandler[cause];
    _kDebugHandler[cause] = handler;
    if ((unsigned int)(cause - EXC_TLB_MOD) < EXC_TLB_COUNT) {
        SetVTLBRefillHandler(cause, _kDebugException);
    } else {
        SetVCommonHandler(cause, _kDebugException);
    }
    return old;
}

/* system call 90 once kCopy is installed: a copy into kernel memory */
static int Copy(void *dst, void *src, int size)
{
    __asm__("li $3, 90\n\tsyscall");
}

static int kCopy(int *dst, int *src, unsigned int size)
{
    unsigned int i;
    size >>= 2;
    for (i = 0; i < size; i++) {
        *dst = *src;
        src++;
        dst++;
    }
    return 0;
}

/* the kernel's handler of system call `number` */
static void *GetEntryAddress(int number)
{
    __asm__("li $3, 91\n\tsyscall");
}

/* SetSyscall */
static void setup(int number, void *handler)
{
    __asm__("li $3, 116\n\tsyscall");
}

void InitTLBFunctions(void)
{
    unsigned int i;
    setup(SysEntry_tlbfunc[0].number, SysEntry_tlbfunc[0].handler);
    Copy(TLB_PATCH_ADDR, tlbsrc, TLB_PATCH_SIZE);
    FlushCache(0);
    FlushCache(2);
    setup(SysEntry_tlbfunc[1].number, SysEntry_tlbfunc[1].handler);
    setup(SysEntry_tlbfunc[2].number, SysEntry_tlbfunc[2].handler);
    for (i = 3; i < 8; i++) {
        setup(SysEntry_tlbfunc[i].number, GetEntryAddress(SysEntry_tlbfunc[i].number));
    }
    _kExecArg = GetEntryAddress(3);
}

int PutTLBEntry(u_int pagemask, u_int hi, u_int lo0, u_int lo1)
{
    __asm__("li $3, 85\n\tsyscall");
}

int iPutTLBEntry(u_int pagemask, u_int hi, u_int lo0, u_int lo1)
{
    __asm__("li $3, -85\n\tsyscall");
}

static int _SetTLBEntry(int index, u_int pagemask, u_int hi, u_int lo0, u_int lo1)
{
    __asm__("li $3, 86\n\tsyscall");
}

/* Sets one of the TLB entries left to the program; the kernel's and the wired ones are refused. */
int SetTLBEntry(int index, u_int pagemask, u_int hi, u_int lo0, u_int lo1)
{
    int result;
    if ((unsigned int)(index - TLB_USER_FIRST) >= TLB_USER_COUNT) {
        result = -1;
    } else {
        result = _SetTLBEntry(index, pagemask, hi, lo0, lo1);
    }
    return result;
}

int iSetTLBEntry(int index, u_int pagemask, u_int hi, u_int lo0, u_int lo1)
{
    __asm__("li $3, -86\n\tsyscall");
}

int GetTLBEntry(int index, u_int *pagemask, u_int *hi, u_int *lo0, u_int *lo1)
{
    __asm__("li $3, 87\n\tsyscall");
}

int iGetTLBEntry(int index, u_int *pagemask, u_int *hi, u_int *lo0, u_int *lo1)
{
    __asm__("li $3, -87\n\tsyscall");
}

int ProbeTLBEntry(u_int hi, u_int *pagemask, u_int *lo0, u_int *lo1)
{
    __asm__("li $3, 88\n\tsyscall");
}

int iProbeTLBEntry(u_int hi, u_int *pagemask, u_int *lo0, u_int *lo1)
{
    __asm__("li $3, -88\n\tsyscall");
}

int ExpandScratchPad(u_int page)
{
    __asm__("li $3, 89\n\tsyscall");
}

int InitTLB(void)
{
    int r;
    if (GetMemorySize() == EXTENDED_MEMORY) {
        r = InitTLB32MB();
    } else {
        r = _InitTLB();
    }
    return r;
}

static int InitTLB32MB(void)
{
    register int i asm("$25");
    int n;
    int j;
    TlbEntry *e;
    kprintf("# TLB spad=0 kernel=1:%d default=%d:%d extended=%d:%d\n", TLBInfo.nkernel - 1, TLBInfo.nkernel,
                 TLBInfo.nkernel + TLBInfo.ndefault - 1, TLBInfo.nkernel + TLBInfo.ndefault,
                 TLBInfo.nkernel + TLBInfo.ndefault + TLBInfo.nextend - 1);
    __asm__("mtc0 $0, $6\n\tsync.p");
    i = 0;
    n = TLBInfo.nkernel;
    if (n > TLB_ENTRIES) {
        kprintf("# TLB over flow (1)");
        Exit(1);
    }
    for (e = TLBInfo.kernel; i < n; i++, e++)
        _SetTLBEntry(i, (*e)[0], (*e)[1], (*e)[2], (*e)[3]);
    n = i + TLBInfo.ndefault;
    if (n > TLB_ENTRIES) {
        kprintf("# TLB over flow (2)");
        Exit(1);
    }
    for (e = TLBInfo.deflt; i < n; i++, e++)
        _SetTLBEntry(i, (*e)[0], (*e)[1], (*e)[2], (*e)[3]);
    TLBInfo.wired = i;
    __asm__("mtc0 %0, $6\n\tsync.p" : : "r"(i));
    if (TLBInfo.nextend > 0) {
        n = i + TLBInfo.nextend;
        if (n > TLB_ENTRIES) {
            kprintf("# TLB over flow (3)");
            Exit(1);
        }
        for (e = TLBInfo.extend; i < n; i++, e++)
            _SetTLBEntry(i, (*e)[0], (*e)[1], (*e)[2], (*e)[3]);
    }
    /* the unused entries map nothing: each gets its own unmapped EntryHi */
    for (j = i; j < TLB_ENTRIES; j++)
        _SetTLBEntry(j, 0, 0xe0000000 + (j << 13), 0, 0);
    return i;
}
