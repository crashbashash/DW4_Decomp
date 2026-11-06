extern "C" {
int FUN_001b23e0(int, void *);
int FUN_001b24d0(int, void *);
int igObject_IsKindOf(void *, int);
extern int DAT_0055f158[4];
extern int DAT_0055f170[4];
bool FUN_001b2600(int arg0, void *arg1);
}
class Elem { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct List { int pad0[2]; int count; int pad1; Elem **data; };
struct Owner { char pad[32]; List *list; };
bool FUN_001b2600(int arg0, void *arg1) {
    int i;
    bool ok;
    int n;
    List *l;
    Elem *e;
    ok = true;
    l = ((Owner *)arg1)->list;
    n = l->count;
    for (i = 0; i < n; i++) {
        e = l->data[i];
        if (igObject_IsKindOf(e, DAT_0055f170[0]) != 0) {
            if (FUN_001b23e0(arg0, e) == 0) {
                ok = false;
            }
        } else if (DAT_0055f158[0] == e->vX()) {
            if (FUN_001b24d0(arg0, e) == 0) {
                ok = false;
            }
        } else {
            ok = false;
        }
    }
    return ok;
}
