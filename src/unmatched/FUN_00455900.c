int FUN_004578c0();
extern int DAT_0058c458[4];
struct S { char pad[14]; unsigned char f; };
void FUN_00455900(struct S *arg0, unsigned char arg1) {
    int sp10[3];
    unsigned char temp_a2;

    temp_a2 = arg0->f;
    if (temp_a2 != arg1) {
        arg0->f = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c458[0];
        FUN_004578c0(arg0, sp10, temp_a2);
    }
}
