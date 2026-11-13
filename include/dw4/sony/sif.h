/* sif.h - libkernl's SIF command and RPC layer (Sony sifcmd.h, sifrpc.h): the packets the EE and the
 * IOP exchange, the command handler tables and the RPC client, server and queue blocks. */
#ifndef DW4_SONY_SIF_H
#define DW4_SONY_SIF_H

/* SIF command ids with the top bit set are system commands, indexed by the low bits. */
#define SIF_CMD_SYSTEM 0x80000000
#define SIF_CMD_SET_SREG 0x80000001
#define SIF_CMD_INIT_CMD 0x80000002
#define SIF_CMD_RPC_END 0x80000008
#define SIF_CMD_RPC_BIND 0x80000009
#define SIF_CMD_RPC_CALL 0x8000000a
#define SIF_CMD_RPC_RDATA 0x8000000c

/* sceSifBindRpc/sceSifCallRpc/sceSifGetOtherData mode: return without waiting for the reply */
#define SIF_RPCM_NOWAIT 0x01
/* the packet's rec_id: in use, and the reply goes to a client-table packet */
#define SIF_RPC_PKT_USED 0x01
#define SIF_RPC_PKT_CLIENT 0x04

#define SIF_CMD_PACKET_SIZE 64

typedef struct {
    unsigned int size; /* packet size in the low byte, extra data size above it */
    void *dest;
    int cid;
    unsigned int opt;
} sceSifCmdHdr;

typedef void (*sceSifCmdHandler)(void *packet, void *harg);

typedef struct {
    sceSifCmdHandler func;
    void *data;
    void *gp;
} sceSifCmdData;

/* sceSifGetDataTable's block */
typedef struct {
    void *pktbuf;
    void *unused;
    void *iopbuf;
    sceSifCmdData *sysTable;
    int sysCount;
    sceSifCmdData *userTable;
    int userCount;
    unsigned int *sregs;
} sceSifCmdState;

typedef struct {
    sceSifCmdHdr hdr;
    int index;
    unsigned int value;
} sceSifCmdSRegData;

typedef struct {
    sceSifCmdHdr hdr;
    void *iopbuf;
} sceSifCmdChangeAddr;

typedef void *(*sceSifRpcFunc)(unsigned int fno, void *data, int size);
typedef void (*sceSifEndFunc)(void *param);

struct _sif_serve_data;
struct _sif_queue_data;

typedef struct {
    void *paddr; /* this client's packet */
    unsigned int pid;
    int tid; /* semaphore the caller waits on, or -1 */
    unsigned int mode;
} sceSifRpcData;

typedef struct _sif_client_data {
    sceSifRpcData rpcd;
    unsigned int command;
    void *buff;
    void *gp; /* the caller's $gp for its end function */
    sceSifEndFunc func;
    void *para;
    struct _sif_serve_data *serve;
} sceSifClientData;

typedef struct {
    sceSifRpcData rpcd;
    void *src;
    void *dest;
    int size;
} sceSifReceiveData;

typedef struct _sif_serve_data {
    unsigned int command;
    sceSifRpcFunc func;
    char *buff;
    int size;
    sceSifRpcFunc cfunc;
    char *cbuff;
    int csize;
    sceSifClientData *client;
    unsigned int paddr; /* the IOP's packet */
    unsigned int fno;
    unsigned int receive; /* the IOP's buffer for the result */
    int rsize;
    int rmode;
    unsigned int rid;
    void *link; /* sceSifServeData: the queue's servers */
    void *next; /* sceSifServeData: the queue's pending requests */
    struct _sif_queue_data *base;
} sceSifServeData;

typedef struct _sif_queue_data {
    int key; /* the serving thread */
    int active;
    void *link; /* sceSifServeData */
    sceSifServeData *start;
    void *end; /* sceSifServeData */
    struct _sif_queue_data *next;
} sceSifQueueData;

/* Every RPC packet starts with these words; the rest depends on the command. */
typedef struct {
    sceSifCmdHdr hdr;
    unsigned int rec_id; /* packet index << 16 | SIF_RPC_PKT_* */
    void *pkt_addr;
    unsigned int rpc_id;
} sceSifRpcPktHeader;

