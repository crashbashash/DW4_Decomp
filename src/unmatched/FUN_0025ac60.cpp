struct R { int w0; int refs; int f8; int w12; int *f16; };
extern "C" int igObject_Destroy(...);
extern "C" int StringChunk_ReleaseHeader(...);
/* Engine-object reference returned by value from the owner's slot 24. The owner unit's inline
 * releases read the pointer again after the count store. */
struct Ref {
    R *p;
    Ref() {}
    ~Ref() {
#if __option(exceptions)
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)(long long)p->refs & 0x7fffffULL) == 0) igObject_Destroy(p);
        }
#else
        R *o = p;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) igObject_Destroy(o);
        }
#endif
    }
};
/* Interned-string share (count at p[-1], header at p[-2]). */
struct StringRef {
    int *p;
    StringRef() {}
    static inline void Release(int *x) {
        if (x != 0) { int *hd = x - 2; int c = x[-1] - 1; x[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); }
    }
    ~StringRef() { Release(p); }
};
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual Ref v24(); };
/* matching construct: the returned reference is a temporary of the call, so it takes a low frame slot and is released right after the store */
struct Assign {
    static inline void Take(R *&dst, const Ref &src) {
        R *rs = src.p;
        R *o;
        if (rs != 0) rs->refs = rs->refs + 1;
        o = dst;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) igObject_Destroy(o);
        }
        dst = rs;
    }
};
struct S { char p0[48]; R *f48; V *f52; };
extern "C" {
int strcpy(...);
int strlen(...);
int FUN_002eb010(...);
int FUN_0030bb40(...);
int List_RemoveWordAt(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
extern int DAT_004ecfa0[4];
extern int DAT_00586f20[4];
void FUN_0025ac60(S *arg0);
}
extern "C" StringRef StringList_CopyRetained(void *, int);
#define REL(x) if ((x) != 0) { int *hd_ = (int *)(x) - 2; int c_ = ((int *)(x))[-1] - 1; ((int *)(x))[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*hd_, hd_); }
void FUN_0025ac60(S *arg0) {
    char buf[256];
    R *l2;
    int s2;
    int s3;
    int *np;
    R *la;
    R *lb;
    R *l3;
    int cnt;
    int *slot;
    int s1;
    R *o;

    Assign::Take(arg0->f48, arg0->f52->v24());
    la = arg0->f48;
    if (la != 0) {
        s3 = la->f8 - 1;
        s1 = s3 * 4;
        if (s3 >= 0) {
            do {
                {
                StringRef s348 = StringList_CopyRetained(arg0->f48, s3);
                strcpy(buf, s348.p);
                buf[strlen(buf) - 2] = 0;
                if (DAT_00586f20[0] == 0) {
                    int v = FUN_002eb010(0x10);
                    if (v != 0) v = StringPool_Construct(v);
                    DAT_00586f20[0] = v;
                }
                np = (int *)StringPool_Intern(DAT_00586f20[0], buf);
                StringRef::Release(s348.p);
                s348.p = np;
                lb = arg0->f48;
                cnt = lb->f8;
                if (cnt != 0 && s3 >= 0 && s3 < cnt) {
                    slot = (int *)((char *)lb->f16 + s1);
                    if (s348.p != 0) s348.p[-1] = s348.p[-1] + 1;
                    StringRef::Release((int *)*slot);
                    *slot = (int)s348.p;
                }
                }
                s3 -= 1;
                s1 -= 4;
            } while (s3 >= 0);
        }
        l2 = arg0->f48;
        if (l2 != 0) {
            s2 = l2->f8 - 1;
            if (s2 >= 0) {
                do {
                    {
                    StringRef s344 = StringList_CopyRetained(arg0->f48, s2);
                    if (FUN_0030bb40(s344.p, &DAT_004ecfa0[0]) == 0) {
                        l3 = arg0->f48;
                        StringRef::Release(StringList_CopyRetained(l3, s2).p);
                        List_RemoveWordAt(l3, s2);
                        l3->f16[l3->f8] = 0;
                    }
                    }
                    s2 -= 1;
                } while (s2 >= 0);
            }
        }
    }
}
