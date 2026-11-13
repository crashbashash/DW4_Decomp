#include "dw4/eekernel_gp.h"
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
int DIntr(void);
int EIntr(void);
int sceSifAddRebootNotifyHandler(unsigned int index, NotifyHandler func, void *data) {
    NotifyEntry *table;
    unsigned int count;
    int interrupts;
    if ((int)index < 0) {
        index &= 0x7FFFFFFF;
        table = rebootNotifySysTable;
        count = 32;
    } else {
        table = rebootNotifyTable;
        count = rebootNotifyCount;
    }
    if (index >= count) return 0x80000069;
    interrupts = DIntr();
    table[index].func = func;
    table[index].data = data;
    table[index].gp = GetGp();
    if (interrupts) EIntr();
    return 0;
}
