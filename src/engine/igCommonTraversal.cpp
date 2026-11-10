#include "dw4/reflected.h"

struct TravObject { int _vtable; unsigned int _refCount; int _id; };
struct TravObjectList { char pad[8]; int _count; int _capacity; TravObject **_data; };
struct TravFunctionTable { char pad[16]; int *_data; };
struct TravFlattenView { char pad[40]; TravObjectList *_a; TravObjectList *_b; };

struct NodeProcEntry { int meta; int proc; };
struct NodeProcTable { NodeProcEntry e[34]; } __attribute__((aligned(16)));

class igTimerSourceView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long getTime();
};
class H { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void vX(int, int); char p0[180]; igBitMask *f184; };
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int); };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); };

typedef struct A0 { char p0[32]; int f32; char p1[124]; int f160; char p2[12]; int f176; int f180; } A0;
typedef struct A1 { char p0[52]; int f52; char p1[12]; int f68; } A1;
typedef struct { char pad[64]; unsigned char flags; } T;
struct Rc { int vt; int rc; int w8; int w12; int f16; };
struct M4130 { char pad[12]; int f12; };
struct A4130 { char pad[8]; int f8; };
struct O4130 { char pad0[32]; struct M4130 *f32; char pad1[20]; struct A4130 *f56; char pad2[100]; struct Rc *f160; };
struct Q { char p0[8]; int count; char pc[4]; int *data; };
struct A4220 { char p0[144]; struct Q *f144; };
struct B4220 { char p0[52]; int f52; };
struct S4500 { char p0[12]; int k; char p1[100]; float firstX,firstY,firstZ,secondX,secondY,secondZ; };
struct O4500 { char p0[56]; float x,y,z; int w; char p1[64]; struct S4500 *s; };

extern igTimerSourceView *DAT_005871d8;
extern const NodeProcTable DAT_0048d8f0;

extern "C" {
extern igMetaObject *DAT_0055efe8[4];
extern int DAT_00561280;
extern int DAT_005612b0;
extern int DAT_005612d8;
extern int DAT_005612e0;
extern int DAT_00561308;
extern int DAT_00561570;
extern int DAT_00561578;
extern int DAT_005615d0;
extern int DAT_005615d8;
extern int DAT_00561620;
extern int DAT_005617a8;
extern int DAT_00561818;
extern int DAT_00561860;
extern int DAT_00561868;
extern int DAT_00561870;
extern int DAT_00561878;
extern int DAT_00561888;
extern int DAT_00561898;
extern int DAT_005618d8;
extern int DAT_005618e8;
extern int DAT_005618f8;
extern int DAT_00561908;
extern int DAT_00561910;
extern int DAT_00561920;
extern int DAT_00561a38;
extern int DAT_00561a98;
extern int DAT_00561bd8;
extern int DAT_00561ca0;
extern int DAT_00561e98;
extern int DAT_00561ee8;
extern int DAT_00561f38;
extern int DAT_00561f68;
extern int DAT_00562078;
extern int DAT_00562488;
extern int DAT_00562598[4];
extern int DAT_005625a0[4];
extern int DAT_005625a8[4];
extern int DAT_005625b0[4];
extern int DAT_005625b8[4];
extern int DAT_005625c0[4];
extern int DAT_005625c8[4];
extern int DAT_005625d0[4];
extern int DAT_005625d8[4];
extern int DAT_005625e0[4];
extern int DAT_005625e8[4];
extern void *DAT_005625f0;
extern VC *DAT_00562638[4];
extern TravFunctionTable *DAT_00562640;

int FUN_00130830(...);
int FUN_00130a70(...);
int FUN_00130cf0(...);
int FUN_001318f0(...);
int FUN_00132a00(...);
int FUN_001357e0(...);
int FUN_0013b110(...);
struct Rc *FUN_00140c00(...);
int FUN_00157200(...);
int FUN_0019a6e0(int);
int FUN_001b0ea0(...);
int FUN_001b12f0(...);
int FUN_001b13d0(...);
int FUN_001b1e50(...);
int FUN_001b3030(...);
int FUN_001c5660(...);
int FUN_001dc500(...);
int FUN_001dc610(...);
void FUN_001e02f0(void *, void *);
void FUN_001e06c0(...);
int FUN_001e07a0(...);
int FUN_002fe290(void *, int);
TravObject *FUN_002fe300(int, int);
int Gap__Core__igObject__vfunc_08__002ff0f0(...);
int Gap__Sg__igTraversal__vfunc_09(...);
int igMetaObject_CountTree(int);
int igNode_GetMetaObject(void);
int igObject_Destroy(...);
igMetaObject *igTextureBindAttr_GetMetaObject(...);
int Memory_GetAllocatorBySelector(int);

long long Gap__Sg__igCommonTraversal__vfunc_26(igCommonTraversal *t);
int FUN_001b3ad0(igCommonTraversal *arg0, int arg1);
void FUN_001b3c90(A0 *arg0, A1 *arg1);
void FUN_001b3ff0(void *arg0, int arg1);
void FUN_001b4090(T *arg0, int arg1, int arg2);
int FUN_001b40f0(void *arg0, int arg1);
int FUN_001b4120(int *p);
int FUN_001b4130(struct O4130 *arg0);
void FUN_001b4220(struct A4220 *arg0, struct B4220 *arg1);
void FUN_001b42c0(TravFlattenView *self, int root);
void FUN_001b4500(struct O4500 *o, struct S4500 *s, int b);
int FUN_001b4bb0(igCommonTraversal *arg0, int arg1);
void FUN_001b68b0(int arg0);
void FUN_001b68c0(void *self, void *meta);
void Gap__Sg__igCommonTraversal__vfunc_09(igCommonTraversal *arg0, int arg1);
void FUN_001b6be0(void);
void FUN_001b6c50(void);
int Gap__Core__igObject__vfunc_08();
}

