/* timer.c - the EE timer library on hardware timer 2: a 64-bit system time made of the 16-bit
 * counter and an overflow count, and 128 software counters, each of which may carry a handler
 * that cbTimerHandler calls when the counter reaches its schedule. */
#include "dw4/libkernl.h"

typedef unsigned long u_long;

#define T2_COUNT (*(volatile unsigned int *)0x10001000)
#define T2_MODE (*(volatile unsigned int *)0x10001010)
/* the uncached addresses SetT2 writes, from kernel mode */
#define T2_COUNT_KSEG1 0xb0001000
#define T2_MODE_KSEG1 0xb0001010
#define T2_COMP_KSEG1 0xb0001020

/* Tn_MODE bits */
#define T_MODE_CLKS 0x3U
#define T_MODE_CUE 0x80U
#define T_MODE_CMPE 0x100U
#define T_MODE_OVFE 0x200U
#define T_MODE_EQUF 0x400U
#define T_MODE_OVFF 0x800U

#define INTC_TIM2 11

#define TIMER_COUNTERS 128
#define TIMER_ID_KEY_MASK 0x3ff

#define BUS_CLOCK 147456000
#define BUS_CLOCKS_200_USEC (BUS_CLOCK * 200UL / 1000000)
#define PRESCALED(clocks, mode) ((clocks) >> (((mode) & T_MODE_CLKS) << 2))

#define KE_OK 0
#define KE_BUSY 0x80000010
#define KE_ERROR 0x80008001
#define KE_ILLEGAL_ID 0x80008002
#define KE_NO_COUNTER 0x80008005
#define KE_NO_HANDLER 0x80009021

/* COUNTER_RUNNING: counting; COUNTER_HANDLER: a handler is set, and the counter is on the alarm
 * list while it also runs */
#define COUNTER_RUNNING 1
#define COUNTER_HANDLER 2

typedef u_long (*TimerHandler)(int id, u_long schedule, u_long actual, void *arg, void *addr);

/* A counter's id is its address shifted up by 4 with a 10-bit key in the low bits; the counters are
 * 64-byte aligned, so the address comes back as (id >> 10) << 6. */
typedef struct Counter {
    struct Counter *next;
    struct Counter *prev;
    volatile int key;
    unsigned int flags;
    u_long base;
    u_long count;
    u_long schedule;
    TimerHandler handler;
    void *gp;
    void *arg;
    int pad[3];
} Counter;

typedef struct {
    u_long overflows;
    int intcHandler;
    volatile unsigned int uniqueKey;
    volatile int usedCounters;
    Counter *freeList;
    Counter *alarms;
    volatile int current;
} TimerState;

#define COUNTER_OF(id) ((Counter *)(((unsigned int)(id) >> 10) << 6))
#define COUNTER_ID(c) (((int)(c) << 4) | (c)->key)

void *memset(void *dst, int value, unsigned int size);
int _sceTimerAlarmInit(void);
int AddIntcHandler2(int cause, int (*handler)(int), int next, void *arg);
int RemoveIntcHandler(int cause, int id);
int EnableIntc(int cause);
int DisableIntc(int cause);
void SetT2(unsigned int addr, unsigned int value);
int cbTimerHandler(int cause);

extern TimerState g_Timer;
extern Counter timerCounters[TIMER_COUNTERS];

void SetT2_COUNT(unsigned int count)
{
    SetT2(T2_COUNT_KSEG1, count);
}

void SetT2_MODE(unsigned int mode)
{
    SetT2(T2_MODE_KSEG1, mode);
}

void SetT2_COMP(unsigned int comp)
{
    SetT2(T2_COMP_KSEG1, comp);
}

int InitTimer(int clock)
{
    int i;
    int handler;
    int intr;
    int mode;
    if (g_Timer.intcHandler >= 0) {
        return KE_ERROR;
    }
    g_Timer.overflows = 0;
    g_Timer.usedCounters = 0;
    memset(timerCounters, 0, sizeof(timerCounters));
    g_Timer.freeList = timerCounters;
    for (i = TIMER_COUNTERS - 1; i >= 0; i--) {
        timerCounters[i].next = &timerCounters[i + 1];
    }
    timerCounters[TIMER_COUNTERS - 1].next = 0;
    _sceTimerAlarmInit();
    handler = AddIntcHandler2(INTC_TIM2, cbTimerHandler, 0, 0);
    if (handler < 0) {
        return KE_NO_HANDLER;
    }
    g_Timer.intcHandler = handler;
    intr = DIntr();
    mode = T2_MODE;
    mode = (mode & ~T_MODE_CLKS) | clock;
    mode |= T_MODE_OVFE | T_MODE_CMPE;
    if (!(mode & T_MODE_CUE)) {
        mode |= T_MODE_OVFF | T_MODE_EQUF | T_MODE_CUE;
        SetT2_COUNT(0);
        SetT2_COMP(0xffff);
    }
    SetT2_MODE(mode);
    EnableIntc(INTC_TIM2);
    if (intr) {
        EIntr();
    }
    return KE_OK;
}

