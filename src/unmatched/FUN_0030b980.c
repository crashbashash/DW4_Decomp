/* Strip the last path component: backwards scan for a slash or backslash (bottom-tested comma
 * loop), terminate the string, re-run the setter; alternate compiler -O3. */
struct P { int a; int b; char *path; int len; };
int FUN_0030b3c0();
extern int DAT_004c22f0[4];
void FUN_0030b980(struct P *p) {
    char *base = p->path;
    char *q;
    if (base != 0) {
        q = base + p->len;
        while (q--, base < q) {
            if (*q == 0x5C || *q == 0x2F) {
                *q = 0;
                FUN_0030b3c0(p, p->path);
                break;
            }
        }
        if (q == p->path) {
            FUN_0030b3c0(p, DAT_004c22f0[0]);
        }
    }
}
