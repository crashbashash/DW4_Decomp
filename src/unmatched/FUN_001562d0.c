struct C { int f0; int f4; int f8; int fc; };
struct B { char pad[16]; struct C **tab; };
struct A { char pad[308]; struct B *b; };
int FUN_001562d0(struct A *arg0, int arg1) {
    if (arg1 >= 0x2F) {
        return (*(struct C **)((char *)arg0->b->tab + arg1 * 4 - 188))->fc;
    }
    return -1;
}
