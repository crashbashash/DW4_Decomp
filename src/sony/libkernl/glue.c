/* glue.c - libkernl's newlib system-call glue: the console reads and writes through the DECI2 tty,
 * the heap grows up to EndOfHeap, files are unsupported. VSync waits on the INTC's vblank bit. */

#include "dw4/eekernel_intr.h"

/* newlib's struct stat with the EE's 64-bit long */
struct stat {
    short st_dev;
    short st_ino;
    int st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    short st_rdev;
    long st_size;
    long st_atime;
    long st_spare1;
    long st_mtime;
    long st_spare2;
    long st_ctime;
    long st_spare3;
    long st_blksize;
    long st_blocks;
    long st_spare4[2];
};

#define S_IFCHR 0x2000
#define EIO 5
#define ENOMEM 12

/* INTC_STAT; writing a cause bit clears it */
#define INTC_STAT (*(volatile int *)0x1000f000)
#define INTC_VBLANK_START 4

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int DIntr(void);
int EIntr(void);
void SetVSyncFlag(int *flag, unsigned long *time);
void *EndOfHeap(void);
int sceTtyInit(void);
int sceTtyRead(void *buf, int size);
int sceTtyWrite(void *buf, int size);
int *__errno(void);
void Exit(int status);

extern char _end[];

static int ttyinit = 0;

void sceResetttyinit(void)
{
    ttyinit = 0;
}

void VSync(void)
{
    int interrupts = DIntr();
    INTC_STAT = INTC_VBLANK_START;
    __asm__("sync");
    if (interrupts) EIntr();
    while ((INTC_STAT & INTC_VBLANK_START) == 0) {
    }
    interrupts = DIntr();
    INTC_STAT = INTC_VBLANK_START;
    __asm__("sync");
    if (interrupts) EIntr();
}

/* VSync that also returns the time the kernel stamped at the vblank */
unsigned long VSync2(void)
{
    int interrupts;
    volatile struct {
        int flag;
        unsigned long time;
    } vsync;
    vsync.flag = 0;
    SetVSyncFlag((int *)&vsync.flag, (unsigned long *)&vsync.time);
    interrupts = DIntr();
    INTC_STAT = INTC_VBLANK_START;
    __asm__("sync");
    if (interrupts) EIntr();
    while ((INTC_STAT & INTC_VBLANK_START) == 0 && vsync.flag == 0) {
    }
    interrupts = DIntr();
    INTC_STAT = INTC_VBLANK_START;
    __asm__("sync");
    if (interrupts) EIntr();
    return vsync.time;
}

int write(int fd, void *buf, int size)
{
    if ((unsigned int)(fd - STDOUT) < 2) {
        if (ttyinit == 0) {
            if (sceTtyInit() == 0) goto err;
            ttyinit = 1;
        }
        return sceTtyWrite(buf, size);
    }
err:
    return -1;
}

int read(int fd, void *buf, int size)
{
    if (fd == STDIN) {
        if (ttyinit == 0) {
            if (sceTtyInit() == 0) goto err;
            ttyinit = 1;
        }
        return sceTtyRead(buf, size);
    }
err:
    return -1;
}

int open(void)
{
    *__errno() = EIO;
    return -1;
}

int close(void)
{
    return -1;
}

int ioctl(void)
{
    return -1;
}

int lseek(void)
{
    return -1;
}

void *sbrk(int incr)
{
    static char *heap_ptr = _end;
    u_int stat;
    char *prev;
    char *next;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    stat &= 0x10000;
    if (stat) DI();
    next = heap_ptr + incr;
    if ((char *)EndOfHeap() < next) {
        *__errno() = ENOMEM;
        if (stat) EI();
        return (void *)-1;
    }
    prev = heap_ptr;
    heap_ptr = next;
    if (stat) EI();
    return prev;
}

int isatty(void)
{
    return 1;
}

int fstat(int fd, struct stat *st)
{
    st->st_blksize = 0;
    st->st_mode = S_IFCHR;
    return 0;
}

int getpid(void)
{
    return 1;
}

/* signalling the process itself exits */
int kill(int pid, int sig)
{
    if (pid == 1) {
        Exit(sig);
    }
    return 0;
}

int stat_glue(void)
{
    *__errno() = EIO;
    return -1;
}

int unlink(void)
{
    *__errno() = EIO;
    return -1;
}
