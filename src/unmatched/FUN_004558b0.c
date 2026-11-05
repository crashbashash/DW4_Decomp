struct S { char pad[13]; unsigned char b; };
int FUN_004578c0();
extern int DAT_0058c450[4];
void FUN_004558b0(struct S *arg0, unsigned char arg1) {
    int sp10[4];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c450[0];
        FUN_004578c0(arg0, &sp10[0], temp_a2);
    }
}
