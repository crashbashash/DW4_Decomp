struct Obj { int w0; int references; };
struct List { int pad0[2]; int count; int pad1; Obj **data; };
struct T {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void v21();
    int pad4[2];
    int f12;
    List *f16;
    List *f20;
    char pad2[28];
    Obj *f52;
    Obj *f56;
};
extern "C" {
int FUN_001afc90(T *, Obj *);
int igObject_Destroy(void *);
extern List *DAT_00562578[4];
void FUN_001b0000(T *arg0, int arg1, Obj *arg2, Obj *arg3)
{
    List *l;
    int n;
    int i;
    Obj *o;
    if (arg2 != 0) {
        arg2->references = arg2->references + 1;
    }
    o = arg0->f56;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f56 = arg2;
    if (arg3 != 0) {
        arg3->references = arg3->references + 1;
    }
    o = arg0->f52;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f52 = arg3;
    arg0->v21();
    l = arg0->f20;
    n = l->count;
    for (i = 0; i < n; i++) {
        o = l->data[i];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m = l->count;
        int j;
        for (j = 0; j < m; j++) {
            l->data[j] = 0;
        }
    }
    l->count = 0;
    l = arg0->f16;
    n = l->count;
    for (i = 0; i < n; i++) {
        o = l->data[i];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m = l->count;
        int j;
        for (j = 0; j < m; j++) {
            l->data[j] = 0;
        }
    }
    l->count = 0;
    arg0->f12 = 0;
    n = DAT_00562578[0]->count;
    for (i = 0; i < n; i++) {
        FUN_001afc90(arg0, DAT_00562578[0]->data[i]);
    }
}
}
