extern "C" {
int thunk_FUN_003065f0(int, int, void *, int *, int, int);
int FUN_00165d10(void *);
struct Buf;
Buf *Memory_AllocateBufferDirect(int, int);
void *Memory_FindBufferOwner(void *);
int FUN_002caa70(int);
int FUN_002eb010(int);
int StringPool_Construct(int);
int *StringPool_Intern(int, const char *);
void StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(void *);
extern char DAT_004e0800[];
extern int DAT_00586f20[4];
extern int *DAT_00586dc8[4];
}
struct T { int word0; int references; };
class Owner {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void *v224(int, int);
    virtual void *v228(int, int, int);
};
struct Buf { short s0, s2, s4; short pad6; int f8; short *f12; void *f16; };
struct Self { char p[324]; Buf *f324; int pad328; T *f332; int f336, f340; char p344[220]; char a564[16]; };
extern "C" void FUN_0017a300(Self *self) {
    int sp5C;
    int bi;
    Buf *b;
    T *o;
    int i;
    sp5C = 0x40;
    thunk_FUN_003065f0(*(int *)((char *)DAT_00586dc8[0] + 56), 4, DAT_004e0800, &sp5C, 0x40, 0);
    Buf *r = (Buf *)Memory_AllocateBufferDirect(0x14, FUN_00165d10(self));
    if (r != 0) {
        bi = (int)r;
        b = (Buf *)bi;
        int n = sp5C;
        Owner *ow;
        int k;
        int *old;
        int *tok;
        b->f8 = 0;
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        tok = StringPool_Intern(DAT_00586f20[0], DAT_004e0800);
        old = (int *)b->f8;
        if (old != 0) {
            int *h = old - 2;
            int c = old[-1] - 1;
            old[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
        b->f8 = (int)tok;
        if (n == 0) n = 1;
        ow = (Owner *)Memory_FindBufferOwner(b);
        b->f16 = ow->v228(n, 0x88, 0x10);
        b->f12 = (short *)ow->v224(n, 2);
        b->s2 = n;
        b->s0 = n;
        b->s4 = n;
        for (k = 0; k < n; k++) b->f12[k] = (short)k;
        r = (Buf *)bi;
    }
    self->f324 = r;
    self->f336 = -1;
    self->f340 = 1;
    i = 0;
    do {
        self->a564[i] = 0;
        i++;
    } while (i < 16);
    o = (T *)FUN_002caa70(FUN_00165d10(self));
    if (o != 0) o->references = o->references + 1;
    {
        T *old2 = self->f332;
        if (old2 != 0) {
            --old2->references;
            if (((unsigned long long)(long long)old2->references & 0x7fffffULL) == 0) igObject_Destroy(old2);
        }
    }
    self->f332 = o;
    {
        T *c = self->f332;
        --c->references;
        if (((unsigned long long)(long long)c->references & 0x7fffffULL) == 0) igObject_Destroy(c);
    }
}
