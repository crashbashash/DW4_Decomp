typedef void (*NotifyHandler)(void *arg, void *data);
typedef struct {
    NotifyHandler func;
    void *data;
    void *gp;
    int pad;
} NotifyEntry;
extern NotifyEntry DAT_0055cd48[32];
extern NotifyEntry *DAT_00483528;
extern int DAT_0048352c;
static inline void *currentGp(void) {
    void *gp;
    __asm__ volatile("move %0,$28" : "=r"(gp));
    return gp;
}
static inline void *swapGp(void *gp) {
    void *old;
    __asm__ volatile("move %0,$28; move $28,%1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
void sceSifExecNotifyHandler(int builtin, void *arg) {
    NotifyEntry *entry;
    int count;
    int i;
    void *savedGp;
    if (builtin) {
        entry = DAT_0055cd48;
        count = 32;
    } else {
        entry = DAT_00483528;
        count = DAT_0048352c;
    }
    savedGp = currentGp();
    for (i = 0; i < count; i++) {
        if (entry[i].func) {
            swapGp(entry[i].gp);
            entry[i].func(arg, entry[i].data);
        }
    }
    swapGp(savedGp);
}
