struct L { int p[2]; int cnt; int cap; int *arr; };
struct E { int key; int w[4]; };
struct EL { int p[2]; int cnt; int cap; E *arr; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual int v28(); int p[3]; EL *ents; L *idx; };
extern "C" int Gap__Core__igLocationTable__vfunc_26(O *o, int key);
int Gap__Core__igLocationTable__vfunc_26(O *o, int key) {
int i = o->v28();
L *l = o->idx;
int e;
int n = l->cnt;
int j = 0;
int r = -1;
for (;;) { e = l->arr[i]; if (e == -1) { return r; } { int kk = o->ents->arr[e].key; if (kk == key) { r = e; break; } } i++; if (i >= n) i = 0; j++; if (!(j < n)) break; } return r;}
