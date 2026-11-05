extern "C" {
struct Ent { int f0; int f4; int f8; int f12; int f16; int f20; float f24; int f28; int f32; int f36; int f40; int f44; };
struct Pool { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; unsigned short *f12; Ent *f16; };
int memset(void *p, int v, int n);
Ent *thunk_FUN_002ed3b0(Ent *p, int n, int a);
}
class Buf { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual unsigned short *vB(unsigned short *p, int n); };
struct Src { int f0; int f4; int f8; int f12; int f16; int f20; int f24; float f28; };
struct Obj { char pad[868]; Pool *f868; int f872; };
extern "C" Buf *Memory_FindBufferOwner(Pool *p);
extern "C" int Gap__Core__igPsx2VisualContext__vfunc_46(Obj *arg0, Src *arg1);
int Gap__Core__igPsx2VisualContext__vfunc_46(Obj *arg0, Src *arg1) {
    Pool *p;
    Ent *e;
    int s0;
    int i;
    p = arg0->f868;
    if (p->f4 <= 0) {
        p->f16 = thunk_FUN_002ed3b0(p->f16, (p->f0 + 4) * 48, 16);
        memset(p->f16 + p->f0, 0, 192);
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
    e = arg0->f868->f16 + s0;
    e->f28 = arg1->f0;
    e->f0 = arg1->f4;
    e->f4 = arg1->f8;
    e->f8 = arg1->f12;
    e->f16 = arg1->f16;
    e->f12 = arg1->f20;
    e->f20 = arg1->f24;
    e->f24 = arg1->f28;
    e->f40 = 0;
    e->f44 = 0;
    e->f36 = -1;
    arg0->f872 = s0;
    return s0;
}
