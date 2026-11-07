typedef struct { char pad[144]; unsigned int *tab[32]; } O;
int Gap__Core__igPageMemoryPool__vfunc_103(O *o, unsigned int arg1) {
    unsigned int *t;
    unsigned int v;
    t = o->tab[arg1 >> 27];
    if (t == 0) return 0;
    v = (arg1 & 0x7ffffff) >> 12;
    return ((1 << ((v & 0xF) * 2)) & t[v >> 4]) != 0;
}
