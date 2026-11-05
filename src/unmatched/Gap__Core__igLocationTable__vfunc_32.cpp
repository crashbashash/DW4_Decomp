/* 0x002eb980 - Gap__Core__igLocationTable__vfunc_32. Location table clear-and-visit: reserve/resize the index list, fill it with the default word, then walk the 20-byte entries calling a virtual per entry (division of the pointer difference by 20 keeps the div); capacity test spelled arg1 <= cap; default compiler. Verified byte-identical by tools/verify.py. */

struct E { int w[5]; };
struct IL { int p[2]; int cnt; int cap; int *arr; };
struct EL { int p[2]; int cnt; int cap; E *arr; };
class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int v124(int, int); };
struct Tab : VT { int p[3]; EL *ents; IL *idx; };
extern "C" { int FUN_002eb0a0(); int List_Reserve(IL *, int, int); int List_Resize(IL *, int, int); extern int DAT_004c2148[]; }
extern "C" void Gap__Core__igLocationTable__vfunc_32(Tab *arg0, int arg1);
void Gap__Core__igLocationTable__vfunc_32(Tab *arg0, int arg1) {
    IL *l; int i; int *a; int n; E *s0; E *s1; E *s3;
    FUN_002eb0a0();
    l = arg0->idx;
    if (!(arg1 < l->cnt)) List_Reserve(l, arg1, 4);
    l = arg0->idx;
    if (arg1 >= 0) {
        if (!(arg1 > l->cap)) { l->cnt = arg1; } else { List_Resize(l, arg1, 4); }
    }
    l = arg0->idx;
    n = l->cnt;
    a = l->arr;
    for (i = 0; i < n; i++) {
        a[i] = DAT_004c2148[0];
    }
    EL *e = arg0->ents;
    s1 = e->arr;
    s0 = s1;
    s3 = s1 + e->cnt / 5;
    while (s0 < s3) {
        if (arg0->v124(s0->w[0], s0 - s1) == 0) break;
        s0++;
    }
}
