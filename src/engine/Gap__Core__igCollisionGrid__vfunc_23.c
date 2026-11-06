struct E { char pad[36]; float f36; float f40; float f44; char pad2[12]; float f60; float f64; float f68; char pad3[16]; int f88; };
struct L { char pad[8]; int count; char pad2[4]; struct E **data; };
int Gap__Core__igCollisionGrid__vfunc_23(int arg0, struct L *arg1, int arg2) {
    struct E *e;
    int n = arg1->count;
    while (arg2 < n) {
        e = arg1->data[arg2];
        arg2++;
        e->f88 = 0x3F800000;
        e->f60 = e->f36;
        e->f64 = e->f40;
        e->f68 = e->f44;
    }
    return 0;
}