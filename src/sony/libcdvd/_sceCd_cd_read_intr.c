typedef struct {
    int n0;
    int n1;
    unsigned char *dst0;
    unsigned char *dst1;
    unsigned char data0[64];
    unsigned char data1[64];
} Pkt;
extern int DAT_00483598;
void _sceCd_cd_callback(void *p);
void _sceCd_cd_read_intr(unsigned int addr) {
    Pkt *p;
    int i;
    unsigned char *d;
    unsigned char *u;
    p = (Pkt *)(addr | 0x20000000);
    if (p->n0 > 0) {
        u = (unsigned char *)((unsigned int)p->dst0 | 0x20000000);
        d = p->dst0;
        for (i = 0; i < p->n0; i++) {
            d[i] = u[i] = p->data0[i];
        }
    }
    if (p->n1 > 0) {
        u = (unsigned char *)((unsigned int)p->dst1 | 0x20000000);
        d = p->dst1;
        for (i = 0; i < p->n1; i++) {
            d[i] = u[i] = p->data1[i];
        }
    }
    _sceCd_cd_callback(&DAT_00483598);
}
