unsigned int strlen(char *);
int strcasecmp(char *, char *);
int FUN_0030bb40(char *arg0, char *arg1) {
    unsigned int len = strlen(arg0);
    unsigned int slen = strlen(arg1);
    int dot = 1;
    int off;
    if (*arg1 == 0x2E) {
        dot = 0;
    }
    if (len < slen + dot) {
        return 0;
    }
    off = len - slen;
    if (arg0[off - dot] != 0x2E) {
        return 0;
    }
    {
        int r = strcasecmp(arg0 + off, arg1);
        return r == 0;
    }
}