int EndTimer(void)
{
    int intr;
    if (g_Timer.intcHandler < 0) {
        return KE_ERROR;
    }
    if (g_Timer.usedCounters != 0) {
        return KE_BUSY;
    }
    intr = DIntr();
    if (RemoveIntcHandler(INTC_TIM2, g_Timer.intcHandler) == 0) {
        DisableIntc(INTC_TIM2);
        SetT2_MODE(T_MODE_OVFF | T_MODE_EQUF);
        SetT2_COUNT(0);
    }
    g_Timer.overflows = 0;
    g_Timer.intcHandler = -1;
    if (intr) {
        EIntr();
    }
    return KE_OK;
}

int GetTimerPreScaleFactor(void)
{
    if (g_Timer.intcHandler < 0) {
        return KE_ERROR;
    }
    return T2_MODE & T_MODE_CLKS;
}

u_long iGetTimerSystemTime(void);
static void SetNextComp(u_long now);

int StartTimerSystemTime(void)
{
    int intr = DIntr();
    int mode = T2_MODE;
    if (mode & T_MODE_CUE) {
        if (intr) {
            EIntr();
        }
        return 1;
    }
    SetT2_MODE((mode & ~(T_MODE_OVFF | T_MODE_EQUF)) | T_MODE_CUE);
    SetNextComp(iGetTimerSystemTime());
    if (intr) {
        EIntr();
    }
    return 0;
}

int StopTimerSystemTime(void)
{
    int intr = DIntr();
    int mode = T2_MODE;
    if (!(mode & T_MODE_CUE)) {
        if (intr) {
            EIntr();
        }
        return 0;
    }
    SetT2_MODE(mode & ~(T_MODE_OVFF | T_MODE_EQUF | T_MODE_CUE));
    if (intr) {
        EIntr();
    }
    return 1;
}

/* Sets the compare register for the first alarm due, and for every alarm due within 200 us of it
 * at once; an alarm already that close is given 200 us from now. */
static void SetNextComp(u_long now)
{
    u_long first, next;
    long left;
    unsigned int mode;
    Counter *alarm = g_Timer.alarms;

    if (g_Timer.current >= 0) {
        return;
    }
    mode = T2_MODE;
    if (alarm == 0) {
        SetT2_COMP(0);
        SetT2_MODE(mode & ~T_MODE_OVFF);
        return;
    }
    first = alarm->schedule + alarm->base - alarm->count;
    alarm = alarm->next;
    while (alarm) {
        next = alarm->schedule + alarm->base - alarm->count;
        if (next < first + BUS_CLOCKS_200_USEC) {
            first = next;
        } else {
            break;
        }
        alarm = alarm->next;
    }
    left = first - now;
    if (left < (long)BUS_CLOCKS_200_USEC) {
        SetT2_COMP(T2_COUNT + PRESCALED(BUS_CLOCKS_200_USEC, mode));
        SetT2_MODE(mode & ~T_MODE_OVFF);
    } else {
        SetT2_MODE(mode & ~T_MODE_OVFF);
        SetT2_COMP(PRESCALED(first, mode));
    }
    return;
}

/* Puts the counter on the alarm list, which is kept in the order the alarms fall due. */
static void InsertAlarm(Counter *alarm)
{
    Counter *prev = 0;
    Counter *cur = g_Timer.alarms;
    u_long due = alarm->schedule + alarm->base - alarm->count;
    while (cur != 0 && due >= cur->schedule + cur->base - cur->count) {
        prev = cur;
        cur = cur->next;
    }
    alarm->prev = prev;
    alarm->next = cur;
    if (cur != 0) {
        cur->prev = alarm;
    }
    if (prev != 0) {
        prev->next = alarm;
    } else {
        g_Timer.alarms = alarm;
    }
}

