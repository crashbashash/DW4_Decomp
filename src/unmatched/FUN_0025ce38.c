typedef struct {
    unsigned char *src;
    int limit;
    char pad8[12];
    short *dst;
    int total;
    int stride;
    int pos;
    int max;
    int f40;
} AdxPcmOut;

typedef struct AdxtWork AdxtWork;
struct AdxtWork {
    short used;
    char pad2[2];
    int stat;
    void *rna;
    char pad12[2];
    signed char nch;
    char pad15[57];
    AdxPcmOut pcm;
    char pad116[4];
    int (*cb120)(int obj, int *a, int *b, int *c);
    int obj124;
    void (*cb128)(int obj, int a, int b);
    int obj132;
    char pad136[8];
    int f144;
    int f148;
};

extern short DAT_00498a58[256];
int ADXPD_GetStat(void *rna);

void FUN_0025ce38(AdxtWork *w)
{
    AdxPcmOut *pcm;
    unsigned char *src;
    short *dst;
    short *dst2;
    int n;
    int i;

    pcm = &w->pcm;
    src = pcm->src;
    if (w->stat == 1) {
        if (ADXPD_GetStat(w->rna) == 0) {
            w->cb120(w->obj124, &pcm->pos, &pcm->max, &pcm->f40);
            n = pcm->total - pcm->pos;
            if (pcm->max < n) {
                n = pcm->max;
            }
            if (pcm->limit < n) {
                n = pcm->limit;
            }
            dst = pcm->dst + pcm->pos;
            if (w->nch == 2) {
                dst2 = pcm->dst + (pcm->stride + pcm->pos);
                for (i = 0; i < n; i++) {
                    dst[i] = DAT_00498a58[src[i * 2]];
                    dst2[i] = DAT_00498a58[src[i * 2 + 1]];
                }
            } else {
                for (i = 0; i < n; i++) {
                    dst[i] = DAT_00498a58[src[i]];
                }
            }
            w->stat = 2;
            w->f144 = n;
            w->f148 = n * w->nch;
        }
    }
    if (w->stat == 2) {
        w->cb128(w->obj132, w->f148, w->f144);
        w->stat = 3;
    }
}
