/* The hook data is declared as an int array so it is addressed absolutely. */
int vsprintf(char *, int, char *);
extern int DAT_0056df30[4];
extern int DAT_0056df38[4];
void FUN_002467a0(int arg0, ...) {
    char sp10[4096];
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    vsprintf(sp10, arg0, (char *)__builtin_next_arg(arg0) - off);
    if (DAT_0056df30[0] != 0) {
        ((int (*)(char *, int))DAT_0056df30[0])(sp10, DAT_0056df38[0]);
    }
}
