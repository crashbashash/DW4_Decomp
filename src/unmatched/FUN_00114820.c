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

void *memset(void *dst, int value, unsigned int size);
int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_001147f0(int arg);
void FUN_00114800(int mode);
void FUN_00114810(int arg);
void FUN_00115ae8(void);
int AddIntcHandler__0010abd0(int cause, void *handler, int next, void *arg);
int FUN_0010ba28(int cause);
int FUN_00114dc0();
extern Alarm D_0055a940[128];

int FUN_00114820(int clock)
{
    int i;
    int handler;
    int state;
    int mode;
    if (D_00483508.handler >= 0) {
        return 0x80008001;
    }
    D_00483508.count = 0;
    D_00483508.active = 0;
    memset(D_0055a940, 0, sizeof(D_0055a940));
    D_00483508.free_list = D_0055a940;
    for (i = 127; i >= 0; i--) {
        D_0055a940[i].next = &D_0055a940[i + 1];
    }
    D_0055a940[127].next = 0;
    FUN_00115ae8();
    handler = AddIntcHandler__0010abd0(11, FUN_00114dc0, 0, 0);
    if (handler < 0) {
        return 0x80009021;
    }
    D_00483508.handler = handler;
    state = FUN_00113f20();
    mode = *(volatile int *)0x10001010;
    mode = (mode & 0xFFFFFFFC) | clock;
    mode |= 0x300;
    if (!(mode & 0x80)) {
        mode |= 0xC80;
        FUN_001147f0(0);
        FUN_00114810(0xFFFF);
    }
    FUN_00114800(mode);
    FUN_0010ba28(11);
    if (state) {
        FUN_00113f78();
    }
    return 0;
}
