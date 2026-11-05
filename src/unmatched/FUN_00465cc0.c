int FUN_004578c0();
int FUN_004658d0();
int FUN_00465a40(char *, float);
int FUN_00465b90();
extern int DAT_0058cd38[4];
void FUN_00465cc0(char *arg0, float fparg0) {
    int sp[3];
    int temp_s0;

    temp_s0 = *(int *)(arg0 + 8);
    FUN_004658d0(arg0);
    if (*(unsigned char *)(arg0 + 132) != 0) {
        FUN_00465b90(arg0);
    }
    FUN_00465a40(arg0, fparg0);
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = DAT_0058cd38[0];
    FUN_004578c0(temp_s0, sp);
}
