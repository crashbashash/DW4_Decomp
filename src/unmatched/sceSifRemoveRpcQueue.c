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

extern SifRpcData DAT_00557a00;
int FUN_00113f20(void);
int FUN_00113f78(void);

sceSifQueueData *sceSifRemoveRpcQueue(sceSifQueueData *qd) {
    sceSifQueueData *pq;
    FUN_00113f20();
    if ((pq = DAT_00557a00.active_queue) == qd) {
        DAT_00557a00.active_queue = pq->next;
    } else {
        while (pq != 0) {
            if (pq->next == qd) {
                pq->next = qd->next;
                break;
            }
            pq = pq->next;
        }
    }
    FUN_00113f78();
    return pq;
}
