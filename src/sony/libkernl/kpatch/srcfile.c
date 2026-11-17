/* srcfile.c - the alarm kernel patch. Linked to run at 0x80076000, where alarm.c copies it, it adds SetAlarm and
 * ReleaseAlarm to a kernel that lacks them: up to 64 one-shot alarms on timer 3, kept in a list sorted by the
 * count each fires at, whose handlers run in user mode when the timer's compare interrupt comes. */
#include "dw4/sony/libkernl_patch.h"

typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned long u_long;

#define T3_COUNT ((volatile u_int *)0xb0001800)
#define T3_MODE ((volatile u_int *)0xb0001810)
#define T3_COMP ((volatile u_int *)0xb0001820)
#define I_STAT ((volatile u_int *)0x1000f000)
#define INTC_TIM3 0x1000

/* T3_MODE: bus clock / 256, count enabled; with the compare interrupt enabled and its flag cleared; without
 * the interrupt; stopped */
#define T3_MODE_COMPARE 0x583
#define T3_MODE_RUN 0x483
#define T3_MODE_STOP 0x83

#define MAX_ALARMS 64

/* where eenull is copied: runs a handler in user mode */
#define USER_MODE_DISPATCHER ((void *)0x82000)

typedef void (*AlarmHandler)(int id, u_short target, void *arg);

typedef struct {
    u_short target;
    u_short start;
    int id;
    AlarmHandler handler;
    void *arg;
    u_int gp; /* the setter's $gp register, put back while its handler runs */
} Alarm;

int kSetAlarm(u_short time, AlarmHandler handler, void *arg);
int kReleaseAlarm(int id);
void kAlarmInterrupt(void);
void ReturnFromUserHandler(void);
void CallUserHandler(void *dispatcher, AlarmHandler handler, int id, u_short target, void *arg);
static void StartCompare(int target);

static int alarmCount = 0;
static u_long usedAlarms = 0;

static SyscallEntry kSysEntry[6] = {
    {0xfc, kSetAlarm},
    {0xfe, kSetAlarm},
    {0xfd, kReleaseAlarm},
    {0xff, kReleaseAlarm},
    {0x12c, kAlarmInterrupt},
    {8, ReturnFromUserHandler},
};

static Alarm alarms[MAX_ALARMS];

/* system call 91 while the patch is installed: what alarm.c installs for each call number */
void *kGetEntryAddress(int number)
{
    u_int i;
    for (i = 0; i < 6; i++) {
        if (number == kSysEntry[i].number) {
            return kSysEntry[i].handler;
        }
    }
    return 0;
}

/* `count`, read at or after `now`, on a scale where the 16-bit counter's wrap does not reorder them */
static int UnwrapCount(int now, int count)
{
    if (count < now) {
        return count | 0x10000;
    }
    return count;
}

/* Makes room in the list for an alarm due at `target`; returns its index. */
static int InsertAlarm(int now, int target)
{
    int i, j;
    for (i = 0; i < alarmCount; i++) {
        if (target < UnwrapCount(now, alarms[i].target)) {
            for (j = alarmCount - 1; j >= i; j--) {
                alarms[j + 1] = alarms[j];
            }
            break;
        }
    }
    return i;
}

/* Takes the lowest free alarm id; returns it, or -1 when all 64 are in use. */
static inline int AllocAlarmId(void)
{
    int i;
    for (i = 0; i < MAX_ALARMS; i++) {
        if (((usedAlarms >> i) & 1) == 0) {
            usedAlarms |= (u_long)1 << i;
            return i;
        }
    }
    return -1;
}

static int AddAlarm(u_short time, AlarmHandler handler, void *arg)
{
    int now, target, id, at;
    u_int gp;

    now = *T3_COUNT;
    target = time;
    target += now;
    if (alarmCount >= MAX_ALARMS) {
        return -1;
    }
    id = AllocAlarmId();
    if (id < 0) {
        return id;
    }
    __asm__ volatile("move %0, $28" : "=r"(gp));
    at = InsertAlarm(now, target);
    alarms[at].target = target;
    alarms[at].start = now;
    alarms[at].id = id;
    alarms[at].handler = handler;
    alarms[at].arg = arg;
    alarms[at].gp = gp;
    alarmCount++;
    StartCompare(alarms[0].target);
    return alarms[at].id;
}

/* Cancels alarm `id`; returns the counts left before it was due, or -1 when it is unknown or already due. */
int kReleaseAlarm(int id)
{
    int result, i, j;
    u_short start;

    result = -1;
    if (alarmCount > 0)
    for (i = 0; i < alarmCount; i++) {
        if (id == alarms[i].id) {
            if (alarms[i].target == *T3_COMP && (*I_STAT & INTC_TIM3)) {
                return -1;
            }
            start = alarms[i].start;
            for (j = i; j < alarmCount - 1; j++) {
                alarms[j] = alarms[j + 1];
            }
            alarmCount--;
            usedAlarms &= ~((u_long)1 << id);
            if (i == 0) {
                StartCompare(alarms[0].target);
            }
            if (alarmCount == 0) {
                *T3_MODE = T3_MODE_STOP;
            }
            result = UnwrapCount(start, *T3_COUNT) - start;
            break;
        }
    }
    __asm__("sync");
    return result;
}

int kSetAlarm(u_short time, AlarmHandler handler, void *arg)
{
    int id;
    id = AddAlarm(time, handler, arg);
    __asm__("sync");
    return id;
}

static void StartCompare(int target)
{
    *T3_COMP = target;
    __asm__("sync");
    *T3_MODE = T3_MODE_COMPARE;
}

/* the timer 3 compare interrupt: runs every alarm due at this count, then sets the compare for the next */
void kAlarmInterrupt(void)
{
    Alarm alarm;
    u_int gp;
    int i;

    for (i = 0; i < alarmCount; i++) {
        if (alarms[0].target != alarms[i].target) {
            StartCompare(alarms[i].target);
            break;
        }
    }
    do {
        alarm = alarms[0];
        alarmCount--;
        for (i = 0; i < alarmCount; i++) {
            alarms[i] = alarms[i + 1];
        }
        __asm__ volatile("move %0, $28" : "=r"(gp));
        __asm__("move $28, %0" : : "r"(alarm.gp));
        usedAlarms &= ~((u_long)1 << alarm.id);
        CallUserHandler(USER_MODE_DISPATCHER, alarm.handler, alarm.id, alarm.target, alarm.arg);
        __asm__("move $28, %0" : : "r"(gp));
    } while (alarmCount > 0 && alarm.target == alarms[0].target);
    if (alarmCount > 0) {
        StartCompare(alarms[0].target);
    } else {
        *T3_MODE = T3_MODE_RUN;
    }
    __asm__("sync");
    __asm__("ei");
}
