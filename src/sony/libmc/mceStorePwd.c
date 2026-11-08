extern char DAT_0055db80[1024];
extern int DAT_00485198;
int FUN_0010af10(int sema);
unsigned int FUN_0012a78c(const char *s);
void *FUN_00127098(void *dst, const void *src, unsigned int n);
void mceStorePwd(char *dst) {
    unsigned int n;
    if (dst) {
        if (FUN_0012a78c((char *)((unsigned int)DAT_0055db80 | 0x20000000)) < 1024) {
            n = FUN_0012a78c((char *)((unsigned int)DAT_0055db80 | 0x20000000));
        } else {
            n = 1023;
        }
        FUN_00127098(dst, (char *)((unsigned int)DAT_0055db80 | 0x20000000), n);
        dst[n] = 0;
    }
    FUN_0010af10(DAT_00485198);
}
