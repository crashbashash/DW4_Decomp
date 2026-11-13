typedef struct sceSifQueueData { char pad[20]; struct sceSifQueueData *next; } sceSifQueueData;
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

sceSifQueueData *sceSifRemoveRpcQueue(sceSifQueueData *qd) {
    sceSifQueueData *pq;
    DIntr();
    if ((pq = _sif_rpc_data.active_queue) == qd) {
        _sif_rpc_data.active_queue = pq->next;
    } else {
        while (pq != 0) {
            if (pq->next == qd) {
                pq->next = qd->next;
                break;
            }
            pq = pq->next;
        }
    }
    EIntr();
    return pq;
}
