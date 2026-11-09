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
    unsigned long long count;
    int handler;
    int pad0;
    int active;
    Alarm *free_list;
    Alarm *head;
} AlarmState;

extern AlarmState D_00483508;

void InsertAlarm(Alarm *alarm)
{
    Alarm *prev = 0;
    Alarm *cur = D_00483508.head;
    unsigned long long key = alarm->length + alarm->target - alarm->start;
    while (cur != 0 && key >= cur->length + cur->target - cur->start) {
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
        D_00483508.head = alarm;
    }
}
