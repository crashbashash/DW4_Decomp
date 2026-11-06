/* IgCallStackTable vfunc 31: reserves/resizes the slot list to arg1 entries (or releases it for
 * 0), fills it from the table symbol, then walks the zero-terminated records through virtual 28.
 * Alternate compiler -O3; declaration order found by permutation search. */
extern "C" {
extern int DAT_004c1e98[];
void *FUN_002ca8b0(int);
int FUN_002d38e0(void *);
int List_Reserve(void *, int, int);
int List_Resize(void *, int, int);
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
}
struct Ref { int pad; union { int w; struct { unsigned cnt : 23; unsigned f : 9; } b; } u; };
struct IList { int w0; int w4; int count; int cap; unsigned *data; };
struct Tab { int w0; int w4; int count; int w12; unsigned *data; };
struct T {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27();
    virtual int v28(unsigned *, int);
    int pad[3];
    Tab *tab;
    IList *list;
};
extern "C" void Gap__Core__igCallStackTable__vfunc_31(T *self, int arg1)
{
    Ref *r;
    int cnt;
    IList *l;
    unsigned *var_a1_2;
    unsigned *data;
    int var_a0;
    IList *v;
    unsigned *temp_s2;
    int var_a1;
    unsigned *temp_s1_2;
    unsigned *var_s0;
    int temp_s1;

    FUN_002d38e0(self);
    if (arg1 != 0) {
        if (self->list == 0) {
            temp_s1 = igObject_GetAllocator(self);
            r = (Ref *)self->list;
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->list = (IList *)FUN_002ca8b0(temp_s1);
        }
        l = self->list;
        if (arg1 >= l->count) List_Reserve(l, arg1, 4);
        l = self->list;
        if (arg1 >= 0) {
            if (arg1 <= l->cap) l->count = arg1;
            else List_Resize(l, arg1, 4);
        }
        v = self->list;
        cnt = v->count;
        data = v->data;
        for (var_a1 = 0; var_a1 < cnt; var_a1++) data[var_a1] = *(unsigned *)DAT_004c1e98;
        temp_s2 = self->tab->data;
        var_s0 = temp_s2;
        temp_s1_2 = temp_s2 + self->tab->count;
        while (var_s0 < temp_s1_2) {
            if (!self->v28(var_s0, var_s0 - temp_s2)) return;
            var_a1_2 = var_s0;
            var_a0 = 0;
            while (*var_a1_2++ != 0) var_a0++;
            var_s0 += var_a0 + 1;
        }
    } else {
        r = (Ref *)self->list;
        if (r != 0) {
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->list = 0;
        }
    }
}
