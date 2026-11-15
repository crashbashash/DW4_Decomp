/* alarm.c - the kernel patch that adds the alarm system calls on kernels without them. */
#include "dw4/libkernl.h"

#define ALARM_PATCH_ADDR ((void *)0x80076000)
#define ALARM_PATCH_SIZE 0x740
/* the null program the patch leaves at 0x82000 */
#define EENULL_ADDR ((void *)0x82000)
#define EENULL_SIZE 0x28

/* a kernel with the alarm calls built in runs them on timer 3, its compare interrupt enabled */
#define T3_MODE (*(volatile int *)0x10001810)
#define T_MODE_CMPE 0x100

static int kCopy(int *dst, int *src, unsigned int size);

/* the kernel code that adds the alarm calls (src/sony/libkernl/kpatch/srcfile.c, alarmuser.S) */
static unsigned char srcfile[ALARM_PATCH_SIZE] = {
#include "srcfile.inc"
};

/* the user-mode side of an alarm handler (src/sony/libkernl/kpatch/eenull.S) */
static unsigned char eenull[EENULL_SIZE] = {
#include "eenull.inc"
};

/* the calls InitAlarm installs: Copy's kernel side, the patch's lookup as call 91, then the patch's own calls,
 * each at the address the patch's lookup gives */
static SyscallEntry SysEntry_alarm[8] = {
    {0x5a, kCopy},
    {0x5b, ALARM_PATCH_ADDR},
    {0xfc, 0},
    {0xfe, 0},
    {0xfd, 0},
    {0xff, 0},
    {0x12c, 0},
    {8, 0},
};

/* SetSyscall */
static void setup(int number, void *handler)
{
    __asm__("li $3, 116\n\tsyscall");
}

/* system call 90: a copy into kernel memory */
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

void InitAlarm(void)
{
    unsigned int i;
    if (!(T3_MODE & T_MODE_CMPE)) {
        setup(SysEntry_alarm[0].number, SysEntry_alarm[0].handler);
        Copy(ALARM_PATCH_ADDR, srcfile, ALARM_PATCH_SIZE);
        Copy(EENULL_ADDR, eenull, EENULL_SIZE);
        FlushCache(0);
        FlushCache(2);
        setup(SysEntry_alarm[1].number, SysEntry_alarm[1].handler);
        for (i = 2; i < 8; i++) {
            setup(SysEntry_alarm[i].number, GetEntryAddress(SysEntry_alarm[i].number));
        }
    }
}
