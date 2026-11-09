typedef struct {
    void *data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} SifDmaData;

typedef struct {
    char pad0[60];
    int count;
} SifPeer;

typedef struct {
    char f0;
    signed char state;
    char busy;
    char f3;
    int f4;
    int count;
    char *buf;
    int size;
    SifPeer *peer;
    unsigned int dst;
    unsigned int dstsize;
    void (*recv)(int obj, char *buf, int size);
    int recv_obj;
    int (*send)(int obj, char *buf, int size);
    int send_obj;
    SifDmaData dma;
    unsigned int dmaid;
} SifChannel;

extern int DAT_004a9b28;
extern int DAT_004a9b1c;
void FUN_0010b918(char *start, char *end);
void FUN_0010b7d8(char *start, char *end);
unsigned int sceSifSetDma(SifDmaData *sdd, int len);

/* matching construct: statement-order sweep of the four DMA stores */
void FUN_00273558(SifChannel *ch)
{
    DAT_004a9b28++;
    if (ch->state == 1) {
        if (ch->count < ch->peer->count) {
            FUN_0010b918(ch->buf, ch->buf + ch->size - 1);
            ch->recv(ch->recv_obj, ch->buf, ch->size);
            ch->count = ch->peer->count;
            ch->state = 0;
        }
    }
    if (ch->state == 0 && ch->busy == 1) {
        if (DAT_004a9b1c == 1) {
            ch->send(ch->send_obj, ch->buf, ch->size);
            ch->count++;
            ch->peer->count = ch->count;
            FUN_0010b7d8(ch->buf, ch->buf + ch->size - 1);
            FUN_0010b918(ch->buf, ch->buf + ch->size + 63);
            ch->dma.data = (void *)((unsigned int)ch->buf & 0x0fffffff);
            ch->dma.addr = ch->dst;
            ch->dma.size = ch->dstsize;
            ch->dma.mode = 0;
            ch->dmaid = sceSifSetDma(&ch->dma, 1);
            ch->state = 1;
        }
    }
}
