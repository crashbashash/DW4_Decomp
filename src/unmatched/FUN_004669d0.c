int FUN_00456a60();
int FUN_004569c0(int, unsigned char);
struct S80 { char pad[80]; int f80; char pad2[4]; int f88; unsigned char f92; };
void FUN_004669d0(struct S80 *arg0) {
    if (arg0->f80 != 0) {
        FUN_00456a60(arg0->f80, arg0->f88);
        FUN_004569c0(arg0->f80, arg0->f92);
    }
}
