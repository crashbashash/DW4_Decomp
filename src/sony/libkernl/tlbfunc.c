/* tlbfunc.c - the TLB: the refill and debug exception hooks, the kernel patch that adds the TLB system
 * calls, and the initial TLB of a 32 MB machine. */
#include "dw4/libkernl.h"

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
void _kDebugException(void);
int GetMemorySize(void);
int _InitTLB(void);
int kprintf(const char *fmt, ...);
void Exit(int status);

extern void *_kTLBRefillHandler;
extern void *_kDebugHandler[16];
extern char *_kExecArg;
extern SyscallEntry SysEntry_tlbfunc[8];
extern char tlbsrc[TLB_PATCH_SIZE];
extern TlbInfo TLBInfo;

static int InitTLB32MB(void);

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