long long Gap__Sg__igCommonTraversal__vfunc_26(igCommonTraversal *t) {
    int top; igLongStack *stack = (igLongStack *)t->_timeStack; int n = stack->_count; top = n - 1;
    if (n == 0) {
        if (!t->_timeBuffered) {
            if (t->_userTimeState) {
                t->_timeLongBuf = t->_timeLong;
            } else {
                t->_timeLongBuf = DAT_005871d8->getTime();
            }
            t->_timeBuffered = 1;
        }
        return t->_timeLongBuf;
    }
    return ((long long *)stack->_data)[top];
}

int FUN_001b3ad0(igCommonTraversal *arg0, int arg1) {
    igAttrStackManager *p;
    igMetaObject *mo;
    igAttrStack *a0;
    igAttrStack *l;
    int a2;
    int km;
    int k;
    unsigned s2;
    bool flag;
    igBitMask *b;
    igBitMask *b2;
    unsigned idx;
    int n;
    unsigned *d;
    unsigned w;
    unsigned idx2;
    unsigned w2;

    p = (igAttrStackManager *)arg0->_attrStack;
    a0 = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[DAT_0055efe8[0]->_id]];
    k = a0->_count;
    km = k - 1;
    if (k == 0) {
        a2 = 0;
    } else {
        a2 = ((int *)a0->_data)[km];
    }
    ((H *)DAT_005625f0)->vX(arg1, a2);
    mo = igTextureBindAttr_GetMetaObject();
    p = (igAttrStackManager *)arg0->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[mo->_id]];
    if (l != 0) {
        flag = !(l->_count == 0);
    } else {
        flag = 0;
    }
    b = ((H *)DAT_005625f0)->f184;
    s2 = b->_bitCount;
    FUN_001b1e50(b, s2 + 1);
    b2 = ((H *)DAT_005625f0)->f184;
    if (flag) {
        idx = s2 >> 5;
        w = ((unsigned *)b2->_data)[idx] | (1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx >= 0 && (int)idx < b2->_count) {
            ((unsigned *)b2->_data)[idx] = w;
        }
    } else {
        idx2 = s2 >> 5;
        w2 = ((unsigned *)b2->_data)[idx2] & ~(1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx2 >= 0 && (int)idx2 < b2->_count) {
            ((unsigned *)b2->_data)[idx2] = w2;
        }
    }
    FUN_001c5660(arg1, 4, 1);
    return 0;
}

