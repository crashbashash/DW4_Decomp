extern "C" {
extern char *DAT_0058a214[4];
int igStrCmp(char *, char *);
int MDLisCallName(char *name);
}

int MDLisCallName(char *name) {
    char *s = DAT_0058a214[0];
    if (s == 0) return name == 0;
    asm("nop");
    return igStrCmp(s, name) == 0;
}
