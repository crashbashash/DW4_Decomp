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
extern SifCmdState _sif_cmd_data;
void sceSifAddCmdHandler(int cid, SifCmdHandler func, void *data) {
    if (cid < 0) {
        _sif_cmd_data.sysTable[cid & 0x7FFFFFFF].func = func;
        _sif_cmd_data.sysTable[cid & 0x7FFFFFFF].data = data;
        _sif_cmd_data.sysTable[cid & 0x7FFFFFFF].gp = GetGp();
    } else {
        _sif_cmd_data.userTable[cid].func = func;
        _sif_cmd_data.userTable[cid].data = data;
        _sif_cmd_data.userTable[cid].gp = GetGp();
    }
}
