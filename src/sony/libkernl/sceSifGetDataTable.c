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

SifCmdState *sceSifGetDataTable(void) {
    return &_sif_cmd_data;
}
