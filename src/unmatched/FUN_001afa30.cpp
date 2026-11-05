extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(int);
int List_RemoveWordAt(void *, int);
int igObject_Destroy(void *);
}
struct L {
    int w0; int rc; int n; int w12; int *data;
    inline int IndexOf(int v) {
        int cnt = n;
        int i;
        for (i = 0; i < cnt; i++) {
            if (v == data[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" L *DAT_00562580[4];
extern "C" void FUN_001afa30(int arg0) {
    volatile int sp2C;
    sp2C = arg0;
    int key = sp2C;
    L *l = DAT_00562580[0];
    int i = l->IndexOf(key);
    if (i >= 0) {
        List_RemoveWordAt(l, i);
    }
    L *p = DAT_00562580[0];
    if (p->n == 0) {
        p->rc = p->rc - 1;
        if ((p->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
        DAT_00562580[0] = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
