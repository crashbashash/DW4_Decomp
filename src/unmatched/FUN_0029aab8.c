extern int DAT_004bd254;
extern int DAT_004be8a8;
extern volatile int DAT_004be8ac;
char *FUN_00294a30(int);
int FUN_0029a308(int *);
void FUN_002aa708(void);

void FUN_0029aab8(void) {
    int state;
    int *flag;

    DAT_004be8a8++;
    DAT_004be8ac++;
    state = DAT_004bd254;
    if (state == 1) {
        flag = (int *)(FUN_00294a30(1) + 92);
        if (FUN_0029a308(flag) != 0) {
            if (DAT_004bd254 == state) {
                FUN_002aa708();
            }
            *flag = 0;
        }
    }
}
