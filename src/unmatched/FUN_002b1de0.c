typedef struct { char pad[24]; unsigned char major; unsigned char minor; } Info;
extern int FUN_002b1d48(void *h, char *buf);
extern int FUN_002b20c8(char *buf, int *maj, int *min);
int FUN_002b1de0(char **h, int *pmaj, int *pmin) {
    char buf[48];
    int maj, min;
    Info *info;
    int a, b, r;
    *pmaj = 0;
    *pmin = 0;
    info = (Info *)(h[1] + 32);
    r = FUN_002b1d48(h, buf);
    if (r == 0) return r;
    a = info->major;
    b = info->minor;
    r = FUN_002b20c8(buf, &maj, &min);
    if (r == 0) return r;
    if (a * 100 + b >= maj * 100 + min) {
        *pmaj = a;
        *pmin = b;
    } else {
        *pmaj = maj;
        *pmin = min;
    }
    return 1;
}
