int FUN_0018aaa0();
int FUN_00190120();
struct S18d110 { char pad[8]; float a; char pad2[8]; float b; };
void FUN_0018d110(int arg0, struct S18d110 *arg1) {
    float buf[24];

    if (arg1->a <= arg1->b) {
        FUN_0018aaa0(arg1, buf);
        FUN_00190120(arg0, buf, 8);
    }
}
