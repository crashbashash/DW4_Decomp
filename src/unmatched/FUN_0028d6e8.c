int FUN_0028d760(int a, int b);
void FUN_0028b5f8(void);
void FUN_0028d498(void);

extern char DAT_004f2998[];
extern char *volatile DAT_00573f08;
extern unsigned char DAT_004f29e8;

int FUN_0028d6e8(int a, int b) {
    int result;

    DAT_00573f08 = DAT_004f2998;
    if (DAT_004f29e8 != 4) {
        for (;;) {
            ((void (*)(void))-1)();
        }
    }
    result = FUN_0028d760(a, b);
    if (result != 0) {
        return result;
    }
    FUN_0028b5f8();
    FUN_0028d498();
    return 0;
}
