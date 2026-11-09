typedef struct AdxtCreateWork AdxtCreateWork;
struct AdxtCreateWork {
    short used;
    char pad2[6];
    void *rna;
    char pad12[44];
    int f56;
    int f60;
    int f64;
    int f68;
    char pad72[48];
    void (*cb120)(AdxtCreateWork *, int, int);
    AdxtCreateWork *obj124;
    void (*cb128)(AdxtCreateWork *, int, int);
    AdxtCreateWork *obj132;
    char pad136[68];
    int f204;
    char f208[16];
    short f224;
    short f226;
    short f228;
    char pad230[30];
};

extern AdxtCreateWork DAT_00498c80[16];
void *memset(void *dst, int value, unsigned int size);
void *FUN_0026ee98(void);
void FUN_0025d4f8(AdxtCreateWork *p);
void FUN_0025d370(AdxtCreateWork *p, int a, int b);
void FUN_0025d3a0(AdxtCreateWork *p, int a, int b);

/* matching construct: store-order search over the eight stores, 117 of 150 steps */
AdxtCreateWork *FUN_0025d3c0(int a0, int a1, int a2, int a3)
{
    AdxtCreateWork *p;
    int i;

    for (i = 0; i < 16; i++) {
        if (DAT_00498c80[i].used == 0) {
            break;
        }
    }
    if (i == 16) {
        return 0;
    }
    p = &DAT_00498c80[i];
    memset(p, 0, sizeof(*p));
    p->used = 1;
    p->rna = FUN_0026ee98();
    if (p->rna == 0) {
        FUN_0025d4f8(p);
        return 0;
    }
    p->f56 = a0;
    p->f60 = a1;
    p->f64 = a2;
    p->f68 = a3;
    p->cb120 = FUN_0025d370;
    p->obj124 = p;
    p->obj132 = p;
    p->cb128 = FUN_0025d3a0;
    p->f204 = 0;
    p->f224 = 0;
    p->f226 = -128;
    p->f228 = -128;
    memset(p->f208, 0, 16);
    return p;
}
