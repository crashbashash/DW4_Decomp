struct T { int word0; int references; };
struct N { int word0; int references; int f8; int f12; struct T *f16; };
struct W { char pad8[8]; int f8; };
struct N *FUN_0044dc20(int);
int ObjectList_AppendRetained(int, struct N *);
void igObject_Destroy(struct T *);
int igObject_GetAllocator(void *);
void FUN_004573f0(struct W *arg0, int arg1, int arg2, struct T *arg3) {
    struct N *volatile sp5C;
    struct T **p; struct T *old; struct N *r;
    sp5C = FUN_0044dc20(igObject_GetAllocator(arg0));
    sp5C->f8 = arg1;
    sp5C->f12 = arg2;
    p = &sp5C->f16;
    if (arg3 != 0) { arg3->references = arg3->references + 1; }
    old = *p;
    if (old != 0) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    *p = arg3;
    ObjectList_AppendRetained(arg0->f8, sp5C);
    r = sp5C;
    if (r != 0) {
        --r->references;
        if (((unsigned long long)(long long)r->references & 0x7fffffULL) == 0) {
            igObject_Destroy((struct T *)r);
        }
    }
}
