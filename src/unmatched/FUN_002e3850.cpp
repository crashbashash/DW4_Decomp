#include "dw4/igobject_release.h"
struct Obj { int vt; unsigned int _refCount; char *text; };
struct Holder { Obj *p; Holder() {} Holder(const Holder &o) { p = o.p; } };
class Named { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual Holder Find(int key);
    int rc;
    char *name;
};
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, char *);
void StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(Obj *);
extern char *DAT_004c22f0[4];
extern void *DAT_00586f20[4];
void FUN_002e3850(Named *self, int key);
}
static inline void *pool() {
    if (DAT_00586f20[0] == 0) {
        void *o = FUN_002eb010(0x10);
        if (o != 0) {
            o = StringPool_Construct(o);
        }
        DAT_00586f20[0] = o;
    }
    return DAT_00586f20[0];
}
void FUN_002e3850(Named *self, int key) {
    Holder h = self->Find(key);
    char *text = h.p->text;
    char *v;
    char *old;
    text = (text == 0) ? DAT_004c22f0[0] : text;
    v = StringPool_Intern(pool(), text);
    old = self->name;
    if (old != 0) {
        int *hdr = (int *)(old - 8);
        int r = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    self->name = v;
    IG_OBJECT_RELEASE(h.p);
}
