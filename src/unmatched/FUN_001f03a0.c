struct S { long long f0; char pad[56]; unsigned char b0:1; unsigned char b1:1; unsigned char b2:6; };
int FUN_001efd90();
void FUN_001f0390(void);
extern struct S * DAT_00568f04[4];
long long FUN_001f03a0(void) {
    struct S *s = DAT_00568f04[0];
    unsigned char t;
    if (((const struct S *)s)->b1 != 1) {
        t = *(unsigned char *)((char *)s + 64);
        s->b1 = 1;
        FUN_001efd90(1, FUN_001f0390, 0, t);
    }
    return s->f0;
}