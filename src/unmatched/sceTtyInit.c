typedef struct { int size; int count; char *rd; char *wr; } Q;
typedef struct { unsigned short len; unsigned short rsvd; unsigned short proto; unsigned char src; char dst; int data; char buf[256]; } Hdr;
typedef struct { volatile int id; volatile int len; volatile int rlen; volatile int busy; Hdr *tx; Hdr *rx; Q *q; } D;
extern D DAT_00555bd0;
extern char DAT_00555c00[];
extern char DAT_00555d40[];
void FlushCache(int mode);
int sceDeci2Open(unsigned short protocol, void *opt, void (*handler)(int, void *));
void sceTtyHandler(int event, void *opt);
Q *FUN_0010c268(int size);
int sceTtyInit(void) {
    Hdr *tx;
    FlushCache(0);
    DAT_00555bd0.id = sceDeci2Open(0x210, &DAT_00555bd0, sceTtyHandler);
    if (DAT_00555bd0.id < 0) return 0;
    DAT_00555bd0.busy = 0;
    DAT_00555bd0.len = 0;
    DAT_00555bd0.rlen = 0;
    DAT_00555bd0.rx = (Hdr *)((unsigned int)DAT_00555d40 | 0x20000000);
    tx = (Hdr *)((unsigned int)DAT_00555c00 | 0x20000000);
    DAT_00555bd0.tx = tx;
    tx->proto = 0x210;
    tx->src = 'E';
    tx->dst = 'H';
    tx->rsvd = 0;
    tx->data = 0;
    DAT_00555bd0.q = FUN_0010c268(256);
    return 1;
}
