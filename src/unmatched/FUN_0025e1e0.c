typedef struct {
    int f0;
    int len;
    int nch;
    int f12;
    int blk;
    void *f20;
    int top;
    int f28;
    int pos;
    int lim;
    int end;
} AdxBuf;

typedef struct {
    char pad0[8];
    void *rna;
    char pad12[52];
    int f64;
    int f68;
    AdxBuf buf;
    char pad116[28];
    int f144;
    int f148;
    char pad152[80];
    int f232;
} AdxDec;

int FUN_0026f148(void *rna);
void FUN_0025e150(void *dst, int size, int a, int n);
void FUN_0025e1c0(void *dst, int size, int a, int n);

/* matching construct: statement-order search, first step */
void FUN_0025e1e0(AdxDec *d)
{
    AdxBuf *b = &d->buf;
    int blk;
    int nch;
    int t;
    int r;
    int q;
    int done;
    int n;
    int pos;
    int size;
    int a;
    int f12;
    void *dst;

    blk = b->blk;
    t = b->end + blk - 1;
    size = d->f64;
    dst = b->f20;
    a = d->f68;
    f12 = b->f12;
    q = t / blk;
    r = blk - t % blk - 1;
    pos = b->pos;
    done = FUN_0026f148(d->rna);
    nch = b->nch;
    n = done * blk / nch;
    n = (done < q * nch) ? n : n - r;
    pos += n;
    d->f148 = done * f12;
    d->f144 = n;
    if (pos >= size) {
        pos -= size;
        if (b->nch == 2 || d->f232 != 0) {
            FUN_0025e150(dst, size, a, pos);
        } else {
            FUN_0025e1c0(dst, size, a, pos);
        }
    }
}
