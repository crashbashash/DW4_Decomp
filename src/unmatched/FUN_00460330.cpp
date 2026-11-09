typedef struct Obj { int w0; int references; } Obj;
typedef struct List { int pad0[2]; int count; int pad1; Obj **data; } List;
typedef struct Hold { char pad[28]; List *l28; } Hold;
typedef struct X { char pad[12]; int f12; } X;
class Ob { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); int pad; int f4x; };
typedef struct Mk { int vt; int refs; int f8; int f12; Obj *f16; } Mk;
typedef struct A { char pad[12]; X *f12; char pad2[32]; Hold *f48; char pad3[8]; List *f60; List *f64; char pad4[16]; Obj *f84; } A;
extern "C" {
Obj *FUN_001361b0(int);
int FUN_001c5d10(Hold *, int);
int FUN_001c5eb0(Obj **, Hold *, int);
int FUN_00460790(A *, int);
int ObjectList_AppendRetained(int, int);
int igObject_Destroy(Obj *);
void FUN_00460330(A *arg0);
}
#define CLEAR(src) { \
    List *l = (src); \
    int n = l->count; \
    int i; \
    int m; \
    int j; \
    Obj *o; \
    for (i = 0; i < n; i++) { \
        o = l->data[i]; \
        if (o != 0) { \
            o->references = o->references - 1; \
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->count; \
    for (j = 0; j < m; j++) { \
        l->data[j] = 0; \
    } \
    l->count = 0; }
void FUN_00460330(A *arg0) {
    Obj * volatile sp7C;
    Obj * sp78;
    volatile char sp74[1];
    Hold *a1;
    List *v1;
    int var_v1;
    Obj *t;
    int s5;
    int n3;
    Obj *s3;
    Mk *s2;
    int s0;
    Obj *tq;
    a1 = arg0->f48;
    v1 = a1->l28;
    if (v1 != 0) {
        var_v1 = v1->count;
    } else {
        var_v1 = 0;
    }
    if (var_v1 > 0) {
        FUN_001c5eb0((Obj **)&sp78, a1, 0);
        t = sp78;
        if (t != 0) {
            t->references = t->references - 1;
            t = sp78;
            if (((unsigned long long)((long long)t->references << 0x29) >> 0x29) == 0) igObject_Destroy(t);
        }
    }
    CLEAR(arg0->f64)
    CLEAR(arg0->f60)
    if (arg0->f12->f12 != 0) {
        FUN_001c5d10(arg0->f48, arg0->f12->f12);
        FUN_00460790(arg0, arg0->f12->f12);
    }
    n3 = arg0->f60->count;
    s5 = 0;
    if (0 < n3) {
        s0 = 0;
        do {
            sp74[0] = 0;
            sp7C = FUN_001361b0(0);
            s3 = *(Obj **)((char *)arg0->f60->data + s0);
            s2 = (Mk *)sp7C;
            if (s3 != 0) s3->references = s3->references + 1;
            tq = s2->f16;
            if (tq != 0) {
                tq->references = tq->references - 1;
                if (((unsigned long long)((long long)tq->references << 0x29) >> 0x29) == 0) igObject_Destroy(tq);
            }
            s2->f16 = s3;
            ((Ob *)sp7C)->v128(0);
            ObjectList_AppendRetained((int)arg0->f64, (int)sp7C);
            t = sp7C;
            if (t != 0) {
                t->references = t->references - 1;
                if (((unsigned long long)((long long)t->references << 0x29) >> 0x29) == 0) igObject_Destroy(t);
            }
            s5 += 1;
            s0 += 4;
        } while (s5 < n3);
    }
    t = arg0->f84;
    if (t != 0) {
        t->references = t->references - 1;
        if (((unsigned long long)((long long)t->references << 0x29) >> 0x29) == 0) igObject_Destroy(t);
    }
    arg0->f84 = 0;
}
