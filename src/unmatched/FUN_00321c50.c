extern char DAT_004f7910[];
extern char DAT_004fe080[];
extern char DAT_004fe088[];
int sprintf();
int strlen();
char *FUN_00321c10();
char *FUN_00321c50(int arg0, int arg1, char *arg2) {
    int a;
    int i;
    char *s;
    char *sep;
    i = 0;
    *arg2 = 0;
    do {
        a = arg0 & (1 << i);
        if (a != 0) {
            s = FUN_00321c10(a, arg1);
            if (*s != 0) {
                if (*arg2 != 0) {
                    sep = DAT_004f7910;
                } else {
                    sep = DAT_004fe080;
                }
                sprintf(&arg2[strlen(arg2)], DAT_004fe088, sep, s);
            }
        }
        i++;
    } while (i < 32);
    return arg2;
}
