extern void memset(void *p, int c, int n);
typedef struct { char c[12]; } Name;
extern Name *FUN_002b25a8(void *h, int k);
int FUN_002b24b8(void *h, unsigned char k, char *dst) {
    Name *src;
    *dst = 0;
    src = FUN_002b25a8(h, k);
    if (src == 0) return 0;
    memset(dst, 0, 13);
    *(Name *)dst = *src;
    return 1;
}
