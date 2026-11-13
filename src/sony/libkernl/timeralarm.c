/* timeralarm.c - one-shot alarms on top of the timer counters: each alarm owns a counter whose
 * handler calls the alarm's callback, and is freed when the callback returns 0. */
#include "dw4/libkernl.h"

typedef unsigned long u_long;

#define TIMER_ALARMS 64

#define KE_ILLEGAL_ID 0x80008002
#define KE_NO_ALARM 0x80008005
#define KE_ILLEGAL_HANDLER 0x80000016

/* the callback's return: 0 frees the alarm, anything else is the next schedule */
typedef int (*AlarmCallback)(int id, int schedule, int actual, int arg);

/* An alarm's id is its address shifted up by 4 with the low byte of its counter's id (odd, so never
 * 0) below it; the alarms are 16-byte aligned. */
typedef struct Alarm {
    struct Alarm *next;
    volatile int counter;
    AlarmCallback callback;
    int arg;
} Alarm;

#define ALARM_OF(id) ((Alarm *)(((unsigned int)(id) >> 8) << 4))
#define ALARM_ID(a, counter) (((int)(a) << 4) | ((counter) & 0xfe) | 1)

int AllocTimerCounter(void);
int iAllocTimerCounter(void);
int FreeTimerCounter(int id);
int iFreeTimerCounter(int id);
int StartTimerCounter(int id);
int iStartTimerCounter(int id);
int SetTimerHandler(int id, u_long schedule, int (*handler)(int, int, int, Alarm *), Alarm *arg);
int iSetTimerHandler(int id, u_long schedule, int (*handler)(int, int, int, Alarm *), Alarm *arg);

extern Alarm timerAlarms[TIMER_ALARMS];
extern Alarm *freeAlarms;

int _sceTimerAlarmInit(void)
{
    int i;
    freeAlarms = timerAlarms;
    for (i = TIMER_ALARMS - 1; i >= 0; i--) timerAlarms[i].next = &timerAlarms[i + 1];
    timerAlarms[TIMER_ALARMS - 1].next = 0;
    return 0;
}

/* The counter's handler: calls the callback with the alarm's id, and frees the alarm (returning -1,
 * which stops the counter's handler) when the callback returns 0. */
static int AlarmHandler(int counter, int schedule, int actual, Alarm *alarm)
{
    int next;
    next = alarm->callback(ALARM_ID(alarm, counter), schedule, actual, alarm->arg);
    if (next == 0) {
        alarm->next = freeAlarms;
        freeAlarms = alarm;
        alarm->counter = 0;
        return -1;
    }
    return next;
}

int SetTimerAlarm(u_long clocks, AlarmCallback callback, int arg)
{
    Alarm *alarm;
    Alarm *head;
    int counter;
    int intr;
    if (callback == 0) return KE_ILLEGAL_HANDLER;
    intr = DIntr();
    head = freeAlarms;
    if (head) freeAlarms = head->next;
    alarm = head;
    if (alarm == 0) {
        if (intr) EIntr();
        return KE_NO_ALARM;
    }
    counter = AllocTimerCounter();
    if (counter < 0) {
        alarm->next = freeAlarms;
        freeAlarms = alarm;
        alarm->counter = 0;
        if (intr) EIntr();
        return counter;
    }
    alarm->callback = callback;
    alarm->arg = arg;
    alarm->counter = counter;
    SetTimerHandler(counter, clocks, AlarmHandler, alarm);
    StartTimerCounter(counter);
    if (intr) EIntr();
    return ALARM_ID(alarm, counter);
}

int iSetTimerAlarm(u_long clocks, AlarmCallback callback, int arg)
{
    Alarm *alarm;
    Alarm *head;
    int counter;
    if (callback == 0) return KE_ILLEGAL_HANDLER;
    head = freeAlarms;
    if (head) freeAlarms = head->next;
    alarm = head;
    if (alarm == 0) return KE_NO_ALARM;
    counter = iAllocTimerCounter();
    if (counter < 0) {
        alarm->next = freeAlarms;
        freeAlarms = alarm;
        alarm->counter = 0;
        return counter;
    }
    alarm->callback = callback;
    alarm->arg = arg;
    alarm->counter = counter;
    iSetTimerHandler(counter, clocks, AlarmHandler, alarm);
    iStartTimerCounter(counter);
    return ALARM_ID(alarm, counter);
}

int ReleaseTimerAlarm(int id)
{
    Alarm *alarm;
    int intr;
    alarm = ALARM_OF(id);
    intr = DIntr();
    if (id < 0 || ((id ^ alarm->counter) & 0xff) != 0) {
        if (intr) EIntr();
        return KE_ILLEGAL_ID;
    }
    FreeTimerCounter(alarm->counter);
    alarm->next = freeAlarms;
    freeAlarms = alarm;
    alarm->counter = 0;
    if (intr) EIntr();
    return 0;
}

int iReleaseTimerAlarm(int id)
{
    Alarm *alarm;
    int result;
    alarm = ALARM_OF(id);
    if (id < 0 || ((id ^ alarm->counter) & 0xff) != 0) return KE_ILLEGAL_ID;
    result = iFreeTimerCounter(alarm->counter);
    if (result == 0) {
        alarm->next = freeAlarms;
        freeAlarms = alarm;
        alarm->counter = 0;
    }
    return result;
}