void FUN_001b3c90(A0 *arg0, A1 *arg1) {
    int temp_a0;
    int temp_s0;

    FUN_001b3030();
    temp_a0 = arg0->f160;
    FUN_00157200(temp_a0, 1, temp_a0);
    temp_s0 = arg1->f52;
    FUN_001dc500(arg1->f68, 0, 0);
    FUN_001b12f0(temp_s0, DAT_005625e0[0]);
    FUN_001b12f0(temp_s0, DAT_005625e8[0]);
    FUN_001b12f0(temp_s0, DAT_005625b8[0]);
    FUN_001b12f0(temp_s0, DAT_005625c8[0]);
    FUN_001b12f0(temp_s0, DAT_005625c0[0]);
    FUN_001b12f0(temp_s0, DAT_005625d0[0]);
    FUN_001b12f0(temp_s0, arg0->f176);
    FUN_001b12f0(temp_s0, arg0->f32);
    FUN_001e07a0(arg1, arg0);
    FUN_001b13d0(temp_s0, arg0->f32);
    FUN_001b13d0(temp_s0, arg0->f176);
    FUN_001b13d0(temp_s0, DAT_005625d0[0]);
    FUN_001b13d0(temp_s0, DAT_005625c0[0]);
    FUN_001b13d0(temp_s0, DAT_005625c8[0]);
    FUN_001b13d0(temp_s0, DAT_005625b8[0]);
    FUN_001b12f0(temp_s0, DAT_00562598[0]);
    FUN_001b12f0(temp_s0, DAT_005625d0[0]);
    FUN_001b12f0(temp_s0, DAT_005625c8[0]);
    FUN_001e07a0(arg1, arg0);
    FUN_001b13d0(temp_s0, DAT_005625c8[0]);
    FUN_001b13d0(temp_s0, DAT_005625d0[0]);
    FUN_001b13d0(temp_s0, DAT_00562598[0]);
    FUN_001b12f0(temp_s0, DAT_005625b0[0]);
    FUN_001b12f0(temp_s0, DAT_005625c8[0]);
    FUN_001b12f0(temp_s0, DAT_005625c0[0]);
    FUN_001b12f0(temp_s0, DAT_005625d0[0]);
    FUN_001b12f0(temp_s0, arg0->f180);
    FUN_001b12f0(temp_s0, arg0->f32);
    FUN_001e07a0(arg1, arg0);
    FUN_001b13d0(temp_s0, arg0->f32);
    FUN_001b13d0(temp_s0, arg0->f180);
    FUN_001b13d0(temp_s0, DAT_005625d0[0]);
    FUN_001b13d0(temp_s0, DAT_005625c0[0]);
    FUN_001b13d0(temp_s0, DAT_005625c8[0]);
    FUN_001b13d0(temp_s0, DAT_005625b0[0]);
    FUN_001b12f0(temp_s0, DAT_005625a8[0]);
    FUN_001b12f0(temp_s0, DAT_005625d0[0]);
    FUN_001b12f0(temp_s0, DAT_005625c8[0]);
    FUN_001e07a0(arg1, arg0);
    FUN_001b13d0(temp_s0, DAT_005625c8[0]);
    FUN_001b13d0(temp_s0, DAT_005625d0[0]);
    FUN_001b13d0(temp_s0, DAT_005625a8[0]);
    FUN_001b12f0(temp_s0, DAT_005625d8[0]);
    FUN_001b12f0(temp_s0, DAT_005625c8[0]);
    FUN_001b12f0(temp_s0, DAT_005625a0[0]);
    FUN_001e07a0(arg1, arg0);
    FUN_001b13d0(temp_s0, DAT_005625a0[0]);
    FUN_001b13d0(temp_s0, DAT_005625c8[0]);
    FUN_001b13d0(temp_s0, DAT_005625d8[0]);
    FUN_001b13d0(temp_s0, DAT_005625e8[0]);
    FUN_001b13d0(temp_s0, DAT_005625e0[0]);
    FUN_001dc610(arg1->f68);
}

