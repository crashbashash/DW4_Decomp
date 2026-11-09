extern "C" {
typedef struct Ob { int w0; unsigned refs; int w2; } Ob;
typedef struct Hd { int w[5]; int f20; int w6[2]; Ob *f32; } Hd;
typedef struct O { int w[3]; Hd *f12; } O;
typedef struct Gl { int w[2]; int f8; } Gl;
extern int DAT_00586f20[4];
extern Gl *_impure_ptr[4];
extern char DAT_004fb390[];
int fflush(int);
Ob *FUN_002c72c0(int);
int FUN_00301000(void);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(void *);
int FUN_00308850(O *, Hd *);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        if (p != 0) {
            p->refs = p->refs - 1;
            if ((p->refs & 0x7fffff) == 0) igObject_Destroy(p);
        }
    }
};
static inline void setHeader(O *owner, const igSmartPointer<Ob> &value) {
    Ob *held = value.p;
    Ob *old;
    if (held != 0) held->refs = held->refs + 1;
    old = (Ob *)owner->f12;
    if (old != 0) {
        old->refs = old->refs - 1;
        if ((old->refs & 0x7fffff) == 0) igObject_Destroy(old);
    }
    owner->f12 = (Hd *)held;
}
extern "C" Hd *FUN_00308a90(O *arg0) {
    if (arg0->f12 == 0) {
        int *hd;
        int v;
        int s2;
        Hd *s0;
        int old;
        {
            igSmartPointer<Ob> created(FUN_002c72c0(FUN_00301000()));
            setHeader(arg0, created);
        }
        s0 = arg0->f12;
        if (0 == DAT_00586f20[0]) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s2 = StringPool_Intern(DAT_00586f20[0], DAT_004fb390);
        old = s0->f20;
        if (old != 0) {
            hd = (int *)(old - 8);
            v = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        s0->f20 = s2;
        arg0->f12->f32 = (Ob *)arg0;
        FUN_00308850(arg0, arg0->f12);
    }
    fflush(_impure_ptr[0]->f8);
    return arg0->f12;
}
