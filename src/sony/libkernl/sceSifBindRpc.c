typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; unsigned int option; } SemaParam;
typedef struct { char p0[20]; void *paddr; int rid; void *client; int rpc; char p1[28]; } Pkt;
typedef struct { Pkt *pkt; int rid; int sema; int p0; int command; char p1[16]; void *server; } Client;
extern char _sif_rpc_data[];
Pkt *_sceRpcGetPacket(void *);
void FUN_0010dbb0(Pkt *);
int FUN_0010aee0(SemaParam *);
int FUN_0010aef0(int);
int FUN_0010af20(int);
int FUN_0010d6c8(int, Pkt *, int, int, int, int);
int sceSifBindRpc(Client *cd, int rpc, int mode) {
    SemaParam sp;
    Pkt *pkt;
    cd->command = 0;
    cd->server = 0;
    pkt = _sceRpcGetPacket(_sif_rpc_data);
    if (pkt == 0) return -1;
    cd->pkt = pkt;
    cd->rid = pkt->rid;
    pkt->rpc = rpc;
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
        if (FUN_0010d6c8(0x80000009, pkt, 64, 0, 0, 0) == 0) {
            FUN_0010dbb0(pkt);
            FUN_0010aef0(cd->sema);
            return -2;
        }
        FUN_0010af20(cd->sema);
        FUN_0010aef0(cd->sema);
        return 0;
    }
    cd->sema = -1;
    if (FUN_0010d6c8(0x80000009, pkt, 64, 0, 0, 0) == 0) {
        FUN_0010dbb0(pkt);
        return -2;
    }
    return 0;
}
