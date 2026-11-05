typedef struct { char pad[116]; unsigned a; unsigned long long len; int pad2; unsigned c; int d; unsigned char flag; } S;
void Gap__Core__igStackMemoryPool__vfunc_30(S *p) {
    unsigned v = p->a;
    if (v != 0) {
        p->c = v;
        p->d = (int)((unsigned long long)p->c + p->len + 0xFFFFFFFFFFFFFFFCULL);
        p->d = p->d - (p->d & 3);
        p->flag = 1;
    }
}
