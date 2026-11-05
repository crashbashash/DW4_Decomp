int FUN_004658c0();
struct S465dc0 { char pad[132]; unsigned char f; };
void FUN_00465dc0(struct S465dc0 *arg0) {
    if (arg0->f != 0) {
        arg0->f = 0;
        FUN_004658c0();
    }
}
