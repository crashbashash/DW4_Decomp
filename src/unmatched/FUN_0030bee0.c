/* 0x0030bee0 - 192 bytes. Trims whitespace (ctype-table bit 8) from both ends of a duplicated string. The first callee takes the forwarded receiver; the table is declared 260 bytes so it is not gp-relative; alternate compiler -O3. */
struct S { char pad0[8]; int f8; };
int strlen(char *);
int FUN_0030b3c0(struct S *, char *);
int Memory_FreeBuffer(char *);
char *igObject_DuplicateString(struct S *, int);
extern char DAT_004d3d10[260];
void FUN_0030bee0(struct S *arg0) {
    int n;
    char *s;
    char *p;
    if (arg0->f8 != 0) {
        s = igObject_DuplicateString(arg0, arg0->f8);
        n = strlen(s) - 1;
        while (n >= 0 && (DAT_004d3d10[s[n] + 1] & 8)) {
            s[n] = 0;
            n -= 1;
        }
        p = s;
        while (*p != 0 && (DAT_004d3d10[*p + 1] & 8)) {
            p += 1;
        }
        FUN_0030b3c0(arg0, p);
        Memory_FreeBuffer(s);
    }
}
