struct L { int p[2]; int cnt; int cap; int *arr; };
struct E { int pad; unsigned start; int len; int w; };
struct L2 { int p[2]; int cnt; int cap; unsigned *arr; };
struct EL { int p[2]; int cnt; int cap; E *arr; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int v28();
  char pp[24]; EL *ents; L *idx; };
extern "C" int Gap__Core__igSymbolTable__vfunc_26(O *o, unsigned key);
int Gap__Core__igSymbolTable__vfunc_26(O *o, unsigned key) {
E *en1; int len2; int i; int i0; int e1; int len1; unsigned st2; int cnt; int e2; unsigned end1; unsigned end2; int k; unsigned st1; int j; E *en2; L *l;
    i0 = o->v28();
    i = i0;
    l = o->idx;
    cnt = l->cnt;
    j = 0;
    for (;;) {
        e1 = l->arr[i];
        if (e1 == -1) break;
        en1 = &o->ents->arr[e1];
        len1 = en1->len;
        if (len1 != 0) { st1 = en1->start; end1 = st1 + len1; }
        else { st1 = en1->start; end1 = st1 + len1 + 1; }
        if (key >= st1) { if (key <= end1) return e1; }
        i++;
        if (i >= cnt) i = 0;
        j++;
        if (j >= cnt) return -1;
    }
    k = i0 - 1;
    L2 *l2 = (L2*)l;
    while (k > 0) {
        if (l2->arr[k] != (unsigned)-1) break;
        k--;
    }
    while (k > 0) {
        e2 = l2->arr[k];
        if (e2 == -1) return -1;
        en2 = &o->ents->arr[e2];
        len2 = en2->len;
        if (len2 != 0) { st2 = en2->start; end2 = st2 + len2; }
        else { st2 = en2->start; end2 = st2 + len2 + 1; }
        if (key >= st2) { if (key <= end2) return e2; }
        k--;
    }
    return -1;
}