static Counter *UnlinkAlarm(Counter *alarm)
{
    Counter *next = alarm->next;
    if (alarm->prev != 0) {
        alarm->prev->next = next;
    } else {
        g_Timer.alarms = next;
    }
    if (next != 0) {
        next->prev = alarm->prev;
    }
    alarm->prev = 0;
    return next;
}

/* The system time: the overflow count above the 16-bit counter, in bus clocks (the counter's
 * prescale shifted back out). A pending overflow the interrupt has not counted yet is counted here,
 * with the counter read again after it. */
static inline u_long readSystemTime(void)
{
    u_long now;
    __asm__(
        ".set push\n.set noreorder\n"
        "lwu %0,0(%1)\n"
        "lw $8,0x10(%1)\n"
        "ld $10,%2\n"
        "andi $9,$8,0x800\n"
        "beq $9,$0,1f\n"
        "addiu $9,$0,2\n"
        "lwu %0,0(%1)\n"
        "daddiu $10,$10,1\n"
        "1:\n"
        "andi $8,$8,3\n"
        "dsll $10,$10,16\n"
        "movz $9,$0,$8\n"
        "or %0,%0,$10\n"
        "dsllv $9,$9,$8\n"
        "dsllv %0,%0,$9\n"
        ".set pop"
        : "=&r"(now)
        : "r"(0x10001000), "m"(g_Timer)
        : "$8", "$9", "$10", "memory");
    return now;
}

u_long iGetTimerSystemTime(void)
{
    return readSystemTime();
}

u_long GetTimerSystemTime(void)
{
    u_long now;
    int intr = DIntr();
    now = readSystemTime();
    if (intr) EIntr();
    return now;
}

int iAllocTimerCounter(void)
{
    Counter *c = g_Timer.freeList;
    if (c == 0) {
        return KE_NO_COUNTER;
    }
    g_Timer.usedCounters++;
    g_Timer.freeList = c->next;
    c->handler = 0;
    c->flags = 0;
    c->count = 0;
    g_Timer.uniqueKey++;
    c->key = ((g_Timer.uniqueKey << 1) & 0x3fe) | 1;
    return COUNTER_ID(c);
}

int AllocTimerCounter(void)
{
    int intr;
    int id;
    intr = DIntr();
    id = iAllocTimerCounter();
    if (intr != 0) {
        EIntr();
    }
    return id;
}

int iFreeTimerCounter(int id)
{
    Counter *c = COUNTER_OF(id);
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != c->key) return KE_ILLEGAL_ID;
    if (g_Timer.current == id) return KE_BUSY;
    if (c->flags & COUNTER_HANDLER) UnlinkAlarm(c);
    c->key = 0;
    c->flags = 0;
    c->next = g_Timer.freeList;
    g_Timer.freeList = c;
    g_Timer.usedCounters--;
    return KE_OK;
}

int FreeTimerCounter(int id)
{
    int intr;
    int result;
    intr = DIntr();
    result = iFreeTimerCounter(id);
    if (intr != 0) {
        EIntr();
    }
    return result;
}

int iGetTimerUsedUnusedCounters(int *used, int *unused)
{
    if (g_Timer.intcHandler < 0) return KE_ERROR;
    if (used) *used = g_Timer.usedCounters;
    if (unused) *unused = TIMER_COUNTERS - g_Timer.usedCounters;
    return KE_OK;
}

int GetTimerUsedUnusedCounters(int *used, int *unused)
{
    int intr;
    int result;
    intr = DIntr();
    result = iGetTimerUsedUnusedCounters(used, unused);
    if (intr != 0) {
        EIntr();
    }
    return result;
}

int iStartTimerCounter(int id)
{
    Counter *c = COUNTER_OF(id);
    u_long now;
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != c->key) return KE_ILLEGAL_ID;
    if (g_Timer.current == id) return KE_BUSY;
    if (c->flags & COUNTER_RUNNING) return 1;
    now = iGetTimerSystemTime();
    c->base = now;
    c->flags |= COUNTER_RUNNING;
    if (c->flags & COUNTER_HANDLER) {
        InsertAlarm(c);
        SetNextComp(now);
    }
    return KE_OK;
}

int StartTimerCounter(int id)
{
    int intr;
    int result;
    intr = DIntr();
    result = iStartTimerCounter(id);
    if (intr != 0) {
        EIntr();
    }
    return result;
}

