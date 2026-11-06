struct N { int pad0; int f4; struct N *f8; };
extern struct N *DAT_0056c290[4];
void FUN_0020d400(struct N *arg0, int arg1) {
    int acc;
    int v;
    struct N *prev;
    struct N *cur;
    struct N *t;
    acc = 0;
    cur = DAT_0056c290[0];
    prev = 0;
    if (cur == 0) {
        arg0->f4 = arg1;
        DAT_0056c290[0] = arg0;
        return;
    }
    while (cur != 0) {
        v = cur->f4;
        if (arg1 < acc + v) {
            arg0->f8 = cur;
            if (prev == 0) {
                arg0->f4 = arg1;
                DAT_0056c290[0]->f4 = DAT_0056c290[0]->f4 - arg0->f4;
                DAT_0056c290[0] = arg0;
            } else {
                prev->f8 = arg0;
                arg0->f4 = arg1 - acc;
                t = arg0->f8;
                t->f4 = t->f4 - arg0->f4;
            }
            break;
        }
        prev = cur;
        acc += v;
        cur = cur->f8;
    }
    if (cur == 0) {
        prev->f8 = arg0;
        arg0->f8 = 0;
        arg0->f4 = arg1 - acc;
    }
}
