extern "C" {
struct Ent { int f0; int f4; int f8; int f12; int f16; int f20; };
struct Pool { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; unsigned short *f12; Ent *f16; };
int memset(void *p, int v, int n);
int FUN_0016a800(Ent *e);
Ent *thunk_FUN_002ed3b0(Ent *p, int n, int a);
}
class Buf { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual unsigned short *vB(unsigned short *p, int n); };
struct Obj { char pad[328]; Pool *f328; };
extern "C" Buf *Memory_FindBufferOwner(Pool *p);
extern "C" int FUN_0016ad20(Obj *arg0, int arg1, int arg2);
int FUN_0016ad20(Obj *arg0, int arg1, int arg2) {
    Pool *p;
    Ent *e;
    int s0;
    int i;
    if (arg1 > 256) {
        return -1;
    }
    p = arg0->f328;
    if (p->f4 <= 0) {
        p->f16 = thunk_FUN_002ed3b0(p->f16, (p->f0 + 4) * 24, 16);
        memset(p->f16 + p->f0, 0, 96);
        if (p->f2 < 4) {
            Buf *b = Memory_FindBufferOwner(p);
            p->f12 = b->vB(p->f12, 8);
            p->f2 = 4;
        }
        i = 0;
        do {
            p->f12[i] = p->f0 + i;
            i++;
        } while (i < 4);
        p->f4 = 4;
        p->f0 = p->f0 + 4;
    }
    s0 = p->f12[p->f4 - 1];
    p->f4 = p->f4 - 1;
    e = arg0->f328->f16 + s0;
    FUN_0016a800(e);
    e->f20 = 0;
    e->f12 = arg2;
    e->f0 = arg1;
    e->f16 = 0;
    return s0;
}
