struct S { char pad[8]; char *f8; };
int strlen();
extern char *DAT_004c22f0[4];

void FUN_0032cac0(struct S *arg0) {
    int i;
    char *s;
    int c;

    s = arg0->f8;
    if (s == 0) {
        s = DAT_004c22f0[0];
    }
    i = strlen(s) - 1;
    while ((c = s[i]) == 0x20 || c == 9) {
        i--;
    }
    if (c != 0x5C) {
        if (c != 0x2F) {
            i += 1;
        }
    }
    s[i] = 0;
}
