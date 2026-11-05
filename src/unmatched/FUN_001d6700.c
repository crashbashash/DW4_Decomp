struct T { int word0; int references; };
struct O { char pad[20]; int f20; };
int FUN_001d6790();
struct T *FUN_002c72c0();
int FUN_002d8620();
void igObject_Destroy(struct T *);
int igObject_GetAllocator();
void FUN_001d6700(struct O *arg0) {
    struct T *volatile sp2C;
    struct T *o;

    sp2C = FUN_002c72c0(igObject_GetAllocator(arg0));
    FUN_002d8620(sp2C, arg0->f20, 0, 0);
    FUN_001d6790(arg0, sp2C);
    o = sp2C;
    if (o != 0) {
        --o->references;
        if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
            igObject_Destroy(o);
        }
    }
}
