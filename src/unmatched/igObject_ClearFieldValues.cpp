extern "C" {
extern int *DAT_00587198[4];
void igObject_ClearFieldValues(int *arg0);
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int *vX(); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vX(int *); };
struct Q { int p0; int p1; B **data; int count; };
void igObject_ClearFieldValues(int *arg0) {
    Q *q;
    int i;
    int n;

    q = (Q *)((int *)((A *)arg0)->vX())[10];
    i = ((Q *)DAT_00587198[0][10])->count;
    n = q->count;
    for (; i < n; i++) {
        q->data[i]->vX(arg0);
    }
}
