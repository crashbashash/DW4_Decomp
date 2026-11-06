/* Configure the stage render-state objects (viewport/camera/clear/light setup). A straight run of
 * configuration writes: object fields (+12 mode words, +20/+24/+36 flags), the virtual setters at
 * vtable offsets +100 (select) and +128 (value) on the objects held in the globals
 * 0x5628f0..0x5629f0, a unit-colour vector copied into one object (0x562940), then the scene list
 * (0x5629a0, +32) is cleared and refilled with the object FUN_001d6900 returns, and the
 * projection/view helpers FUN_00191860 / FUN_00191b10 get their literal arguments. Names are role
 * hypotheses; evidence: asm/FUN_001d6a70.s. Matching constructs: dummy virtual slots give the
 * retail vtable offsets (offset = 8 + 4 * index); the stack vectors are declared in the order eye,
 * origin, up, white, forward so the frame offsets match, and the Vec4 is copied with float
 * loads/stores. Build: local/mwcps2/combat/mwccps2.exe (sha256
 * acf1088553362dddef7eee2d269848b03208e29fd26caa441848e57b6299786a), -O3 -Iinclude. */
struct Vec4 { float x, y, z, w; };
struct Vec3x { float x, y, z; };

class Gfx; class Lens; class GfxQuad; class GfxScene; class GfxVec;

/* Generic render-state object: select() is +100, set() +128. */
class Gfx {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void select(int);           /* +100 */
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void set(int);              /* +128 */
  virtual void set2(int);             /* +132 */
  virtual void set3(int);             /* +136 */
  int refs;                           /* +4 */
  int w8;
  int mode;                           /* +12 */
  int w16;
  int w20;
  unsigned char flag24;
  char pad25[3];
  int w28, w32;
  int w36;
};
class GfxQuad {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void select(int);
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void set(int, int, int, int);
};
class GfxVec {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void select(int);
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void set(const Vec4 *);
};
struct SceneList { int vtbl, refs, count, capacity; int *data; };
class GfxScene { public: int vtbl, refs, w8, mode; int w16, w20, w24, w28; SceneList *items; };
struct Ref { int vtbl; int refs; };
struct Lens {                             /* the object at 0x562900 / 0x562940 */
  int vtbl, refs, w8, mode;
  Vec4 color;                             /* +16 */
  int w32, w36, w40, w44;
  long long w48;
  int w56, w60, w64;
};
extern "C" {
void igObject_Destroy(void *);
int ObjectList_AppendRetained(...);
int FUN_001d6900(...);
void FUN_00191860(void *, float, float, float, float, float, float);
void FUN_00191b10(void *, void *, void *, void *);
int FUN_001931b0(void *, int, int, void *);
extern Gfx *DAT_005628f0[4];
extern Gfx *DAT_005628f8[4];
extern Lens *DAT_00562900[4];
extern Gfx *DAT_00562908[4];
extern Gfx *DAT_00562910[4];
extern Gfx *DAT_00562918[4];
extern Gfx *DAT_00562920[4];
extern Gfx *DAT_00562928[4];
extern Gfx *DAT_00562930[4];
extern Gfx *DAT_00562938[4];
extern Lens *DAT_00562940[4];
extern Gfx *DAT_00562948[4];
extern Gfx *DAT_00562950[4];
extern Gfx *DAT_00562958[4];
extern Gfx *DAT_00562960[4];
extern Gfx *DAT_00562968[4];
extern Gfx *DAT_00562970[4];
extern Gfx *DAT_00562978[4];
extern GfxQuad *DAT_00562980[4];
extern GfxQuad *DAT_00562988[4];
extern GfxQuad *DAT_00562990[4];
extern Gfx *DAT_00562998[4];
extern GfxScene *DAT_005629a0[4];
extern Gfx *DAT_005629a8[4];
extern Gfx *DAT_005629b0[4];
extern Gfx *DAT_005629b8[4];
extern Gfx *DAT_005629c0[4];
extern GfxVec *DAT_005629c8[4];
extern Gfx *DAT_005629d0[4];
extern Gfx *DAT_005629d8[4];
extern Gfx *DAT_005629e0[4];
extern Gfx *DAT_005629e8[4];
extern Gfx *DAT_005629f0[4];
}

