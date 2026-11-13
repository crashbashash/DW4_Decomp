typedef struct _sif_client_data sceSifClientData;
typedef struct {
    unsigned int command;
    void *func;
    void *buff;
} sceSifServeData;
/* SIF RPC packets behind the 16-byte SIF command header. */
typedef struct {
    int hdr[4];
    int rec_id;
    void *pkt_addr;
    int rpc_id;
    sceSifClientData *cd;
    unsigned int sid;
} SifRpcBindPkt;
typedef struct {
    int hdr[4];
    int rec_id;
    unsigned int pkt_addr;
    int rpc_id;
    unsigned int cd;
    unsigned int cid;
    void *sd;
    void *buf;
} SifRpcRendPkt;

#define SIF_CMD_RPC_END 0x80000008
#define SIF_CMD_RPC_BIND 0x80000009

SifRpcRendPkt *_sceRpcGetFPacket(void *data);
sceSifServeData *_search_svdata(unsigned int sid, void *data);
int isceSifSendCmd(unsigned int cid, void *pkt, int size, void *src, void *dest, int len);
void iSetTimerAlarm(int clock, void (*handler)(SifRpcRendPkt *), SifRpcRendPkt *arg);
void _alarm_bind(SifRpcRendPkt *rend);

/* The IOP asks to bind to an EE RPC server: answer with the server, retrying from an alarm while the send fails. */
void _request_bind(SifRpcBindPkt *bind, void *data)
{
    SifRpcRendPkt *rend;
    sceSifServeData *sd;
    rend = _sceRpcGetFPacket(data);
    rend->pkt_addr = (unsigned int)bind->pkt_addr;
    rend->cd = (unsigned int)bind->cd;
    rend->cid = SIF_CMD_RPC_BIND;
    sd = _search_svdata(bind->sid, data);
    if (sd == 0) {
        rend->sd = 0;
        rend->buf = 0;
    } else {
        rend->sd = sd;
        rend->buf = sd->buff;
    }
    if (isceSifSendCmd(SIF_CMD_RPC_END, rend, 64, 0, 0, 0) == 0) {
        iSetTimerAlarm(0x800, _alarm_bind, rend);
    }
}
