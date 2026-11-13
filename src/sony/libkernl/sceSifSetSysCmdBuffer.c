typedef void (*SifCmdHandler)(void *packet, void *data);
typedef struct {
    SifCmdHandler func;
    void *data;
    void *gp;
} SifCmdSlot;
typedef struct {
    void *pktbuf;
    void *unused;
    void *iopbuf;
    SifCmdSlot *sysTable;
    int sysCount;
    SifCmdSlot *userTable;
    int userCount;
} SifCmdState;
extern SifCmdState _sif_cmd_data;

SifCmdSlot *sceSifSetSysCmdBuffer(SifCmdSlot *table, int count) {
    SifCmdSlot *old = _sif_cmd_data.sysTable;
    _sif_cmd_data.sysTable = table;
    _sif_cmd_data.sysCount = count;
    return old;
}
