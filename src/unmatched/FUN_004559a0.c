int FUN_004578c0();
extern int DAT_0058c470[4];
struct S { char pad[28]; unsigned char b; };
void FUN_004559a0(struct S *arg0, unsigned char arg1) {
    int sp[3];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        sp[0] = 2;
        sp[1] = 0;
        sp[2] = DAT_0058c470[0];
        FUN_004578c0(arg0, sp, temp_a2);
    }
}
