#include "dw4/reflected.h"
class Alloc { public:
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
  virtual int v52(int);
  virtual int v53(int, int);
};
class VA { public:
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
  virtual unsigned int *v23();
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
  virtual void d54();
  virtual void d55();
  virtual void d56();
  virtual void d57();
  virtual void d58();
  virtual void d59();
  virtual void d60();
  virtual void d61();
  virtual int v62();
  virtual int v63();
  char pad4[4]; int f8; int f12; char pad16[8]; Alloc *f24; char pad28[4]; int f32; int f36;
};
extern "C" {
int igObject_Destroy(...);
igObject *igObject_GetAllocator(...);
int FUN_0015e4e0(VA *arg0);
}
int FUN_0015e4e0(VA *arg0) {
//DECL
    igObject *v0;
    int s2;
    unsigned int *s1;
    int sz;
    unsigned int i;
    int s4;
//ENDDECL
    s2 = 0;
    s1 = arg0->v23();
    if (arg0->f24 == 0) {
        v0 = (igObject *)igObject_GetAllocator(arg0);
        if (v0 != 0) v0->_refCount = v0->_refCount + 1;
        {
            igObject *a = (igObject *)arg0->f24;
            if (a != 0) {
                a->_refCount = a->_refCount - 1;
                if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(a);
            }
        }
        arg0->f24 = (Alloc *)v0;
    }
    if (*s1 & 1) {
        sz = arg0->f12 * 0xC;
        *(int *)(arg0->f8 + 0) = arg0->f24->v52(sz);
        s2 += sz;
    }
    {
    unsigned int f = *s1;
    if (f & 2) {
        int a0 = arg0->f12;
        sz = a0 * 0xC;
        if ((f & 0x400000) || (f & 0x800000)) sz += a0 * 0x18;
        *(int *)(arg0->f8 + 4) = arg0->f24->v52(sz);
        s2 += sz;
    }
    }
    if (*s1 & 4) {
        sz = arg0->f12 * 4;
        *(int *)(arg0->f8 + 8) = arg0->f24->v52(sz);
        s2 += sz;
    }
    {
        unsigned char c = (*s1 & 0xF0) >> 4;
        if (c != 0) {
            int a1 = arg0->f12 * c * 4;
            s2 += a1;
            if (arg0->f32 == 0) arg0->f32 = arg0->f24->v53(a1, 0x10);
        }
    }
    {
        unsigned char c = (*s1 & 0xF00) >> 8;
        i = 0;
        if (c != 0) {
            int a1 = arg0->f12 * c;
            s2 += a1;
            if (arg0->f36 == 0) arg0->f36 = arg0->f24->v53(a1, 0x10);
            i = 0;
        }
        unsigned int fv = *s1;
        while (i < (unsigned char)((fv & 0xF0000) >> 16)) {
            s4 = arg0->f12 * 8;
            int a0 = arg0->f24->v52(s4);
            int off = (i + 11) * 4;
            i++;
            s2 += s4;
            *(int *)(arg0->f8 + off) = a0;
            fv = *s1;
        }
    }
    s2 += arg0->v62();
    s2 += arg0->v63();
    return s2;
}
