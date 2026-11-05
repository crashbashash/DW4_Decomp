/* 0x002eeae0 - igMemoryDictionary vfunc_34 (rehash). Smart pointer kept in a volatile stack slot with plain copies for the tests; allocator call before the field reload; vcall at 124 with a discarded R; alternate -O3. */
extern "C" {
extern char DAT_004c2158[];
void *FUN_002ca260(int);
int List_Reserve(...);
int List_Resize(...);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct R { int v; };
union Ref { int w; struct { unsigned cnt:23; unsigned f:9; } b; };
class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R vIns(int, int); };
struct Tbl { int vt; Ref u; int size; int cap; int *data; };
struct Dict { int vt; int a4; int f8; int f12; Tbl *t; int f20; };
extern "C" {
int Gap__Core__igMemoryDictionary__vfunc_34(int *arg0, Dict *arg1, int arg2) {
    Tbl *volatile sp6C;
    int sz;
    int *dd;
    int var_a0;

    int temp_s2;
    int *var_s1;
    int var_s0;
    int a1;
    Tbl *t;
    Tbl *old;
    Tbl *q;
    int s0;
    int *p;
    sp6C = arg1->t;
    q = sp6C;
    if (q != 0) {
        q->u.w = q->u.w + 1;
    }
    q = sp6C;
    temp_s2 = q->size;
    var_s1 = q->data;
    arg1->f8 = arg2;
    arg1->f20 = 0;
    s0 = igObject_GetAllocator(arg1);
    old = arg1->t;
    if (old != 0) {
        old->u.w = old->u.w - 1;
        if (old->u.b.cnt == 0) {
            igObject_Destroy(old);
        }
    }
    arg1->t = (Tbl *)FUN_002ca260(s0);
    a1 = arg1->f8 * 2;
    if (a1 >= arg1->t->size) {
        List_Reserve(arg1->t, a1, 4);
    }
    t = arg1->t;
    if (t->data == 0) {
        *arg0 = DAT_004fb418[0];
        q = sp6C;
        if (q != 0) {
            q->u.w = q->u.w - 1;
            if (q->u.b.cnt == 0) {
                igObject_Destroy(q);
            }
        }
        return 0;
    }
    a1 = arg1->f8 * 2;
    if (a1 >= 0) {
        if (a1 <= t->cap) {
            t->size = a1;
        } else {
            List_Resize(t, a1, 4);
        }
    }
    t = arg1->t;
    sz = t->size;
    dd = t->data;
    for (var_a0 = 0; var_a0 < sz; var_a0++) {
        dd[var_a0] = *(int *)DAT_004c2158;
    }
    arg1->f12 = 0;
    for (var_s0 = 0; var_s0 < temp_s2; var_s0 += 2, var_s1 += 2) {
        if (var_s1[0] != 0) {
            ((VT *)arg1)->vIns(var_s1[0], var_s1[1]);
        }
    }
    *arg0 = DAT_004fb410[0];
    q = sp6C;
    if (q != 0) {
        q->u.w = q->u.w - 1;
        if (q->u.b.cnt == 0) {
            igObject_Destroy(q);
        }
    }
    return 0;
}
}
