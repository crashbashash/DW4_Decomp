/* Varargs formatter into a 4096-byte stack buffer (FUN_0012fde0) followed by the optional output
 * hook DAT_0056df30; varargs forwarder template of FUN_00304550, hook data declared as an int
 * array so it is addressed absolutely; alternate compiler -O3. */
int FUN_0012fde0(char *, int, char *);
extern int DAT_0056df30[4];
extern int DAT_0056df38[4];
void FUN_002467a0(int arg0, ...) {
    char sp10[4096];
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    FUN_0012fde0(sp10, arg0, (char *)__builtin_next_arg(arg0) - off);
    if (DAT_0056df30[0] != 0) {
        ((int (*)(char *, int))DAT_0056df30[0])(sp10, DAT_0056df38[0]);
    }
}
