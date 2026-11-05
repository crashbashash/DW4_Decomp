extern "C" {
int igObject_IsKindOf(char *, int);
int FUN_003a3960(char *, char *);
extern int DAT_00561d78[4];
extern int DAT_0058a0a0[4];
int FUN_003a3850(char* arg0, char* arg1);
}
int FUN_003a3850(char* arg0, char* arg1) {
    char *s1;
    char *s0;
    if (arg0 != 0 && igObject_IsKindOf(arg0, DAT_00561d78[0]) != 0) {
        s1 = arg0;
    } else {
        s1 = 0;
    }
    if (arg1 != 0 && igObject_IsKindOf(arg1, DAT_0058a0a0[0]) != 0) {
        s0 = arg1;
    } else {
        s0 = 0;
    }
    return (s1 != 0 && s0 != 0) ? FUN_003a3960(s0, s1) : 0;
}
