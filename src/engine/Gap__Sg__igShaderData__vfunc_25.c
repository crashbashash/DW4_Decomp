typedef struct Obj { int w0; int references; } Obj;
typedef struct List { int pad0[2]; int count; int pad1; Obj **data; } List;
struct T { char pad[8]; List *l8; List *l12; Obj *o16; List *l20; };
int igObject_Destroy();
void Gap__Sg__igShaderData__vfunc_25(struct T *arg0) {
    List *l;
    int n;
    int i;
    Obj *o;
    l = arg0->l8;
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
    l = arg0->l12;
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
    l = arg0->l20;
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
    o = arg0->o16;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->o16 = 0;
}
