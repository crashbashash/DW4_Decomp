/* 0x00237b50 — FUN_00237b50. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
extern "C" {
class N;
struct L { char pad[8]; int cnt; int cap; N **data; };
class N { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); char pad[8]; L *f12; };
void FUN_00237b50(N *arg0, int arg1);
void FUN_00237b50(N *arg0, int arg1) {
    int n;
    int i;
    N *t;
    int m;
    int j;
    n = arg0->f12->cnt;
    for (i = 0; i < n; i++) {
        t = arg0->f12->data[i];
        if (t->vX(arg1) != 0) {
            m = t->f12->cnt;
            for (j = 0; j < m; j++) {
                t->f12->data[j]->vX(arg1);
            }
        }
    }
}
}
