struct H { int *vt; unsigned refs : 23; unsigned flag : 1; unsigned char b7; };
extern int DAT_0052f0f0[4];
struct H *igObject_InitHeader(struct H *p) {
    p->vt = &DAT_0052f0f0[0];
    p->refs = 1;
    p->flag = 0;
    p->b7 = 0;
    return p;
}
