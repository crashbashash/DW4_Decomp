typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; unsigned int option; } SemaParam;
typedef struct { char p0[20]; void *paddr; int rid; void *client; int src; int dest; int size; char p1[20]; } Pkt;
typedef struct { Pkt *pkt; int rid; int sema; int p0; int command; char p1[16]; void *server; } Client;
extern char _sif_rpc_data[];
Pkt *_sceRpcGetPacket(void *);
void FUN_0010dbb0(Pkt *);
int FUN_0010aee0(SemaParam *);
int FUN_0010aef0(int);
int FUN_0010af20(int);
int FUN_0010d6c8(int, Pkt *, int, int, int, int);
int FUN_0010de20(Client *cd, int src, int dest, int size, int mode) {
    SemaParam sp;
    Pkt *pkt;
    pkt = _sceRpcGetPacket(_sif_rpc_data);
    if (pkt == 0) return -1;
    cd->pkt = pkt;
    cd->rid = pkt->rid;
    pkt->src = src;
    pkt->dest = dest;
    pkt->size = size;
    pkt->paddr = pkt;
    pkt->client = cd;
    if (!(mode & 1)) {
        sp.init_count = 0;
        sp.max_count = 1;
        cd->sema = FUN_0010aee0(&sp);
        if (cd->sema < 0) {
            FUN_0010dbb0(pkt);
            return -3;
        }
        if (FUN_0010d6c8(0x8000000c, pkt, 64, 0, 0, 0) == 0) {
            FUN_0010dbb0(pkt);
            FUN_0010aef0(cd->sema);
            return -2;
        }
        FUN_0010af20(cd->sema);
        FUN_0010aef0(cd->sema);
        return 0;
    }
    cd->sema = -1;
    if (FUN_0010d6c8(0x8000000c, pkt, 64, 0, 0, 0) == 0) {
        FUN_0010dbb0(pkt);
        return -2;
    }
    return 0;
}
