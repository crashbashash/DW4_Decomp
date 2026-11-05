struct L { char p[8]; unsigned int n; char q[4]; unsigned int *data; 
static inline unsigned int cvt(unsigned int v, int mode) {
    unsigned int s;
    if (mode == 0x80) { return (v & 0xFFFFFF) | (((v >> 1) & 0x7F000000) + (v & 0x01000000)); }
    if (mode == 0xFF) { s = (v & 0x80000000) >> 7; return (v & 0xFFFFFF) | (s + (((v & 0xFF000000) - s) * 2)); }
    return v;
}
};
extern "C" void FUN_0017fd80(L **arg0, L **arg1, int arg2) {
    unsigned int i = 0;
    unsigned int v;
    L *l;
    while (i < (*arg0)->n) {
        v = (*arg0)->data[i];
        v = L::cvt(v, arg2);
        l = *arg1;
        if (l->n != 0 && (int)i >= 0 && (int)i < (int)l->n) {
            l->data[i] = v;
        }
        i++;
    }
}