extern "C" void FUN_001d6a70(void) {
  Ref *scratch;
  Vec3x eye, origin, up;
  Vec4 white;
  Vec4 forward;
  Lens *lens, *tint;
  DAT_005628f0[0]->mode = 2;
  DAT_005628f0[0]->flag24 = 1;
  DAT_005628f0[0]->w20 = -1;
  DAT_005628f0[0]->w36 = 1;
  DAT_00562908[0]->select(0);
  DAT_00562908[0]->set(1);
  DAT_00562918[0]->select(1);
  DAT_00562918[0]->set(1);
  DAT_00562920[0]->select(2);
  DAT_00562920[0]->set(1);
  DAT_00562928[0]->select(3);
  DAT_00562928[0]->set(1);
  DAT_00562930[0]->select(4);
  DAT_00562930[0]->set(1);
  DAT_00562910[0]->select(0);
  DAT_00562910[0]->set(0);
  DAT_005628f8[0]->set(0);
  lens = DAT_00562900[0];
  lens->w48 = (long long)0x3ff00000 << 32;
  lens->w64 = 0x3f800000;
  DAT_00562900[0]->mode = 2;
  white.x = 1.0f; white.y = 1.0f; white.z = 1.0f; white.w = 1.0f;
  tint = DAT_00562940[0];
  tint->color = white;
  tint->w60 = FUN_001931b0(&white, 1, 0x3f800000, lens);
  DAT_00562940[0]->mode = 3;
  DAT_00562948[0]->set(5);
  DAT_00562948[0]->select(0);
  DAT_00562950[0]->set(1);
  DAT_00562950[0]->select(0);
  DAT_00562958[0]->set(1);
  DAT_00562958[0]->select(1);
  DAT_00562960[0]->set(1);
  DAT_00562960[0]->select(2);
  DAT_00562968[0]->set(1);
  DAT_00562968[0]->select(0);
  DAT_00562970[0]->set(1);
  DAT_00562970[0]->select(1);
  DAT_00562978[0]->set(1);
  DAT_00562978[0]->select(2);
  DAT_00562980[0]->set(0, 0, 0, 0);
  DAT_00562988[0]->set(0, 0, 0, 1);
  DAT_00562990[0]->set(1, 1, 1, 0);
  DAT_00562998[0]->set(0);
  DAT_005629e8[0]->set(1);
  DAT_005629f0[0]->set(4);
  DAT_005629f0[0]->set2(5);
  DAT_00562938[0]->mode = 2;
  DAT_00562938[0]->select(0);
  FUN_001d6900(&scratch);
  {
    SceneList *list = DAT_005629a0[0]->items;
    int n = list->count;
    int m;
    int i;
    for (i = 0; i < n; i++) {
      Ref *o = (Ref *)list->data[i];
      if (o != 0) {
        o->refs = o->refs - 1;
        if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
      }
    }
    m = list->count;
    for (i = 0; i < m; i++) list->data[i] = 0;
    list->count = 0;
  }
  ObjectList_AppendRetained(DAT_005629a0[0]->items, scratch);
  FUN_00191860((char *)DAT_005629a8[0] + 12, -1.0f, 1.0f, -1.0f, 1.0f, -5.0f, 5.0f);
  up.x = 0.0f; up.y = 1.0f; up.z = 0.0f;
  origin.x = 0.0f; origin.y = 0.0f; origin.z = 0.0f;
  eye.x = 0.0f; eye.y = 0.0f; eye.z = 5.0f;
  FUN_00191b10((char *)DAT_005629b0[0] + 12, &eye, &origin, &up);
  {
    Ref *o = scratch;
    if (o != 0) {
      o->refs = o->refs - 1;
      if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
    }
  }
  DAT_005629c0[0]->set(0);
  DAT_005629b8[0]->set(0);
  forward.x = 0.0f; forward.y = 0.0f; forward.z = 0.0f; forward.w = 1.0f;
  DAT_005629c8[0]->set(&forward);
  DAT_005629e0[0]->set(1);
  DAT_005629d8[0]->set3(2);
  DAT_005629d8[0]->set(0);
  DAT_005629d0[0]->set(1);
  DAT_005629d0[0]->set2(1);
}
