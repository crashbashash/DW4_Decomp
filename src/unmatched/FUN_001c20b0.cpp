/* 0x001c20b0 - FUN_001c20b0: build the helper objects of a controller on its first update.
 *
 * Reads the stored enable flag from the property set (global 0x586dc8, +56; name at 0x4e4600),
 * then creates up to eight owned helper objects in the fields at +76..+108, each from the
 * controller's own allocator, configures them through their virtual methods (slots at
 * +100 / +128 / +132) and drops the temporary reference.  Every store is the reference-counted
 * assignment idiom: retain the new object, release the old one, publish.
 * Evidence: asm/FUN_001c20b0.s; the same idiom in src/unmatched/igIGBFile_ReadObject.cpp.
 * Matching constructs: each new object lives in a volatile stack slot (the retail code reloads it
 * from the stack for the retain and for the final release); the dummy virtual class supplies the
 * slot offsets (offset = 8 + 4 * index); the two arms that publish into +96 each carry their own
 * store, and `flag` is assigned just before the call.  Build: local/mwcps2/combat/mwccps2.exe
 * (sha256 acf1088553362dddef7eee2d269848b03208e29fd26caa441848e57b6299786a), -O3 -Iinclude. */
class Obj;
struct PropertySet { char pad[56]; int props; };
extern "C" {
void igObject_Destroy(Obj *);
int igObject_GetAllocator(...);
Obj *FUN_00132810(int);
Obj *FUN_001325a0(int);
Obj *FUN_00131c60(int);
int thunk_FUN_00306e50(int, int, char *, unsigned char *, int, int);
extern char DAT_004e4600[];            /* property name of the flag */
extern PropertySet *DAT_00586dc8[4];
extern Obj *DAT_00562738[4];
extern Obj *DAT_00562740[4];
}

class Obj {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void configure(int);        /* +100 */
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void setKind(int);          /* +128 */
  virtual void setValue(int);         /* +132 */
  int refs;                           /* +4, low 23 bits count */
  int field8;
  int field12;
};

struct RefOps {
  static inline void release(Obj *o) {
    if (o != 0) {
      o->refs = o->refs - 1;
      if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
    }
  }
  /* release a reference held in a (volatile) stack slot; the slot is reloaded for the zero test */
  static inline void releaseSlot(Obj *volatile &slot) {
    Obj *o = slot;
    if (o != 0) {
      o->refs = o->refs - 1;
      o = slot;
      if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
    }
  }
};

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
  Obj *volatile t58, *volatile t54, *volatile t50, *volatile t4c, *volatile t48, *volatile t44, *volatile t40, *volatile t3c;
  unsigned char flag;
  Obj *s1;
  int props = DAT_00586dc8[0]->props;
  flag = 1;
  thunk_FUN_00306e50(props, 7, DAT_004e4600, &flag, 1, 1);
  self->enabled = flag;
  t58 = FUN_00132810(igObject_GetAllocator(self));
  s1 = t58;
  if (s1) s1->refs = s1->refs + 1;
  RefOps::release(self->f76);
  self->f76 = s1;
  RefOps::releaseSlot(t58);
  self->f76->setValue(self->a32);
  self->f76->configure(0);
  t54 = FUN_001325a0(igObject_GetAllocator(self));
  s1 = t54;
  if (s1) s1->refs = s1->refs + 1;
  RefOps::release(self->f80);
  self->f80 = s1;
  RefOps::releaseSlot(t54);
  self->f80->setKind(2);
  self->f80->configure(0);
  t50 = FUN_00131c60(igObject_GetAllocator(self));
  s1 = t50;
  if (s1) s1->refs = s1->refs + 1;
  RefOps::release(self->f84);
  self->f84 = s1;
  RefOps::releaseSlot(t50);
  self->f84->field12 = 2;
  self->f84->configure(0);
  if (self->p36 != 0) {
    self->p36->configure(0);
    t4c = FUN_001325a0(igObject_GetAllocator(self));
    s1 = t4c;
    if (s1) s1->refs = s1->refs + 1;
    RefOps::release(self->f88);
    self->f88 = s1;
    RefOps::releaseSlot(t4c);
    self->f88->setKind(0);
    self->f88->configure(0);
    self->f88->setValue(self->a40);
    t48 = FUN_00131c60(igObject_GetAllocator(self));
    s1 = t48;
    if (s1) s1->refs = s1->refs + 1;
    RefOps::release(self->f92);
    self->f92 = s1;
    RefOps::releaseSlot(t48);
    self->f92->field12 = 1;
    self->f92->configure(0);
    if (self->flag48) {
      s1 = DAT_00562738[0];
      if (s1) s1->refs = s1->refs + 1;
      RefOps::release(self->f96);
      self->f96 = s1;
    } else {
      s1 = DAT_00562740[0];
      if (s1) s1->refs = s1->refs + 1;
      RefOps::release(self->f96);
      self->f96 = s1;
    }
  }
  if (self->a52 != 0) {
    t44 = FUN_00132810(igObject_GetAllocator(self));
    s1 = t44;
    if (s1) s1->refs = s1->refs + 1;
    RefOps::release(self->f100);
    self->f100 = s1;
    RefOps::releaseSlot(t44);
    self->f100->setValue(self->a52);
    self->f100->configure(0);
    s1 = self->f88;
    if (s1 != 0 && self->a56 == self->a40) {
      if (s1) s1->refs = s1->refs + 1;
      RefOps::release(self->f104);
      self->f104 = s1;
    } else {
      t40 = FUN_001325a0(igObject_GetAllocator(self));
      s1 = t40;
      if (s1) s1->refs = s1->refs + 1;
      RefOps::release(self->f104);
      self->f104 = s1;
      RefOps::releaseSlot(t40);
      self->f104->setKind(0);
      self->f104->configure(0);
      self->f104->setValue(self->a56);
    }
    t3c = FUN_00131c60(igObject_GetAllocator(self));
    s1 = t3c;
    if (s1) s1->refs = s1->refs + 1;
    RefOps::release(self->f108);
    self->f108 = s1;
    RefOps::releaseSlot(t3c);
    self->f108->field12 = 0;
    self->f108->configure(0);
  }
}
