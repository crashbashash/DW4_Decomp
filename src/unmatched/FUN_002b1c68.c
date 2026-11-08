extern void *memset(void *p, int c, unsigned int n);
extern int FUN_002b1980(void *h);
typedef struct { char c[12]; } Name;
int FUN_002b1c68(char **h, char *dst) {
    Name *src = (Name *)(h[1] + 64);
    if (FUN_002b1980(h) == 0) return 0;
    memset(dst, 0, 13);
    *(Name *)dst = *src;
    return 1;
}
