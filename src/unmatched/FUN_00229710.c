typedef struct R { int w0; int refs; } R;
typedef struct S { R *a; R *b; R *c; } S;
int igObject_Destroy();

S *FUN_00229710(S *arg0) {
    R *p;

    arg0->a = 0;
    arg0->b = 0;
    arg0->c = 0;
    p = arg0->a;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->a = 0;
    p = arg0->b;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->b = 0;
    p = arg0->c;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->c = 0;
    return arg0;
}
