struct ChainedBlock { char pad[12]; int start; int end; struct ChainedBlock *next; };
int memcpy();
int FUN_001eee40(struct ChainedBlock *arg0, int arg1) {
    struct ChainedBlock *p;
    int n;
    int m;
    int s;
    p = arg0;
    n = p->end - (s = p->start);
    memcpy(arg1, s, n);
    arg1 += n;
    while ((p = p->next) != 0) {
        arg1 -= 0x10;
        n -= 0x10;
        m = p->end - (s = p->start);
        memcpy(arg1, s, m);
        arg1 += m;
        n += m;
    }
    return n;
}
