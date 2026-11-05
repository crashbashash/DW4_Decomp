#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(...);
int igObject_GetAllocator();
char *FUN_0014df70(int);
int FUN_0015a380(char *);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v21(void *, int); };
class Strm { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void v24(); virtual void d25(); virtual void d26(); virtual int v27(void *, int, int); };
extern "C" int Gap__Core__igPsx2Image__vfunc_41(igPsx2Image *arg0, Strm *arg1);
int Gap__Core__igPsx2Image__vfunc_41(igPsx2Image *arg0, Strm *arg1) {
    char * volatile sp3C;
    int sp38;
    int sp34;
    char *t;
    sp3C = FUN_0014df70(igObject_GetAllocator());
    ((Obj *)sp3C)->v21(arg0, 1);
    FUN_0015a380(sp3C);
    sp38 = 0x312A57F2;
    arg1->v27(&sp38, 4, 1);
    arg1->v27(&arg0->_imageSize, 4, 1);
    arg1->v27(&arg0->_px, 4, 1);
    arg1->v27(&arg0->_py, 4, 1);
    arg1->v27(&arg0->_pz, 4, 1);
    arg1->v27(&arg0->_ps, 4, 1);
    sp34 = (arg0->_bitsRed << 24) | (arg0->_bitsGrn << 16) | (arg0->_bitsBlu << 8) | arg0->_bitsAlpha;
    arg1->v27(&sp34, 4, 1);
    sp38 = 0;
    arg1->v27(&sp38, 4, 1);
    arg1->v27(&sp38, 4, 1);
    arg1->v27((void *)((igImage *)sp3C)->_pImage, 1, arg0->_imageSize);
    arg1->v24();
    ((igObject *)arg1)->_refCount = ((igObject *)arg1)->_refCount - 1;
    if ((((igObject *)arg1)->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(arg1);
    }
    t = sp3C;
    if (t != 0) {
        ((igObject *)t)->_refCount = ((igObject *)t)->_refCount - 1;
        if ((((igObject *)t)->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    return 1;
}
