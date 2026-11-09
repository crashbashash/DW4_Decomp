typedef unsigned int u_int;
struct DelaySemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    u_int attr;
    u_int option;
};
extern char D_004d2438[];
int CreateSema(struct DelaySemaParam *p);
int DeleteSema(int sema);
int WaitSema(int sema);
unsigned long sceTimerUSec2BusClock(u_int sec, u_int usec);
int SetTimerAlarm(unsigned long clk, int (*cb)(int, int, int, int), int arg);
int FUN_0010c008(int, int, int, int);
int DelayThread(u_int usec)
{
    struct DelaySemaParam sp;
    u_int stat;
    int sema;
    int ret;
    __asm__ volatile("mfc0 %0, $12" : "=r"(stat));
    if (!(stat & 0x10000)) return 0x80008008;
    sp.maxCount = 1;
    sp.option = (u_int)D_004d2438;
    sp.initCount = 0;
    sema = CreateSema(&sp);
    if (sema < 0) return 0x80008003;
    ret = SetTimerAlarm(sceTimerUSec2BusClock(0, usec), FUN_0010c008, sema);
    if (ret < 0) {
        DeleteSema(sema);
        return ret;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return 0;
}
