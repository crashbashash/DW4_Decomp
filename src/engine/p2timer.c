#include "dw4/eekernel.h"
#define __extension__
#include "dw4/newlib_reent.h"
#include "dw4/p2timer.h"

#define T0_COUNT ((unsigned int *)0x10000000)
#define T0_MODE ((unsigned int *)0x10000010)
#define T0_COMP ((unsigned int *)0x10000020)
#define T1_COUNT ((unsigned int *)0x10000800)
#define T1_MODE ((unsigned int *)0x10000810)
#define T1_COMP ((unsigned int *)0x10000820)

#define P2_ALARM_COUNT 20

/* Timer 0 counts 576 ticks a millisecond. */
#define P2_TICKS_PER_MILLISECOND 576
/* The compare register holds at most this many ticks; a longer delay wraps through it. */
#define P2_TIMER_SPAN 0xffff

/* A sleeping thread's alarm: its delay counts from the alarm before it in the pending list. */
typedef struct p2Alarm {
    int sema;
    int delay;
    struct p2Alarm *next;
} p2Alarm;

/* A timer's mode register (Tn_MODE). */
typedef union p2TimerMode {
    unsigned int word;
    struct {
        unsigned int clock : 2;
        unsigned int gate : 1;
        unsigned int gateSource : 1;
        unsigned int gateMode : 2;
        unsigned int zeroReturn : 1;
        unsigned int countUp : 1;
        unsigned int compareInterrupt : 1;
        unsigned int overflowInterrupt : 1;
        unsigned int equalFlag : 1;
        unsigned int overflowFlag : 1;
        unsigned int pad : 20;
    } bits;
} p2TimerMode;

/* A timer's count or compare register (Tn_COUNT, Tn_COMP). */
typedef union p2TimerCount {
    unsigned int word;
    unsigned short value;
} p2TimerCount;

int FUN_0010b9c0(int cause);
int EnableIntc(int cause);
int fprintf(struct __sFILE *stream, const char *format, ...);
void p2StartTimers(void);
int p2Timer1Handler(int cause);
int p2Timer0Handler(int cause);
void p2ArmAlarmTimer(void);
void p2AddAlarm(int sema, int milliseconds);

extern int p2Timer0HandlerId;
extern int p2Timer1HandlerId;
extern p2Alarm *p2PendingAlarms;
extern p2Alarm *p2FreeAlarms;
extern p2Alarm p2Alarms[P2_ALARM_COUNT];
extern int p2AlarmSema;
extern int p2TimerUsers;
extern int p2AlarmWraps;
extern p2TimerMode p2Timer0Mode;
extern p2TimerMode p2Timer1Mode;
extern long long p2ClockOverflows;
extern long long p2NanosecondsBase;
extern struct SemaParam p2AlarmSemaParam;
extern struct SemaParam p2SleepSemaParam;

void p2InitTimer(void) {
    if (p2TimerUsers++ == 0) {
        p2StartTimers();
    }
}

/* Stops both timer interrupts and wakes every thread still asleep. */
void p2StopTimers(void) {
    FUN_0010b9c0(INTC_TIM0);
    FUN_0010b9c0(INTC_TIM1);
    RemoveIntcHandler(INTC_TIM0, p2Timer0HandlerId);
    RemoveIntcHandler(INTC_TIM1, p2Timer1HandlerId);
    while (p2PendingAlarms != 0) {
        SignalSema(p2PendingAlarms->sema);
        p2PendingAlarms = p2PendingAlarms->next;
    }
    DeleteSema(p2AlarmSema);
}

void p2ShutdownTimer(void) {
    if (--p2TimerUsers == 0) {
        p2StopTimers();
    }
}

/* Links the alarm pool into the free list, installs both handlers and starts timer 1 counting
 * BUSCLK/16 with its overflow interrupt. */
void p2StartTimers(void) {
    struct SemaParam param;
    p2TimerCount count;
    p2TimerCount compare;
    int i;

    param = p2AlarmSemaParam;
    for (i = 0; i < P2_ALARM_COUNT; i++) {
        p2Alarms[i].next = &p2Alarms[i + 1];
    }
    p2Alarms[P2_ALARM_COUNT - 1].next = 0;
    p2Timer0HandlerId = AddIntcHandler(INTC_TIM0, p2Timer0Handler, 0);
    p2AlarmSema = CreateSema(&param);
    EnableIntc(INTC_TIM0);
    p2Timer1HandlerId = AddIntcHandler(INTC_TIM1, p2Timer1Handler, 0);
    EnableIntc(INTC_TIM1);
    p2Timer1Mode.bits.clock = 1;
    p2Timer1Mode.bits.gate = 0;
    p2Timer1Mode.bits.gateSource = 0;
    p2Timer1Mode.bits.gateMode = 0;
    p2Timer1Mode.bits.zeroReturn = 0;
    p2Timer1Mode.bits.compareInterrupt = 0;
    p2Timer1Mode.bits.overflowInterrupt = 1;
    p2Timer1Mode.bits.equalFlag = 1;
    p2Timer1Mode.bits.overflowFlag = 1;
    p2Timer1Mode.bits.countUp = 0;
    *T1_MODE = p2Timer1Mode.word;
    compare.value = 0;
    *T1_COMP = compare.word;
    count.value = P2_TIMER_SPAN;
    *T1_COUNT = count.word;
    p2Timer1Mode.bits.countUp = 1;
    *T1_MODE = p2Timer1Mode.word;
}

