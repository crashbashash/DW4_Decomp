/* libkernl.h - what Sony libkernl's files share and export: the kernel patch tables, the interrupt
 * and DMA-channel switches, data-cache maintenance, the kernel printf, the start-up calls, threads,
 * timers and alarms, the DECI2 console and newlib's system-call glue. */
#ifndef DW4_LIBKERNL_H
#define DW4_LIBKERNL_H

#include "dw4/sony/libkernl_patch.h"

#ifdef __cplusplus
extern "C" {
#endif

/* An alarm's callback: its return is the next schedule, or 0 to free the alarm. */
typedef int (*AlarmCallback)(int id, int schedule, int actual, void *arg);

int DIntr(void);
int EIntr(void);
void FlushCache(int mode);
int DisableIntc(int cause);
int EnableIntc(int cause);
int DisableDmac(int channel);
int EnableDmac(int channel);
/* Write back (Sync) or discard (Invalid) the data-cache lines covering [start, end]; the i form is
 * for interrupt handlers. */
void SyncDCache(void *start, void *end);
void iSyncDCache(void *start, void *end);
void InvalidDCache(void *start, void *end);
void scePrintf(const char *format, ...);
void kprintf(const char *format, ...);
int kputs(char *s);

/* the start-up calls initsys.c makes, and the semaphore newlib's malloc lock takes */
int InitThread(void);
void InitTLBFunctions(void);
int InitTLB(void);
void InitExecPS2(void);
void InitAlarm(void);
void sceSifInitRebootNotify(void);
void sceSifExecNotifyHandler(int system, void *arg);
extern int __sce_sema_id;
/* the library's version tag, "PsIIlibkernl" and the release */
extern char __ps2_klibinfo__[];
/* the argument block _ExecPS2 hands to the new program */
extern char *_kExecArg;
void Exit(int status);

int DelayThread(unsigned int usec);
int iSuspendThread(int thread);

/* timer.c: the counters and the system time; clocks are bus-clock cycles (a 64-bit long) */
int InitTimer(int clock);
int StartTimerSystemTime(void);
unsigned long sceTimerUSec2BusClock(unsigned int sec, unsigned int usec);
int AllocTimerCounter(void);
int iAllocTimerCounter(void);
int FreeTimerCounter(int id);
int iFreeTimerCounter(int id);
int StartTimerCounter(int id);
int iStartTimerCounter(int id);

/* timeralarm.c */
int _sceTimerAlarmInit(void);
int SetTimerAlarm(unsigned long clocks, AlarmCallback callback, void *arg);
int iSetTimerAlarm(unsigned long clocks, AlarmCallback callback, void *arg);

/* tty.c and deci2.c: the console over DECI2 */
int sceTtyInit(void);
int sceTtyRead(char *buf, int n);
int sceTtyWrite(char *buf, int n);
int sceDeci2ReqSend(int socket, char dest);
void sceDeci2Poll(int socket);
int sceDeci2ExRecv(int socket, void *buf, unsigned short size);
int sceDeci2ExSend(int socket, void *buf, unsigned short size);

/* glue.c: vblank waits, and newlib's system calls */
struct stat;
void VSync(void);
long VSync2(void);
void sceResetttyinit(void);
int read(int fd, void *buf, int size);
int write(int fd, void *buf, int size);
int close(int fd);
int lseek(int fd, int offset, int whence);
int isatty(int fd);
int fstat(int fd, struct stat *st);
void *sbrk(int incr);
int getpid(void);
int kill(int pid, int sig);

#ifdef __cplusplus
}
#endif

#endif
