typedef struct {
    int f0;
    int used;
    char pad8[4];
    int f12;
    int f16;
    int f20;
    int f24;
    char pad28[4];
    int f32;
    int f36;
    char pad40[16];
    void (*err)(int, int);
    int errobj;
} SjNode;

void SJERR_CallErr(const char *message);
extern char DAT_004f1fc8[];
extern char DAT_004f1ff8[];

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int FUN_0027c648(SjNode *sj, int line, int nbyte, int *out)
{
    int n;

    if (sj == 0) {
        SJERR_CallErr(DAT_004f1fc8);
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr(DAT_004f1ff8);
        return 0;
    }
    if (line == 0) {
        n = sj->f32 - sj->f20 + sj->f36;
        n = MIN(sj->f16, n);
        n = MIN(n, nbyte);
    } else if (line == 1) {
        n = sj->f32 - sj->f24 + sj->f36;
        n = MIN(sj->f12, n);
        n = MIN(n, nbyte);
    } else {
        n = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, -3);
        }
    }
    *out = n;
    return n == nbyte;
}
