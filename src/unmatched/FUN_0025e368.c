typedef struct {
    char pad0[16];
    int nblk;
    char pad20[12];
    short *src;
    short *dst;
} AdxRnaBuf;

typedef struct AdxtWork AdxtWork;
struct AdxtWork {
    short used;
    char pad2[2];
    int stat;
    AdxRnaBuf *rna;
    char pad12[92];
    int f104;
    int f108;
    int f112;
    char pad116[4];
    int (*cb120)(int obj, int *a, int *b, int *c);
    int obj124;
    void (*cb128)(int obj, int a, int b);
    int obj132;
    char pad136[8];
    int f144;
    int f148;
    char pad152[80];
    int f232;
};

extern void (*DAT_00498c6c)(AdxtWork *w, int v, short *src, short *dst);
int FUN_0026f050(AdxRnaBuf *rna);
void FUN_0026f160(AdxRnaBuf *rna);
void FUN_0026f130(AdxRnaBuf *rna);
void FUN_0025e018(AdxtWork *w);
void FUN_0025e1e0(AdxtWork *w);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);

void FUN_0025e368(AdxtWork *w)
{
    AdxRnaBuf *rna;
    int i;

    if (w->stat == 1) {
        if (FUN_0026f050(w->rna) == 0) {
            w->cb120(w->obj124, &w->f104, &w->f108, &w->f112);
            FUN_0025e018(w);
            w->stat = 2;
        }
    }
    if (w->stat == 2) {
        FUN_0026f160(w->rna);
        if (FUN_0026f050(w->rna) == 3) {
            if (w->f232 != 0) {
                rna = w->rna;
                FUN_0025f2d0();
                for (i = 0; i < rna->nblk * 32; i++) {
                    DAT_00498c6c(w, rna->src[i], &rna->src[i], &rna->dst[i]);
                }
                FUN_0025f2e8();
            }
            FUN_0025e1e0(w);
            FUN_0026f130(w->rna);
            w->cb128(w->obj132, w->f148, w->f144);
            w->stat = 3;
        }
    }
}
