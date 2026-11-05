#include "dw4/reflected.h"
extern "C" {
void *Memory_FindOwningAllocator(...);
int Memory_FreeBuffer(...);
int igObject_Destroy(...);
void MemoryContext_RemoveAllocator(void *arg0, int arg1);
}
struct R { int v; R() {} };
class C72 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual R vX(int,long long); };
class C96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual R vX(int,int,int); };
class C104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
class C128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(); };
class C144 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int vX(); };
class C188 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int vX(); };
class C348 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual int vX(int); };

extern "C" { extern class C72 *DAT_00587218[4]; }
typedef igObject Obj;
struct Ctx { char p[8]; int f8; };
struct Slot { Obj *obj; char q[132]; int flags; };
#define RC(o) ((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL)
void MemoryContext_RemoveAllocator(void *arg0, int arg1) {
    R sp6C, sp68, sp64;
    if (arg1 >= 0 && arg1 < 0x2E) {
        Obj *o = *(Obj **)((char *)arg0 + arg1 * 0x90 + 20);
        Slot *slot = (Slot *)((char *)arg0 + arg1 * 0x90 + 20);
        if (o != 0) {
            slot->obj = 0;
            if (RC(o) == 1) {
                if (((C188 *)o)->vX() != 0) {
                    ((C348 *)o)->vX(0);
                }
                ((C128 *)o)->vX();
                {
                    int fl = slot->flags;
                    if (fl & 1) {
                        int a;
                        slot->flags = fl & ~1;
                        a = ((C104 *)o)->vX(fl);
                        if (a != 0) {
                            void *own;
                            sp6C = ((C96 *)o)->vX(0, 0, 0);
                            own = Memory_FindOwningAllocator(a);
                            if (own != 0) {
                                Obj *ob = (Obj *)own;
                                ob->_refCount = ob->_refCount - 1;
                                if (RC(ob) == 0) igObject_Destroy(ob);
                                Memory_FreeBuffer(a);
                            }
                        }
                    } else if (fl & 2) {
                        int a;
                        slot->flags = fl & ~2;
                        a = ((C104 *)o)->vX(fl);
                        if (a != 0) {
                            long long b = (long long)((C144 *)o)->vX();
                            sp68 = ((C96 *)o)->vX(0, 0, 0);
                            sp64 = DAT_00587218[0]->vX(a, b);
                        }
                    }
                }
            }
            o->_refCount = o->_refCount - 1;
            if (RC(o) == 0) igObject_Destroy(o);
            { Ctx *c = (Ctx *)arg0; if (arg1 == c->f8 + 1) c->f8 = arg1; }
        }
    }
}
