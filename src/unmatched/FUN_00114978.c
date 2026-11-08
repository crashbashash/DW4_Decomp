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
    volatile int active;
    Alarm *free_list;
    Alarm *head;
} AlarmState;

extern AlarmState D_00483508;

int FUN_00113f20(void);
int FUN_00113f78(void);
int RemoveIntcHandler(int cause, int handler_id);
int FUN_0010b9c0(int cause);
void FUN_00114800(int mode);
void FUN_001147f0(int arg);

int FUN_00114978(void)
{
    int state;
    if (D_00483508.handler < 0) {
        return 0x80008001;
    }
    if (D_00483508.active != 0) {
        return 0x80000010;
    }
    state = FUN_00113f20();
    if (RemoveIntcHandler(11, D_00483508.handler) == 0) {
        FUN_0010b9c0(11);
        FUN_00114800(0xC00);
        FUN_001147f0(0);
    }
    D_00483508.count = 0;
    D_00483508.handler = -1;
    if (state) {
        FUN_00113f78();
    }
    return 0;
}
