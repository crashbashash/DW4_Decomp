int memcpy();
struct S { int p[2]; int a; int q[2]; unsigned short h; };
void FUN_002fd130(struct S *arg0, int arg1, int arg2) {
    memcpy(arg1 + arg0->a, arg2, arg0->h);
}
