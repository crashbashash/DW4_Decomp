#include "dw4/igSmartPointer.h"
class Obj;
struct PropertySet { char pad[56]; int props; };
extern "C" {
int igObject_GetAllocator(...);
Obj *FUN_00132810(int);
Obj *FUN_001325a0(int);
Obj *FUN_00131c60(int);
int thunk_FUN_00306e50(int, int, char *, unsigned char *, int, int);
extern char DAT_004e4600[];          
extern PropertySet *DAT_00586dc8[4];
extern Obj *DAT_00562738[4];
extern Obj *DAT_00562740[4];
}

class Obj : public igVirtualObject {
public:
  virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void configure(int);        /* +100 */
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void setKind(int);          /* +128 */
  virtual void setValue(int);         /* +132 */
  
  int field8;
  int field12;
};

static inline void release(Obj *o) {
  if (o != 0) {
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
  }
}
static inline void assign(Obj *&field, Obj *value) {
  if (value) value->_refCount = value->_refCount + 1;
  release(field);
  field = value;
}
static inline void assign(Obj *&field, const igSmartPointer<Obj> &value) {
  Obj *held = value.get();
  if (held) held->_refCount = held->_refCount + 1;
  release(field);
  field = held;
}
struct Controller {
  char pad0[32];
  int a32;
  Obj *p36;
  int a40;
  char pad44[4];
  unsigned char flag48;
  char pad49[3];
  int a52;
  int a56;
  char pad60[13];
  unsigned char enabled;   /* +73 */
  char pad74[2];
  Obj *f76, *f80, *f84, *f88, *f92, *f96, *f100, *f104, *f108;
};

extern "C" void FUN_001c20b0(Controller *self) {
  unsigned char flag;
  Obj *s1;
  int props = DAT_00586dc8[0]->props;
  flag = 1;
  thunk_FUN_00306e50(props, 7, DAT_004e4600, &flag, 1, 1);
  self->enabled = flag;
  assign(self->f76, igSmartPointer<Obj>(FUN_00132810(igObject_GetAllocator(self))));
  self->f76->setValue(self->a32);
  self->f76->configure(0);
  assign(self->f80, igSmartPointer<Obj>(FUN_001325a0(igObject_GetAllocator(self))));
  self->f80->setKind(2);
  self->f80->configure(0);
  assign(self->f84, igSmartPointer<Obj>(FUN_00131c60(igObject_GetAllocator(self))));
  self->f84->field12 = 2;
  self->f84->configure(0);
  if (self->p36 != 0) {
    self->p36->configure(0);
    assign(self->f88, igSmartPointer<Obj>(FUN_001325a0(igObject_GetAllocator(self))));
    self->f88->setKind(0);
    self->f88->configure(0);
    self->f88->setValue(self->a40);
    assign(self->f92, igSmartPointer<Obj>(FUN_00131c60(igObject_GetAllocator(self))));
    self->f92->field12 = 1;
    self->f92->configure(0);
    if (self->flag48) {
      s1 = DAT_00562738[0];
      assign(self->f96, s1);
    } else {
      s1 = DAT_00562740[0];
      assign(self->f96, s1);
    }
  }
  if (self->a52 != 0) {
    assign(self->f100, igSmartPointer<Obj>(FUN_00132810(igObject_GetAllocator(self))));
    self->f100->setValue(self->a52);
    self->f100->configure(0);
    s1 = self->f88;
    if (s1 != 0 && self->a56 == self->a40) {
      assign(self->f104, s1);
    } else {
      assign(self->f104, igSmartPointer<Obj>(FUN_001325a0(igObject_GetAllocator(self))));
      self->f104->setKind(0);
      self->f104->configure(0);
      self->f104->setValue(self->a56);
    }
    assign(self->f108, igSmartPointer<Obj>(FUN_00131c60(igObject_GetAllocator(self))));
    self->f108->field12 = 0;
    self->f108->configure(0);
  }
}
