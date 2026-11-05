class S;
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(S *); };
struct L { char pad[8]; int count; char pad2[4]; VC **data; };
class S { public: char pad[8]; L *list; };
extern "C" {
void FUN_00147930(S *arg0);
}
void FUN_00147930(S *arg0) {
    int n = arg0->list->count;
    int i;
    for (i = 0; i < n; i++) {
        arg0->list->data[i]->vX(arg0);
    }
}
