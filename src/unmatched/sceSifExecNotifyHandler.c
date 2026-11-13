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
extern int rebootNotifyCount;
void sceSifExecNotifyHandler(int builtin, void *arg) {
    NotifyEntry *entry;
    int count;
    int i;
    void *savedGp;
    if (builtin) {
        entry = rebootNotifySysTable;
        count = 32;
    } else {
        entry = rebootNotifyTable;
        count = rebootNotifyCount;
    }
    savedGp = GetGp();
    for (i = 0; i < count; i++) {
        if (entry[i].func) {
            SetGp(entry[i].gp);
            entry[i].func(arg, entry[i].data);
        }
    }
    SetGp(savedGp);
}
