extern "C" {
extern char *DAT_0058a214[4];
int strcmp(char *, char *);
int MDLisCallName(char *name);
static inline int isZero(int value) { return value == 0; }
}

int MDLisCallName(char *name) {
    char *s = DAT_0058a214[0];
    if (s == 0) return isZero((int)name);
    return isZero(strcmp(s, name));
}
