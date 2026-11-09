typedef struct Alarm {
    struct Alarm *next;
    struct Alarm *prev;
    int pad[2];
    unsigned long long target;
    unsigned long long start;
    unsigned long long length;
    int rest[6];
} Alarm;
typedef struct {
    unsigned long highCount;
    int handler;
    unsigned int uniqueKey;
    unsigned int usedCounters;
    Alarm *free;
    Alarm *alarms;
    int current;
} TimerState;
extern TimerState DAT_00483508;
void FUN_00114800(int mode);
void FUN_00114810(int compare);
#define T1_COUNT (*(volatile unsigned int *)0x10001000)
#define T1_MODE (*(volatile unsigned int *)0x10001010)
#define BUS_CLOCKS_200_USEC (147456000UL * 200 / 1000000)
#define PRESCALED(clocks, mode) ((clocks) >> (((mode) & 3) << 2))
#define OVERFLOW_FLAG (1 << 11)
void SetNextComp(unsigned long now) {
    unsigned long first, next;
    long left;
    unsigned int mode;
    Alarm *alarm = DAT_00483508.alarms;

    if (DAT_00483508.current >= 0) {
        return;
    }
    mode = T1_MODE;
    if (alarm == 0) {
        FUN_00114810(0);
        FUN_00114800(mode & (unsigned int)~OVERFLOW_FLAG);
        return;
    }
    first = alarm->length + alarm->target - alarm->start;
    alarm = alarm->next;
    while (alarm) {
        next = alarm->length + alarm->target - alarm->start;
        if (next < first + BUS_CLOCKS_200_USEC) {
            first = next;
        } else {
            break;
        }
        alarm = alarm->next;
    }
    left = first - now;
    if (left < (long)BUS_CLOCKS_200_USEC) {
        FUN_00114810(T1_COUNT + PRESCALED(BUS_CLOCKS_200_USEC, mode));
        FUN_00114800(mode & (unsigned int)~OVERFLOW_FLAG);
    } else {
        FUN_00114800(mode & (unsigned int)~OVERFLOW_FLAG);
        FUN_00114810(PRESCALED(first, mode));
    }
    return;
}
