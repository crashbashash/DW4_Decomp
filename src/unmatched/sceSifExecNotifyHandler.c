#include "dw4/eekernel_gp.h"
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
    savedGp = GetGp();
    for (i = 0; i < count; i++) {
        if (entry[i].func) {
            SetGp(entry[i].gp);
            entry[i].func(arg, entry[i].data);
        }
    }
    SetGp(savedGp);
}
