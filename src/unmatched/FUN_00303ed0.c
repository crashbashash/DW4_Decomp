typedef struct Obj { int w0; int refs; } Obj;
typedef struct List { int w0; int w4; int count; int w12; Obj **data; } List;
typedef struct Owner { int w0; int w4; List *a; List *b; } Owner;
void igObject_Destroy(Obj *);

void FUN_00303ed0(Owner *o) {
    List *l = o->a;
    int n = l->count;
    int i;
    for (i = 0; i < n; i++) {
        Obj *p = l->data[i];
        if (p) {
            p->refs = p->refs - 1;
            if ((((unsigned long long)(long long)p->refs) & 0x7fffffULL) == 0) igObject_Destroy(p);
        }
    }
    { int m = l->count; for (i = 0; i < m; i++) l->data[i] = 0; }
    l->count = 0;
    l = o->b;
    n = l->count;
    for (i = 0; i < n; i++) {
        Obj *p = l->data[i];
        if (p) {
            p->refs = p->refs - 1;
            if ((((unsigned long long)(long long)p->refs) & 0x7fffffULL) == 0) igObject_Destroy(p);
        }
    }
    { int m = l->count; for (i = 0; i < m; i++) l->data[i] = 0; }
    l->count = 0;
}
