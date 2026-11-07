extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int memset(...);
int FUN_002f2260(...);
int FUN_00308320(...);
extern int DAT_004c2370[4];
extern int DAT_004fd640[4];
extern int DAT_00587200[4];
extern unsigned char GPR_00554d64;
extern unsigned char GPR_00554d68;
}
class Alloc { public:
    virtual void d0();
    virtual void d1();
    virtual int v2(int);
    virtual void d3();
    virtual int v4(int, int);
};
extern Alloc *DAT_00587218[4];
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)((long long)object->references << 0x29) >> 0x29) == 0)
            igObject_Destroy(object);
    }
} };
struct Arena { char p[2020]; int f2020; int f2024; int f2028; int f2032; char q[24]; int f2060; int f2064; };
struct Bits { unsigned refs : 23; unsigned rest : 9; };
class Pool { public:
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
    virtual void v49();
    int w4;
    char pad8[104];
    Arena *arena;
    unsigned char isActive;
    char pad117[3];
    T *lock;
    int raw;
    unsigned char alch;
    char pad129[7];
    unsigned long long sysAlloc;
    unsigned int elemSize;
    char pad148[4];
    unsigned long long maxSize;
    unsigned long long size;
    unsigned int preSize;
    unsigned short alignment;
    char pad174[2];
    T *tracker;
    int poolIndex;
    int heapLevel;
    int msgLevel;
    int optFlags;
    int preSized;
    unsigned int smallest;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_97(Pool *self);
void Gap__Core__igArenaMemoryPool__vfunc_97(Pool *self) {
    int v;
    FUN_002f2260(self);
    self->w4 = 0;
    ((Bits *)&self->w4)->refs = 1;
    ((char *)self)[7] = 0;
    self->arena = (Arena *)DAT_00587218[0]->v2(0x814);
    if (self->arena == 0 && GPR_00554d64 == 0) {
        v = FUN_00308320(&DAT_004fd640[0]);
        if (v != 1) {
            if (v == 2)
                GPR_00554d64 = 1;
        }
    }
    memset(self->arena, 0, 0x814);
    self->raw = 0;
    self->alch = 0;
    self->sysAlloc = 0;
    self->v49();
    self->maxSize = 0xFFFFFFFFFFFFFFFFULL;
    self->size = 0;
    self->preSize = 0;
    self->alignment = 1;
    Rel::go(self->tracker);
    self->tracker = 0;
    self->isActive = 0;
    DAT_00587200[0] = DAT_00587200[0] + 1;
    Rel::go(self->lock);
    self->lock = 0;
    self->poolIndex = 0;
    self->heapLevel = 0;
    self->msgLevel = 1;
    self->optFlags = DAT_004c2370[0] & ~8;
    self->preSized = 0;
    self->smallest = 16;
    if (self->arena->f2020 == 0) {
        self->arena->f2020 = DAT_00587218[0]->v4(0x200, 4);
        if (self->arena->f2020 == 0 && GPR_00554d68 == 0) {
            v = FUN_00308320(&DAT_004fd640[0]);
            if (v != 1) {
                if (v == 2)
                    GPR_00554d68 = 1;
            }
        }
        self->arena->f2024 = 0x200;
        self->arena->f2028 = 0;
        self->arena->f2032 = 0;
        self->arena->f2060 = -1;
        self->arena->f2064 = 0;
    }
}
