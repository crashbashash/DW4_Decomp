typedef struct _sif_queue_data {
    int key;
    int active;
    struct _sif_serve_data *link;
    struct _sif_serve_data *start;
    struct _sif_serve_data *end;
    struct _sif_queue_data *next;
} sceSifQueueData;
typedef struct SifRpcData {
    int pid;
    void *pkt_table;
    int pkt_table_len;
    int unused1;
    int unused2;
    void *rdata_table;
    int rdata_table_len;
    void *client_table;
    int client_table_len;
    int rdata_table_idx;
    sceSifQueueData *active_queue;
} SifRpcData;
extern SifRpcData _sif_rpc_data;
int DIntr(void);
int EIntr(void);
void sceSifSetRpcQueue(sceSifQueueData *qd, int key) {
    sceSifQueueData *q;
    DIntr();
    qd->key = key;
    qd->active = 0;
    qd->link = 0;
    qd->start = 0;
    qd->end = 0;
    qd->next = 0;
    if (_sif_rpc_data.active_queue == 0) {
        _sif_rpc_data.active_queue = qd;
    } else {
        q = _sif_rpc_data.active_queue;
        while (q->next != 0) q = q->next;
        q->next = qd;
    }
    EIntr();
}
