struct KindMatchObject {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int v20();
};
struct KindMatchList { char p[8]; int n; char q[4]; KindMatchObject **arr; };
struct KindMatchSource { char p[20]; KindMatchList * list; KindMatchList *getList() const { return list; } };
struct KindMatchTarget { char p[36]; int f36; };
extern "C" int FUN_00301e30(int, void *);
extern "C" int DAT_00589658[4];
static inline int count(KindMatchList *l) { return l->n; }
static inline KindMatchObject *at(KindMatchList *l, int i) { return l->arr[i]; }
extern "C" void FUN_00382df0(KindMatchTarget *arg0, KindMatchSource *arg1) {
    int i;
    for (i = 0; i < count(arg1->getList()); i++) {
        KindMatchObject *o = at(arg1->list, i);
        int g = DAT_00589658[0];
        if (g == o->v20()) {
            FUN_00301e30(arg0->f36, o);
        }
    }
}