void FUN_001b3ff0(void *arg0, int arg1) {
    void **temp_a0;
    void **temp_a0_2;

    if (FUN_001b4130((struct O4130 *)arg0) == 0) {
        FUN_001e07a0(arg1, arg0);
        return;
    }
    FUN_001b4220((struct A4220 *)arg0, (struct B4220 *)arg1);
    FUN_001b42c0((TravFlattenView *)arg0, arg1);
    temp_a0 = (void **)(*(int *)((char *)(arg0) + 176));
    ((DW4VC_132_1 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 48)));
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 180));
    ((DW4VC_132_1 *)(temp_a0_2))->vX((int)(*(int *)((char *)(arg0) + 52)));
    FUN_001b3c90((A0 *)arg0, (A1 *)arg1);
}

void FUN_001b4090(T *arg0, int arg1, int arg2) {
    if (arg1 < 8) {
        if (arg2 != 0) {
            arg0->flags |= (1 << arg1);
        } else {
            arg0->flags &= ~(1 << arg1);
        }
    }
}

int FUN_001b40f0(void *arg0, int arg1) {
    if (arg1 >= 8) {
        return 0;
    }
    return *(unsigned char *)((char *)(arg0) + 64) & (1 << arg1) & 0xFF;
}

int FUN_001b4120(int *p)
{
    return *(unsigned char *)((char *)p + 64);
}

int FUN_001b4130(struct O4130 *arg0) {
    struct Rc *temp_a0;
    struct Rc *temp_v0;

    if ((arg0->f32 == 0) || (FUN_001b4120((int *)arg0) == 0) || (arg0->f56->f8 == 0)) {
        return 0;
    }
    if (arg0->f160 == 0) {
        temp_v0 = FUN_00140c00(arg0->f32->f12, 0);
        if (temp_v0 != 0) {
            temp_v0->rc = temp_v0->rc + 1;
        }
        temp_a0 = arg0->f160;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f160 = temp_v0;
        if (arg0->f160 == 0) {
            return 0;
        }
    }
    if (arg0->f160->f16 != 1) {
        return 0;
    }
    return 1;
}

void FUN_001b4220(struct A4220 *arg0, struct B4220 *arg1) {
    int temp_s2;
    int n;
    int i;
    struct Q *q;

    q = arg0->f144;
    temp_s2 = arg1->f52;
    n = 0;
    if (q != 0) {
        n = q->count;
    }
    if (n > 8) {
        n = 8;
    }
    for (i = 0; i < n; i++) {
        FUN_001b4090((T *)arg0, i, FUN_001b0ea0(temp_s2, arg0->f144->data[i]));
    }
}

static inline void clearRetained(TravObjectList *l) {
    int n = l->_count;
    int i;
    for (i = 0; i < n; i++) {
        TravObject *o = l->_data[i];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int total = l->_count;
        for (i = 0; i < total; i++) {
            l->_data[i] = 0;
        }
    }
    l->_count = 0;
}
void FUN_001b42c0(TravFlattenView *self, int root) {
    int saved[32];
    TravFunctionTable *table = DAT_00562640;
    int meta = DAT_00561a38;
    int n = igMetaObject_CountTree(meta);
    int i;
    for (i = 0; i < n; i++) {
        TravObject *m = FUN_002fe300(meta, i);
        saved[i] = table->_data[m->_id];
        FUN_001e06c0(table, m, (void *)FUN_001b3ad0);
    }
    DAT_005625f0 = self;
    clearRetained(self->_a);
    clearRetained(self->_b);
    FUN_001e07a0(root, self);
    for (i = 0; i < n; i++) {
        FUN_001e06c0(table, FUN_002fe300(meta, i), (void *)saved[i]);
    }
}

void FUN_001b4500(struct O4500 *o, struct S4500 *s, int b) {
    s = o->s;
    if (s != 0) {
        if (s->k == 1) { o->x = s->firstX; o->y = s->firstY; o->z = s->firstZ; o->w = 0x3F800000; return; }
        o->x = s->secondX; o->y = s->secondY; o->z = s->secondZ; o->w = 0;
    }
}