int iStopTimerCounter(int id)
{
    Counter *c = COUNTER_OF(id);
    u_long now;
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != c->key) return KE_ILLEGAL_ID;
    if (g_Timer.current == id) return KE_BUSY;
    if (!(c->flags & COUNTER_RUNNING)) return 0;
    now = iGetTimerSystemTime();
    c->count += now - c->base;
    c->flags &= ~COUNTER_RUNNING;
    if (c->flags & COUNTER_HANDLER) {
        UnlinkAlarm(c);
        SetNextComp(now);
    }
    return 1;
}

int StopTimerCounter(int id)
{
    int intr;
    int result;
    intr = DIntr();
    result = iStopTimerCounter(id);
    if (intr != 0) {
        EIntr();
    }
    return result;
}

/* Sets the counter's count; returns the count it had, or -1 for a bad id. */
u_long SetTimerCount(int id, u_long count)
{
    Counter *c = COUNTER_OF(id);
    int intr;
    u_long old;
    u_long now;
    intr = DIntr();
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != c->key || g_Timer.current == id) {
        if (intr) EIntr();
        return -1;
    }
    old = c->count;
    if (c->flags & COUNTER_RUNNING) {
        now = iGetTimerSystemTime();
        old += now - c->base;
        c->base = now;
        c->count = count;
    } else {
        c->count = count;
    }
    if (intr) EIntr();
    return old;
}

/* the system time at which a running counter would have read 0 */
u_long isceTimerGetBaseTime(int id)
{
    Counter *c = COUNTER_OF(id);
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != c->key) return -1;
    if (c->flags & COUNTER_RUNNING) return c->base - c->count;
    return 0;
}

u_long GetTimerBaseTime(int id)
{
    int intr;
    u_long result;
    intr = DIntr();
    result = isceTimerGetBaseTime(id);
    if (intr != 0) {
        EIntr();
    }
    return result;
}

u_long iGetTimerCount(int id)
{
    Counter *c = COUNTER_OF(id);
    u_long count;
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != c->key) return -1;
    count = c->count;
    if (c->flags & COUNTER_RUNNING) count += iGetTimerSystemTime() - c->base;
    return count;
}

u_long GetTimerCount(int id)
{
    int intr;
    u_long result;
    intr = DIntr();
    result = iGetTimerCount(id);
    if (intr != 0) {
        EIntr();
    }
    return result;
}

/* Sets the handler called when the counter reaches `schedule`, or clears it for a null handler. The
 * handler runs with the caller's $gp. */
int iSetTimerHandler(int id, u_long schedule, TimerHandler handler, void *arg)
{
    Counter *c = COUNTER_OF(id);
    if (id < 0 || (id & TIMER_ID_KEY_MASK) != c->key) return KE_ILLEGAL_ID;
    if (g_Timer.current == id) return KE_BUSY;
    if (c->flags & COUNTER_HANDLER) UnlinkAlarm(c);
    c->handler = handler;
    if (handler == 0) {
        c->flags &= ~COUNTER_HANDLER;
    } else {
        c->schedule = schedule;
        c->flags |= COUNTER_HANDLER;
        __asm__("sw $28,%0" : : "m"(c->gp) : "memory");
        c->arg = arg;
        if (c->flags & COUNTER_RUNNING) InsertAlarm(c);
    }
    SetNextComp(iGetTimerSystemTime());
    return KE_OK;
}

int SetTimerHandler(int id, u_long schedule, TimerHandler handler, void *arg)
{
    int intr;
    int result;
    intr = DIntr();
    result = iSetTimerHandler(id, schedule, handler, arg);
    if (intr != 0) {
        EIntr();
    }
    return result;
}

void sceTimerBusClock2USec(u_long clocks, unsigned int *sec, unsigned int *usec)
{
    unsigned int s;
    s = clocks / BUS_CLOCK;
    if (sec) *sec = s;
    if (usec) *usec = (clocks - (u_long)s * BUS_CLOCK) * 1000000 / BUS_CLOCK;
}

u_long sceTimerUSec2BusClock(unsigned int sec, unsigned int usec)
{
    return (u_long)sec * BUS_CLOCK + (u_long)usec * BUS_CLOCK / 1000000;
}

float sceTimerBusClock2Freq(u_long clocks)
{
    return 147456000.0f / clocks;
}

u_long sceTimerFreq2BusClock(float freq)
{
    return 147456000.0f / freq;
}
