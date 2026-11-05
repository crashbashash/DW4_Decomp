extern "C" {
void FUN_002d5020(struct S *arg0, int arg1);
}
class DW4VC_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int); };
struct L { char pad[8]; int n; int pad2; DW4VC_124_0 **arr; };
struct S { char pad[52]; L *list; };
void FUN_002d5020(S *arg0, int arg1) {
    L *l;
    int i;
    i = 0;
    while (l = arg0->list, i < l->n) {
        l->arr[i]->vX(arg1);
        i++;
    }
}
