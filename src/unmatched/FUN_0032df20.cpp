struct R { int a; };
class Obj {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual R vf29();
    virtual void v30();
    virtual R vf31(int);
};
struct Pool {
    unsigned short count;
    unsigned short cap;
    unsigned short nfree;
    unsigned short pad;
    unsigned short *ids;
    char *items;
};
struct Arg { int a0, a4, a8, ac; Obj *r; int p14, p18; Pool *pool; };
extern "C" {
void *FUN_002ed330(void *, int);
void *thunk_FUN_002ed330(void *, int);
void memset(void *, int, int);
unsigned short FUN_0032df20(Arg *self) {
    Pool *p;
    unsigned short r;
    self->r->vf31(1);
    p = self->pool;
    if (p->nfree == 0) {
        int i;
        p->items = (char*)thunk_FUN_002ed330(p->items, (p->count + 4) * 12);
        memset(p->items + p->count * 12, 0, 48);
        if (p->cap < 4) {
            p->ids = (unsigned short*)FUN_002ed330(p->ids, 8);
            p->cap = 4;
        }
        i = 0; do { p->ids[i] = p->count + i; i++; } while (i < 4);
        p->nfree = 4;
        p->count += 4;
    }
    r = p->ids[p->nfree - 1];
    p->nfree = p->nfree - 1;
    self->r->vf29();
    return r;
}
}
