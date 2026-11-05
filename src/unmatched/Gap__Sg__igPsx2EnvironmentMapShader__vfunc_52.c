typedef struct R { int w0; int refs; } R;
typedef struct S { char pad[112]; R *a; R *b; R *c; } S;
int FUN_001c2880();
int igObject_Destroy();

void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_52(S *arg0) {
    R *p;

    FUN_001c2880();
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
}
