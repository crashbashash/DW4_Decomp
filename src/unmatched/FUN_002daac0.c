/* The character variable is an int; a char would add a sign extension. */
struct B { char pad0[12]; int f12; };
struct S { char pad0[40]; struct B *f40; };
int strlen(char *);
int FUN_002da770();
int FUN_002dacc0(struct S *, int, char *, int);
int FUN_0030b460(struct B *, char *, int, int);
void FUN_002daac0(struct S *arg0, int arg1) {
    char buf[4096];
    char *p;
    int c;
    struct B *b;
    int n;
    FUN_002da770();
    while (FUN_002dacc0(arg0, arg1, buf, 0x1000) != 0) {
        p = buf;
        while ((c = *p) != 0) {
            if (c == 0x3B) {
                *p = 0xA;
                p[1] = 0;
                break;
            }
            p++;
        }
        b = arg0->f40;
        n = b->f12;
        FUN_0030b460(b, buf, n, strlen(buf));
    }
}
