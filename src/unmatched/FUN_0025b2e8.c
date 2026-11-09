typedef struct Sj Sj;

typedef struct {
    signed char used;
    char stat;
    signed char nch;
    char pad3;
    Sj *sj[2];
    Sj *out[2];
    int f20[2];
    int nch_;
    int freq;
    float f36;
    float f40;
    int f44;
} AdxRna;

extern AdxRna DAT_00498738[16];
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);

/* matching construct: store-order search over the seven stores, 62 of 150 steps */
AdxRna *FUN_0025b2e8(int nch, Sj **sj, Sj **out)
{
    AdxRna *rna;
    int i;
    int ch;

    for (i = 0; i < 16; i++) {
        if (DAT_00498738[i].used == 0) {
            break;
        }
    }
    if (i == 16) {
        return 0;
    }
    FUN_0025f2d0();
    rna = &DAT_00498738[i];
    rna->nch = nch;
    for (ch = 0; ch < nch; ch++) {
        rna->f20[ch] = 0;
        rna->sj[ch] = sj[ch];
        rna->out[ch] = out[ch];
    }
    rna->freq = 44100;
    rna->stat = 0;
    rna->f44 = 0;
    rna->f36 = 0.1f;
    rna->nch_ = nch;
    rna->f40 = 0.1f;
    rna->used = 1;
    FUN_0025f2e8();
    return rna;
}
