typedef struct { char p0[200]; int a; char p1[36]; unsigned int b; int c; int d; int e; } M;
typedef struct { char pad[64]; M *sys; } sceMpeg;
int FUN_00109410(sceMpeg *);
int FUN_00108fd0(sceMpeg *mp, unsigned int addr, int size) {
    M *m = mp->sys;
    addr = (addr & 0x0fffffff) | 0x20000000;
    m->a = 1;
    m->b = addr;
    m->e = size;
    m->d = 0;
    m->c = 0;
    return FUN_00109410(mp);
}
