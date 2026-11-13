typedef struct { unsigned int src; unsigned int dest; int size; int attr; } Dma;
typedef struct { char p0[16]; int rec; int p1; int rpc_id; void *client; int cid; char p2[28]; } Pkt;
typedef struct { int p0; void *(*func)(int, void *, int); void *buf; int size; char p1[12]; void *client; void *paddr; int rpc; void *recv; int rsize; int rmode; unsigned int rid; } Sd;
extern char _sif_rpc_data[];
void sceSifWriteBackDCache(void *, int);
int DIntr(void);
int EIntr(void);
Pkt *_sceRpcGetFPacket2(void *, unsigned int);
Pkt *_sceRpcGetFPacket(void *);
int FUN_0010d6c8(int, void *, int, void *, void *, int);
int FUN_0010b2a0(Dma *, int);
void sceSifExecRequest(Sd *sd) {
    Dma dmat[2];
    int size = 0;
    void *rec;
    Pkt *rend;
    int n;
    int i;
    int r;
    rec = sd->func(sd->rpc, sd->buf, sd->size);
    if (rec) size = sd->rsize;
    if (sd->size > 0) sceSifWriteBackDCache(sd->buf, sd->size);
    if (size > 0) sceSifWriteBackDCache(rec, size);
    DIntr();
    if (sd->rid & 4) {
        rend = _sceRpcGetFPacket2(_sif_rpc_data, sd->rid >> 16);
    } else {
        rend = _sceRpcGetFPacket(_sif_rpc_data);
    }
    EIntr();
    rend->cid = 0x8000000a;
    rend->client = sd->client;
    if (sd->rmode) {
        while (!FUN_0010d6c8(0x80000008, rend, 64, rec, sd->recv, size));
        return;
    }
    rend->rpc_id = 0;
    rend->rec = 0;
    n = 0;
    if (size > 0) {
        n = 1;
        dmat[0].src = (unsigned int)rec;
        dmat[0].dest = (unsigned int)sd->recv;
        dmat[0].size = size;
        dmat[0].attr = 0;
    }
    dmat[n].src = (unsigned int)rend;
    dmat[n].dest = (unsigned int)sd->paddr;
    dmat[n].size = 64;
    dmat[n].attr = 0;
    n++;
    do {
        r = FUN_0010b2a0(dmat, n);
        if (!r) {
            i = 0x100000;
            while (i--);
        }
    } while (!r);
}
