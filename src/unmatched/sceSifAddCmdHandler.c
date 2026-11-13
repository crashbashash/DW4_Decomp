#include "dw4/eekernel_gp.h"
typedef void (*SifCmdHandler)(void *packet, void *data);
typedef struct {
    SifCmdHandler func;
    void *data;
    void *gp;
} SifCmdSlot;
typedef struct {
    int pad0[3];
    SifCmdSlot *sysTable;
    int sysCount;
    SifCmdSlot *userTable;
} SifCmdState;
extern SifCmdState DAT_00555fd8;
void sceSifAddCmdHandler(int cid, SifCmdHandler func, void *data) {
    if (cid < 0) {
        DAT_00555fd8.sysTable[cid & 0x7FFFFFFF].func = func;
        DAT_00555fd8.sysTable[cid & 0x7FFFFFFF].data = data;
        DAT_00555fd8.sysTable[cid & 0x7FFFFFFF].gp = GetGp();
    } else {
        DAT_00555fd8.userTable[cid].func = func;
        DAT_00555fd8.userTable[cid].data = data;
        DAT_00555fd8.userTable[cid].gp = GetGp();
    }
}
