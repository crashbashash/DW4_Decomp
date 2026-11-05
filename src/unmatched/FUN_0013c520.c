int FUN_00180030();
struct S { char pad[12]; int a; int pad2; int b; };
void FUN_0013c520(struct S *arg0, int arg1) {
    FUN_00180030(arg1, arg0->b, arg0->a);
}
