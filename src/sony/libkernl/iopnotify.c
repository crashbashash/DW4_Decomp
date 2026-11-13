/* iopnotify.c - the handlers sceSifResetIop and sceSifSyncIop call around an IOP reboot: the
 * library's own 32 and those of a buffer the program supplies. */
#include "dw4/eekernel_gp.h"
#include "dw4/libkernl.h"

/* an index with this bit set names a slot of the library's own table */
#define SCE_SIF_SYSTEM_NOTIFY 0x80000000
#define SYSTEM_NOTIFY_SLOTS 32
#define SCE_EINVAL 105
/* the kernel's error form, which Add returns; Remove returns -SCE_EINVAL */
#define KE_EINVAL (0x80000000 | SCE_EINVAL)

typedef void (*NotifyHandler)(void *arg, void *data);

/* a handler, its data and the $gp it runs with */
typedef struct {
    NotifyHandler func;
    void *data;
    void *gp;
    int pad;
} NotifyEntry;

void *memset(void *dst, int value, unsigned int size);

extern NotifyEntry *rebootNotifyTable;
extern unsigned int rebootNotifyCount;
extern NotifyEntry rebootNotifySysTable[SYSTEM_NOTIFY_SLOTS];

void sceSifInitRebootNotify(void)
{
    rebootNotifyTable = 0;
    rebootNotifyCount = 0;
    memset(rebootNotifySysTable, 0, sizeof(rebootNotifySysTable));
}

/* Gives the library the program's table of `count` handlers; returns the table it had. */
NotifyEntry *sceSifSetRebootNotifyBuffer(NotifyEntry *table, int count)
{
    int intr;
    NotifyEntry *old;
    intr = DIntr();
    old = rebootNotifyTable;
    rebootNotifyTable = table;
    rebootNotifyCount = count;
    memset(table, 0, count << 4);
    if (intr) EIntr();
    return old;
}

int sceSifAddRebootNotifyHandler(unsigned int index, NotifyHandler func, void *data)
{
    NotifyEntry *table;
    unsigned int count;
    int intr;
    if ((int)index < 0) {
        index &= ~SCE_SIF_SYSTEM_NOTIFY;
        table = rebootNotifySysTable;
        count = SYSTEM_NOTIFY_SLOTS;
    } else {
        table = rebootNotifyTable;
        count = rebootNotifyCount;
    }
    if (index >= count) return KE_EINVAL;
    intr = DIntr();
    table[index].func = func;
    table[index].data = data;
    table[index].gp = GetGp();
    if (intr) EIntr();
    return 0;
}

int sceSifRemoveRebootNotifyHandler(unsigned int index)
{
    NotifyEntry *table;
    unsigned int count;
    if ((int)index < 0) {
        index &= ~SCE_SIF_SYSTEM_NOTIFY;
        table = rebootNotifySysTable;
        count = SYSTEM_NOTIFY_SLOTS;
    } else {
        table = rebootNotifyTable;
        count = rebootNotifyCount;
    }
    if (index >= count) return -SCE_EINVAL;
    table[index].func = 0;
    return 0;
}

/* Calls every handler of the library's table (`system` set) or the program's, each with its own $gp. */
void sceSifExecNotifyHandler(int system, void *arg)
{
    NotifyEntry *entry;
    int count;
    int i;
    void *savedGp;
    if (system) {
        entry = rebootNotifySysTable;
        count = SYSTEM_NOTIFY_SLOTS;
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
