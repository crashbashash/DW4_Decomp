typedef struct { unsigned short len; } Hdr;
typedef struct { int size; int count; char *rd; char *wr; } Q;
typedef struct { volatile int id; volatile int len; volatile int rlen; volatile int busy; char *tx; char *rx; Q *q; } D;
extern char DAT_004d2448[];
extern char DAT_004d2470[];
extern char DAT_004d2488[];
extern char DAT_004d24a0[];
int FUN_0010d0d0(const char *, ...);
int FUN_0010c150(int, char *, unsigned short);
int FUN_0010c188(int, char *, unsigned short);
void FUN_0010c290(Q *);
void sceTtyHandler(int event, int param, D *d) {
    int r;
    int i;
    Hdr *h;
    switch (event) {
    case 1:
    case 2:
        if (param != 0) {
            if ((unsigned int)(d->rlen + param) > 320) FUN_0010d0d0(DAT_004d2448);
            param = FUN_0010c150(d->id, d->rx + d->rlen, param);
            if (param < 0) FUN_0010d0d0(DAT_004d2470);
            d->rlen += param;
        } else {
            h = (Hdr *)d->rx;
            for (param = 12; param < h->len; param++) {
                *d->q->wr = d->rx[param];
                FUN_0010c290(d->q);
            }
            d->rlen = 0;
        }
        break;
    case 3:
        r = FUN_0010c188(d->id, d->tx, d->len);
        if (r < 0) {
            FUN_0010d0d0(DAT_004d2488, r);
            d->busy = 0;
        } else {
            d->tx += r;
            d->len -= r;
        }
        break;
    case 4:
        if (d->len) FUN_0010d0d0(DAT_004d24a0, d->len);
        d->busy = 0;
        break;
    }
}
