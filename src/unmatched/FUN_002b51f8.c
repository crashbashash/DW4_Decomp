struct T { char *s[2]; };
extern struct T DAT_004f5a30;
extern struct T DAT_004f5a48;
extern struct T DAT_004f5a60;
char *strncpy();
void FUN_002b51f8(char *arg0, int *arg1) {
    struct T a = DAT_004f5a30;
    struct T b = DAT_004f5a48;
    struct T c = DAT_004f5a60;
    strncpy(arg0 + 2, a.s[arg1[0]], 1);
    strncpy(arg0 + 3, b.s[arg1[1]], 1);
    strncpy(arg0 + 4, c.s[arg1[2]], 1);
}