typedef struct {
    sceSifRpcPktHeader rpch;
    sceSifClientData *client;
    unsigned int sid;
    char pad[SIF_CMD_PACKET_SIZE - 36];
} sceSifRpcBindPkt;

typedef struct {
    sceSifRpcPktHeader rpch;
    void *client;
    unsigned int fno;
    int ssize;
    unsigned int receive; /* the IOP's buffer for the result */
    int rsize;
    int rmode;
    sceSifServeData *serve;
    char pad[SIF_CMD_PACKET_SIZE - 56];
} sceSifRpcCallPkt;

typedef struct {
    sceSifRpcPktHeader rpch;
    sceSifReceiveData *recv;
    unsigned int src; /* the requester's side */
    unsigned int dest; /* the other side */
    int size;
    char pad[SIF_CMD_PACKET_SIZE - 44];
} sceSifRpcOtherDataPkt;

/* The reply: RPC_END names the command it ends; the words after it are that command's. */
typedef struct {
    sceSifCmdHdr hdr;
    unsigned int rec_id;
    unsigned int pkt_addr; /* the request's packet, echoed back */
    unsigned int rpc_id;
    unsigned int client; /* the requester's client or receive block, echoed back */
    unsigned int cid;
    union {
        struct {
            sceSifServeData *serve;
            void *buff;
        } bind;
        struct {
            unsigned int src;
            unsigned int dest;
            int size;
        } rdata;
    } u;
    char pad[SIF_CMD_PACKET_SIZE - 48];
} sceSifRpcRendPkt;

/* sifrpc's state: the packets clients send, the reply packets, and the server queues */
typedef struct {
    unsigned int pid; /* the last packet id handed out */
    void *pkt_table;
    int pkt_table_len;
    int unused1;
    int unused2;
    sceSifRpcRendPkt *rdata_table;
    int rdata_table_len;
    sceSifRpcRendPkt *client_table;
    int client_table_len;
    int rdata_table_idx;
    sceSifQueueData *active_queue;
} sceSifRpcState;

void sceSifInitCmd(void);
void sceSifExitCmd(void);
unsigned int sceSifGetSreg(int reg);
unsigned int sceSifSetSreg(int reg, unsigned int value);
sceSifCmdState *sceSifGetDataTable(void);
sceSifCmdData *sceSifSetCmdBuffer(sceSifCmdData *table, int count);
sceSifCmdData *sceSifSetSysCmdBuffer(sceSifCmdData *table, int count);
void sceSifAddCmdHandler(unsigned int cid, sceSifCmdHandler func, void *data);
void sceSifRemoveCmdHandler(unsigned int cid);
unsigned int sceSifSendCmd(unsigned int cid, void *packet, int size, void *src, void *dest, int len);
unsigned int isceSifSendCmd(unsigned int cid, void *packet, int size, void *src, void *dest, int len);
void sceSifWriteBackDCache(void *ptr, int size);

void sceSifInitRpc(unsigned int mode);
void sceSifExitRpc(void);
int sceSifGetOtherData(sceSifReceiveData *rd, void *src, void *dest, int size, unsigned int mode);
int sceSifBindRpc(sceSifClientData *client, unsigned int sid, unsigned int mode);
int sceSifCallRpc(sceSifClientData *client, unsigned int fno, unsigned int mode, void *send, int ssize,
                  void *receive, int rsize, sceSifEndFunc func, void *para);
int sceSifCheckStatRpc(sceSifRpcData *rpcd);
void sceSifSetRpcQueue(sceSifQueueData *queue, int key);
void sceSifRegisterRpc(sceSifServeData *serve, unsigned int command, sceSifRpcFunc func, void *buff,
                       sceSifRpcFunc cfunc, void *cbuff, sceSifQueueData *queue);
sceSifServeData *sceSifRemoveRpc(sceSifServeData *serve, sceSifQueueData *queue);
sceSifQueueData *sceSifRemoveRpcQueue(sceSifQueueData *queue);
sceSifServeData *sceSifGetNextRequest(sceSifQueueData *queue);
void sceSifExecRequest(sceSifServeData *serve);
void sceSifRpcLoop(sceSifQueueData *queue);

#endif
