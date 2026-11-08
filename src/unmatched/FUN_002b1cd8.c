extern void *memset(void *p, int c, unsigned int n);
extern int FUN_002b1980(void *h);
typedef struct { char c[12]; } Name;
typedef struct { char pad[76]; Name name; } Info;
int FUN_002b1cd8(Info **h, char *dst) {
    Info *info;
    *dst = 0;
    info = h[1];
    if (FUN_002b1980(h) == 0) return 0;
    memset(dst, 0, 13);
    *(Name *)dst = info->name;
    return 1;
}