void p2ReadClock(long long *time) {
    *time = *T1_COUNT | (p2ClockOverflows << 16);
}

/* 1.08506942 = 10^7 / 9216000: timer 1 ticks to 100 ns units. */
void p2ReadNanoseconds(long long *time) {
    unsigned int count;
    float scaled;
    unsigned int ticks;

    count = *T1_COUNT;
    scaled = 1.08506942f * (float)count;
    ticks = (unsigned int)scaled;
    *time = (p2NanosecondsBase + ticks) * 100;
}

void p2Sleep(int seconds) {
    p2SleepMilliseconds(seconds * 1000);
}

void p2SleepMilliseconds(int milliseconds) {
    struct SemaParam param;
    long long start;
    long long end;
    int sema;

    param = p2SleepSemaParam;
    sema = CreateSema(&param);
    p2AddAlarm(sema, milliseconds);
    p2ReadClock(&start);
    WaitSema(sema);
    p2ReadClock(&end);
    p2SleepTime += (int)(end - start);
    DeleteSema(sema);
}

/* Inserts the alarm into the pending list, which keeps each delay relative to the one before. */
void p2InsertAlarm(p2Alarm *alarm, int milliseconds) {
    int elapsed;
    int delay;
    p2Alarm *prev;
    p2Alarm *cur;
    p2Alarm *next;

    elapsed = 0;
    cur = p2PendingAlarms;
    prev = 0;
    if (cur == 0) {
        alarm->delay = milliseconds;
        p2PendingAlarms = alarm;
        return;
    }
    while (cur != 0) {
        delay = cur->delay;
        if (milliseconds < elapsed + delay) {
            alarm->next = cur;
            if (prev == 0) {
                alarm->delay = milliseconds;
                p2PendingAlarms->delay = p2PendingAlarms->delay - alarm->delay;
                p2PendingAlarms = alarm;
            } else {
                prev->next = alarm;
                alarm->delay = milliseconds - elapsed;
                next = alarm->next;
                next->delay = next->delay - alarm->delay;
            }
            break;
        }
        prev = cur;
        elapsed += delay;
        cur = cur->next;
    }
    if (cur == 0) {
        prev->next = alarm;
        alarm->next = 0;
        alarm->delay = milliseconds - elapsed;
    }
}

/* Arms timer 0 for the first pending alarm: the compare register takes the delay's remainder
 * after its whole wraps, which the compare interrupt counts down first. */
void p2ArmAlarmTimer(void) {
    p2TimerCount count;
    p2TimerCount compare;
    int ticks;

    ticks = p2PendingAlarms->delay * P2_TICKS_PER_MILLISECOND;
    p2AlarmWraps = ticks / P2_TIMER_SPAN;
    compare.value = ticks % P2_TIMER_SPAN;
    *T0_COMP = compare.word;
    count.value = 0;
    *T0_COUNT = count.word;
    p2Timer0Mode.bits.clock = 2;
    p2Timer0Mode.bits.zeroReturn = 1;
    p2Timer0Mode.bits.compareInterrupt = 1;
    p2Timer0Mode.bits.overflowInterrupt = 0;
    p2Timer0Mode.bits.equalFlag = 1;
    p2Timer0Mode.bits.overflowFlag = 1;
}

/* Takes an alarm from the pool for the semaphore. Timer 0 stops while the pending list changes:
 * the first alarm's delay is first reduced by the time that has already run on it. */
void p2AddAlarm(int sema, int milliseconds) {
    p2Alarm *alarm;
    int count;
    int elapsed;
    int ticks;
    int wraps;
    int remainder;
    int *delay;

    WaitSema(p2AlarmSema);
    p2Timer0Mode.bits.countUp = 0;
    *T0_MODE = p2Timer0Mode.word;
    alarm = p2FreeAlarms;
    if (alarm == 0) {
        fprintf(_impure_ptr->_stderr, "TimerCallback resource exhausted.\n");
        return;
    }
    p2FreeAlarms = alarm->next;
    alarm->sema = sema;
    alarm->next = 0;
    count = *(unsigned short *)T0_COUNT;
    if (p2PendingAlarms != 0) {
        delay = &p2PendingAlarms->delay;
        ticks = *delay * P2_TICKS_PER_MILLISECOND;
        wraps = ticks / P2_TIMER_SPAN;
        remainder = ticks % P2_TIMER_SPAN;
        if (wraps == p2AlarmWraps) {
            elapsed = count;
        } else {
            elapsed = count + (remainder + (wraps - p2AlarmWraps) * P2_TIMER_SPAN);
        }
        *delay -= elapsed / P2_TICKS_PER_MILLISECOND;
    }
    p2InsertAlarm(alarm, milliseconds);
    p2ArmAlarmTimer();
    p2Timer0Mode.bits.countUp = 1;
    *T0_MODE = p2Timer0Mode.word;
    SignalSema(p2AlarmSema);
}
