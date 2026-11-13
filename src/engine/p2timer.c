#include "dw4/eekernel.h"
#include "dw4/p2timer.h"

#define T0_MODE ((volatile unsigned int *)0x10000010)
#define T1_COUNT ((unsigned int *)0x10000800)

/* A sleeping thread's alarm: its delay counts from the alarm before it in the pending list. */
typedef struct p2Alarm {
    int sema;
    int delay;
    struct p2Alarm *next;
} p2Alarm;

int FUN_0010b9c0(int cause);
void p2StartTimers(void);
void p2AddAlarm(int sema, int milliseconds);

extern int p2Timer0HandlerId;
extern int p2Timer1HandlerId;
extern p2Alarm *p2PendingAlarms;
extern int p2AlarmSema;
extern int p2TimerUsers;
extern long long p2ClockOverflows;
extern long long p2NanosecondsBase;
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
