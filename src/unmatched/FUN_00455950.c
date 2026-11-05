int FUN_004578c0();
extern int DAT_0058c460[4];
typedef struct S { char pad[15]; unsigned char b; } S;
void FUN_00455950(S *arg0, unsigned char arg1) {
    int sp10[3];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != (arg1 & 0xFF)) {
        arg0->b = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c460[0];
        FUN_004578c0(arg0, sp10, temp_a2);
    }
}