int FUN_001b4bb0(igCommonTraversal *arg0, int arg1) {
    igAttrStackManager *b;
    igAttrStack *l;
    int v;

    b = (igAttrStackManager *)arg0->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)b->_attrStacks)->_data)[((int *)b->_attrStackIndexTable)[DAT_0055efe8[0]->_id]];
    if (l->_count == 0) {
        v = 0;
    } else {
        v = *(int *)(l->_data + ((l->_count - 1) * 4));
    }
    DAT_00562638[0]->vX(arg1, v);
    return 0;
}

void FUN_001b68b0(int arg0) {
    FUN_001b68c0(DAT_00562640, (void *)arg0);
}

void FUN_001b68c0(void *self, void *meta) {
    FUN_001e02f0(self, meta);
    if (FUN_002fe290(meta, igNode_GetMetaObject()) != 0) {
        NodeProcTable t = DAT_0048d8f0;
        int i;
        t.e[0].meta = DAT_00562488;
        t.e[1].meta = DAT_00561620;
        t.e[2].meta = DAT_005615d0;
        t.e[3].meta = DAT_00561bd8;
        t.e[4].meta = DAT_005615d8;
        t.e[5].meta = DAT_00561a98;
        t.e[6].meta = DAT_00561920;
        t.e[7].meta = DAT_00561908;
        t.e[8].meta = DAT_00561910;
        t.e[9].meta = DAT_00561860;
        t.e[10].meta = DAT_00561868;
        t.e[11].meta = DAT_00561e98;
        t.e[12].meta = DAT_00561ee8;
        t.e[13].meta = DAT_005618f8;
        t.e[14].meta = DAT_00561878;
        t.e[15].meta = DAT_00561870;
        t.e[16].meta = DAT_00561898;
        t.e[17].meta = DAT_005618d8;
        t.e[18].meta = DAT_005618e8;
        t.e[19].meta = DAT_00561a38;
        t.e[20].meta = DAT_005617a8;
        t.e[21].meta = DAT_00561578;
        t.e[22].meta = DAT_00561570;
        t.e[23].meta = DAT_00561f38;
        t.e[24].meta = DAT_00561818;
        t.e[25].meta = DAT_00562078;
        t.e[26].meta = DAT_005612b0;
        t.e[27].meta = DAT_00561f68;
        t.e[28].meta = DAT_00561308;
        t.e[29].meta = DAT_00561280;
        t.e[30].meta = DAT_005612d8;
        t.e[31].meta = DAT_00561ca0;
        t.e[32].meta = DAT_00561888;
        t.e[33].meta = DAT_005612e0;
        for (i = 0; i < 34; i++) {
            NodeProcEntry *e = &t.e[i];
            if (e->meta != 0 && FUN_002fe290(meta, e->meta) != 0) {
                FUN_001e06c0(self, meta, e->proc);
                return;
            }
        }
    }
}

void Gap__Sg__igCommonTraversal__vfunc_09(igCommonTraversal *arg0, int arg1) {
    igObject *s0;
    igObject *a0;

    Gap__Sg__igTraversal__vfunc_09(arg0, arg1);
    if (arg1 == 0) {
        s0 = (igObject *)DAT_00562640;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        a0 = (igObject *)arg0->_travProcs;
        if (a0 != 0) {
            --a0->_refCount;
            if (((unsigned long long)(long long)a0->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->_travProcs = (int)s0;
        ((C *)arg0->_matrixOptimization)->vX(0);
        *(char *)(arg0->_normalizeNormalsEnable + 12) = 1;
    }
}

void FUN_001b6be0(void) {
    *(int *)0x562640 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
    FUN_0013b110();
    FUN_00132a00();
    FUN_001357e0();
    FUN_00130cf0();
    FUN_001318f0();
    FUN_00130830();
    FUN_00130a70();
}

void FUN_001b6c50(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562640;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
}

int Gap__Core__igObject__vfunc_08()
{
    return Gap__Core__igObject__vfunc_08__002ff0f0();
}
