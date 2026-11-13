/* libosd.c - the kernel patch for ExecPS2 on consoles whose kernel needs it. */
#include "dw4/libkernl.h"

#define OSD_PATCH_ADDR ((void *)0x80074000)
#define OSD_PATCH_SIZE 0x7a8

/* the OSD configuration word's 3-bit field at bit 13: kernels that keep it there are already patched */
#define OSD_PATCH_FIELD_SHIFT 13
#define OSD_PATCH_FIELD (7 << OSD_PATCH_FIELD_SHIFT)

void GetOsdConfigParam(void *param);
int SetOsdConfigParam(void *param);

extern char osdsrc[OSD_PATCH_SIZE];
extern SyscallEntry SysExecPS2Entry[3];

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

/* An unpatched kernel drops a value written to the configuration field. */
static int PatchIsNeeded(void)
{
    unsigned int saved;
    unsigned int probe;
    GetOsdConfigParam(&saved);
    probe = (saved & ~OSD_PATCH_FIELD) | (1 << OSD_PATCH_FIELD_SHIFT);
    SetOsdConfigParam(&probe);
    GetOsdConfigParam(&probe);
    SetOsdConfigParam(&saved);
    return ((probe >> OSD_PATCH_FIELD_SHIFT) & 7) == 0;
}

void InitExecPS2(void)
{
    unsigned int i;
    if (PatchIsNeeded() != 0) {
        setup(SysExecPS2Entry[0].number, SysExecPS2Entry[0].handler);
        Copy(OSD_PATCH_ADDR, osdsrc, OSD_PATCH_SIZE);
        FlushCache(0);
        FlushCache(2);
        setup(SysExecPS2Entry[1].number, SysExecPS2Entry[1].handler);
        for (i = 2; i < 3; i++) {
            setup(SysExecPS2Entry[i].number, GetEntryAddress(SysExecPS2Entry[i].number));
        }
    }
}
