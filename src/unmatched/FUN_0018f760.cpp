extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
unsigned FUN_002fe2c0(...);
int FUN_002fe2e0(...);
T *FUN_00186c00(...);
int FUN_00301ee0(...);
int FUN_002fd6e0(...);
extern int DAT_00560f08[4];
}
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Rel2 { static inline void go(T **p) {
    T *o = *p;
    if (o) {
        o->references = o->references - 1;
        T *u = *p;
        if (((unsigned long long)(long long)u->references & 0x7fffffULL) == 0)
            igObject_Destroy(u);
    }
} };
struct L { char pad[8]; int f8; char p2[4]; T **f16; };
extern "C" int FUN_0018f760(T **arg0, int arg1);
int FUN_0018f760(T **arg0, int arg1) {
    T * volatile sp9C;
    T * volatile sp98;
    T *sp94;
    int s3;
    unsigned s6, s2;
    T *s1;
    L *s0;
    int off;
    s3 = DAT_00560f08[0];
    s6 = FUN_002fe2c0(s3);
    sp9C = FUN_00186c00(arg1);
    FUN_00301ee0(sp9C, s6);
    for (s2 = 0; s2 < s6; s2++) {
        FUN_002fd6e0(&sp94, FUN_002fe2e0(s3, s2), arg1);
        sp98 = sp94;
        T *t = sp98;
        if (t != 0) t->references = t->references + 1;
        Rel2::go(&sp94);
        s1 = sp98;
        s0 = (L *)sp9C;
        if (s1 != 0) s1->references = s1->references + 1;
        off = s2 * 4;
        Rel::go(*(T **)((char *)s0->f16 + off));
        if (s0->f8 != 0 && (int)s2 >= 0 && (int)s2 < s0->f8) {
            *(T **)((char *)s0->f16 + off) = s1;
        }
        t = sp98;
        Rel::go(t);
    }
    *arg0 = sp9C;
    {
        T *v = *arg0;
        if (v != 0) v->references = v->references + 1;
    }
    {
        T *w = sp9C;
        Rel::go(w);
    }
    return 0;
}
