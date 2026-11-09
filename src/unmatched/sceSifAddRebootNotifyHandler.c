typedef void (*NotifyHandler)(void *arg, void *data);
typedef struct {
    NotifyHandler func;
    void *data;
    void *gp;
    int pad;
} NotifyEntry;
extern NotifyEntry DAT_0055cd48[32];
extern NotifyEntry *DAT_00483528;
extern unsigned int DAT_0048352c;
int FUN_00113f20(void);
int FUN_00113f78(void);
static inline void *currentGp(void) {
    void *gp;
    __asm__ volatile("move %0,$28" : "=r"(gp));
    return gp;
}
int sceSifAddRebootNotifyHandler(unsigned int index, NotifyHandler func, void *data) {
    NotifyEntry *table;
    unsigned int count;
    int interrupts;
    if ((int)index < 0) {
        index &= 0x7FFFFFFF;
        table = DAT_0055cd48;
        count = 32;
    } else {
        table = DAT_00483528;
        count = DAT_0048352c;
    }
    if (index >= count) return 0x80000069;
    interrupts = FUN_00113f20();
    table[index].func = func;
    table[index].data = data;
    table[index].gp = currentGp();
    if (interrupts) FUN_00113f78();
    return 0;
}
