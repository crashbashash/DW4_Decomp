struct Arr { char pad[8]; int a8; int a12; int a16; void *a20; int a24; };
extern "C" {
int memset(...);
void *FUN_002c4ca0(...);
void *FUN_00300db0(...);
int FUN_00300f50(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_004de6c0[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
int FUN_00154f30(Arr *self, int arg1);
}
class DW4VC_100_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int, int); virtual int v24(); virtual int v25(int,int,int);
  int refs; };
template <class T> struct igSmartPointer {
    T *o;
    ~igSmartPointer() { T *x = o; if (x) { --x->refs; if ((x->refs & 0x7fffff) == 0) igObject_Destroy(x); } }
};
int FUN_00154f30(Arr *self, int arg1) {
    igSmartPointer<DW4VC_100_2> h;
    int a, b;
    int i;
    int *p;
    a = igObject_GetAllocator();
    if (GPR_00554c14 != 0) { b = a; } else { b = Memory_GetAllocatorBySelector(DAT_00587060[0]); } a = b;
    h.o = (DW4VC_100_2 *)FUN_002c4ca0(a);
    if (h.o != 0) h.o->refs++;
    { DW4VC_100_2 *x = h.o; --x->refs; if ((x->refs & 0x7fffff) == 0) igObject_Destroy(x); }
    if (self->a20 != 0) FUN_00300f50(self, self->a20);
    self->a20 = 0;
    if (h.o->vX(arg1, (int)&DAT_004de6c0[0]) == 0) {
        return 0;
    }
    self->a20 = FUN_00300db0(self, 0x400, 0x80);
    p = (int *)self->a20;
    i = 0;
    do {
        h.o->v25((int)p, 1, 3);
        i++;
        *((unsigned char *)p + 3) = 0xff;
        p++;
    } while ((unsigned)i < 0x100);
    if ((unsigned)i < 0x100) memset(p, 0, (0x100 - i) * 4);
    self->a24 = 0x400;
    self->a16 = 4;
    self->a12 = 0x100;
    self->a8 = 7;
    h.o->v24();
    return 1;
}
