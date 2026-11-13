typedef void (*NotifyHandler)(void *arg, void *data);
typedef struct {
    NotifyHandler func;
    void *data;
    void *gp;
    int pad;
} NotifyEntry;
extern NotifyEntry rebootNotifySysTable[32];
extern NotifyEntry *rebootNotifyTable;
extern unsigned int rebootNotifyCount;

#define SCE_SIF_SYSTEM_NOTIFY 0x80000000
#define SCE_EINVAL -105

/* An id with the top bit set names a slot of the library's own table, otherwise one of the buffer sceSifSetRebootNotifyBuffer gave. */
int sceSifRemoveRebootNotifyHandler(unsigned int index) {
    NotifyEntry *table;
    unsigned int count;
    if ((int)index < 0) {
        index &= ~SCE_SIF_SYSTEM_NOTIFY;
        table = rebootNotifySysTable;
        count = 32;
    } else {
        table = rebootNotifyTable;
        count = rebootNotifyCount;
    }
    if (index >= count) return SCE_EINVAL;
    table[index].func = 0;
    return 0;
}
