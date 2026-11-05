class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); };
struct L { char pad[8]; int count; char pad2[4]; VC **data; };
struct S { char pad[52]; L *list; };
extern "C" {
int FUN_002d4e90(S *arg0);
}
int FUN_002d4e90(S *arg0) {
    int mx = 0;
    int i = 0;
    while (i < arg0->list->count) {
        int r = arg0->list->data[i]->vX();
        if (mx < r) mx = r;
        i++;
    }
    return mx;
}
