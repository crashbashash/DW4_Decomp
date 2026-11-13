/* initsys.c - the library's start-up: its semaphores, the kernel's system call table, and every
 * part of libkernl that patches or starts something before main. */
#include "dw4/eekernel.h"
#include "dw4/libkernl.h"

/* the kernel memory searched for the system call table */
#define KSEG0_KERNEL ((int *)0x80000000)
#define KSEG0_KERNEL_END ((int *)0x80080000)

/* where kFindAddress and kCopy sit in the table, once installed as system calls 131 and 90 */
#define FIND_ADDRESS_SLOT_OFFSET 0x20c
#define COPY_SLOT_OFFSET 0x168

#define TIMER_CLOCK_BUSCLK_256 2

int InitThread(void);
void InitTLBFunctions(void);
void InitExecPS2(void);
void InitAlarm(void);
int InitTimer(int clock);
int StartTimerSystemTime(void);
void sceSifInitRebootNotify(void);

extern int __sce_sema_id;
extern int __sce_eh_sema_id;
extern int *_SyscallEntry;
extern SyscallEntry SysEntry_initsys[2];

static void supplement_crt0(void)
{
    struct SemaParam sema;
    struct SemaParam eh_sema;
    sema.maxCount = 1;
    sema.initCount = 1;
    eh_sema.maxCount = 1;
    eh_sema.initCount = 1;
    __sce_sema_id = CreateSema(&sema);
    __sce_eh_sema_id = CreateSema(&eh_sema);
}

int __sce_eh_sema_id_get(void)
{
    return __sce_eh_sema_id;
}

/* system call 90 once kCopy is installed: a copy out of kernel memory */
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

/* the first word from `p` up to `end` that holds `value`, or 0 */
static int *kFindAddress(int *p, int *end, int value)
{
    while (*p != value && p < end) {
        p++;
    }
    return p < end ? p : 0;
}

/* system call 131 once kFindAddress is installed */
static int *FindAddress(int *p, int *end, void *value)
{
    __asm__("li $3, 131\n\tsyscall");
}

/* the kernel's handler of system call `number`, read from its table */
void *GetSystemCallEntry(int number)
{
    void *entry;
    Copy(&entry, _SyscallEntry + number, 4);
    return entry;
}

static void setup(int number, void *handler);

/* Finds the system call table: the one place where kFindAddress and kCopy sit at their own slots. */
static void InitSystemCallTableAddress(void)
{
    int *find;
    int *copy;
    unsigned int find_table;
    unsigned int copy_table;
    setup(SysEntry_initsys[0].number, SysEntry_initsys[0].handler);
    setup(SysEntry_initsys[1].number, SysEntry_initsys[1].handler);
    find = FindAddress(KSEG0_KERNEL, KSEG0_KERNEL_END, kFindAddress);
    copy = FindAddress(KSEG0_KERNEL, KSEG0_KERNEL_END, kCopy);
    find_table = (unsigned int)find - FIND_ADDRESS_SLOT_OFFSET;
    copy_table = (unsigned int)copy - COPY_SLOT_OFFSET;
    while (find_table != copy_table) {
        if (find_table < copy_table) {
            find = FindAddress(find + 1, KSEG0_KERNEL_END, kFindAddress);
            find_table = (unsigned int)find - FIND_ADDRESS_SLOT_OFFSET;
        } else {
            copy = FindAddress(copy + 1, KSEG0_KERNEL_END, kCopy);
            copy_table = (unsigned int)copy - COPY_SLOT_OFFSET;
        }
    }
    _SyscallEntry = (int *)find_table;
}

/* SetSyscall */
static void setup(int number, void *handler)
{
    __asm__("li $3, 116\n\tsyscall");
}

void _InitSys(void)
{
    supplement_crt0();
    InitSystemCallTableAddress();
    InitAlarm();
    InitTimer(TIMER_CLOCK_BUSCLK_256);
    StartTimerSystemTime();
    InitThread();
    InitExecPS2();
    InitTLBFunctions();
    sceSifInitRebootNotify();
}
