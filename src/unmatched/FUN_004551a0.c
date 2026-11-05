int FUN_002fd150();
int FUN_004578c0();
struct S { char pad[8]; int a; int pad2; int b; };
void FUN_004551a0(struct S *arg0, int arg1, int arg2) {
    int sp[3];
    int b;
    FUN_002fd150(arg0->b, arg0->a, arg2, arg1);
    b = arg0->b;
    sp[0] = 2;
    sp[2] = b;
    sp[1] = (int)arg0;
    FUN_004578c0(arg0->a, sp);
}
