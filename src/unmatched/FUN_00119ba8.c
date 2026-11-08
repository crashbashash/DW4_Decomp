typedef struct {
    int n0;
    int n1;
    unsigned char *dst0;
    unsigned char *dst1;
    unsigned char data0[64];
    unsigned char data1[64];
} Pkt;
extern int DAT_00485198;
int FUN_0010af10(int sema);
void FUN_00119ba8(unsigned int arg) {
    Pkt *p;
    unsigned char *d;
    int i;
    p = (Pkt *)(arg | 0x20000000);
    if (p->n0 != 0) {
        d = p->dst0;
        for (i = 0; i < p->n0; i++) *d++ = p->data0[i];
    }
    if (p->n1 != 0) {
        d = p->dst1;
        for (i = 0; i < p->n1; i++) *d++ = p->data1[i];
    }
    FUN_0010af10(DAT_00485198);
}
