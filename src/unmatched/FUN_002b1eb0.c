extern void *memset(void *p, int c, unsigned int n);
extern int FUN_002b1980(void *h);
typedef struct { char c[64]; } Name;
int FUN_002b1eb0(char **h, char *dst) {
    Name *src;
    *dst = 0;
    src = (Name *)(h[1] + 224);
    if (FUN_002b1980(h) == 0) return 0;
    memset(dst, 0, 65);
    *(Name *)dst = *src;
    return 1;
}
