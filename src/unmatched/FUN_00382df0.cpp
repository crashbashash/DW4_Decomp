extern "C" int FUN_00301e30(int, void *);
extern "C" int DAT_00589658[4];
struct Obj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int v20();
};
struct L { char p[8]; int n; char q[4]; Obj **arr; };
struct M { char p[20]; L *list; };
struct T { char p[36]; int f36; };
extern "C" void FUN_00382df0(T *arg0, M *arg1) {
    int off, g, i;
    i = 0;
    if (0 < arg1->list->n) {
        off = 0;
        do {
            Obj *o = *(Obj **)((char *)arg1->list->arr + off);
            g = DAT_00589658[0];
            if (g == o->v20()) {
                FUN_00301e30(arg0->f36, o);
                asm { nop }
            }
            i++;
            off += 4;
        } while (i < arg1->list->n);
    }
}
