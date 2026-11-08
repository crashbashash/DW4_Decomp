extern char D_004f5878[];
extern char D_004f5888[];
extern char D_004f5890[];
extern char D_004f5898[];
extern char D_004f58a0[];
extern void FUN_002b45b0(void *h, char *a, char *b, int *o1, int *o2);
extern int sscanf(const char *s, const char *fmt, ...);
extern long long __muldi3(long long n, int k);
void FUN_002b4498(void *h, int k, int *o1, int *o2) {
    int p, len;
    long long n;
    long long x, y, z;
    char *str;
    FUN_002b45b0(h, D_004f5888, D_004f5878, &p, &len);
    if (p == 0) {
        *o1 = 0;
        *o2 = 0x7FFFFFFF;
        return;
    }
    sscanf((char *)p, D_004f5890, &n);
    FUN_002b45b0(h, D_004f5898, D_004f5878, &p, &len);
    str = (char *)p;
    if (str == 0) {
        *o1 = 0x7FFFFFFF;
        return;
    }
    sscanf(str + (int)__muldi3(n, k), D_004f58a0, &x, &y, &z);
    *o1 = y;
    *o2 = z;
}
