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
  virtual void d52();
  virtual void *v53(int, int);
};

extern "C" {
int FUN_0015e160(...);
int Memory_FreeBuffer(...);
int igObject_Destroy(...);
igObject *igObject_GetAllocator(...);
}

extern "C" void Gap__Core__igVertexArray2__vfunc_48(igVertexArray1_1 *arg0);
void Gap__Core__igVertexArray2__vfunc_48(igVertexArray1_1 *arg0) {
    int s2b;
    unsigned int a1b;
    int s2;
    int **s3;
    int *a0b;
    unsigned int a1;
    unsigned int s4;
    int *a0;
    unsigned char s5;
    unsigned int sp7C;
    int **s3b;
    unsigned int s4b;
    unsigned int s0;
    unsigned char s5b;
    FUN_0015e160(&sp7C, arg0->_vtype);
    arg0->_vertexFormat = sp7C;
    arg0->_vtype = 0;
    if (arg0->_memPool == 0) {
        igObject *v0 = igObject_GetAllocator(arg0);
        if (v0 != 0) v0->_refCount = v0->_refCount + 1;
        {
            igObject *a = (igObject *)arg0->_memPool;
            if (a != 0) {
                a->_refCount = a->_refCount - 1;
                if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(a);
            }
        }
        arg0->_memPool = (int)v0;
    }
    s5 = (sp7C & 0xF0) >> 4;
    s0 = arg0->_numVerts;
    if (s5 != 0) {
        Alloc *al = (Alloc *)arg0->_memPool;
        arg0->_blendWeights = (int)al->v53(s0 * (s5 * 4), 0x10);
        for (s4 = 0; s4 < s5; s4++) {
            s3 = (int **)&arg0->_vdata;
            s2 = (s4 + 3) * 4;
            a0 = *(int **)((char *)arg0->_vdata + s2);
            for (a1 = 0; a1 < s0; a1++) {
                (*(float **)&arg0->_blendWeights)[s4 + s5 * a1] = ((float *)a0)[a1];
            }
            Memory_FreeBuffer(a0, a1);
            *(int *)((char *)*s3 + s2) = 0;
        }
    }
    s5b = (sp7C & 0xF00) >> 8;
    if (s5b != 0) {
        Alloc *al = (Alloc *)arg0->_memPool;
        arg0->_blendIndices = (int)al->v53(s5b * s0, 0x10);
        for (s4b = 0; s4b < s5b; s4b++) {
            s3b = (int **)&arg0->_vdata;
            s2b = (s4b + 7) * 4;
            a0b = *(int **)((char *)arg0->_vdata + s2b);
            for (a1b = 0; a1b < s0; a1b++) {
                (*(unsigned char **)&arg0->_blendIndices)[s4b + s5b * a1b] = *((unsigned char *)a0b + a1b);
            }
            Memory_FreeBuffer(a0b);
            *(int *)((char *)*s3b + s2b) = 0;
        }
    }
}
