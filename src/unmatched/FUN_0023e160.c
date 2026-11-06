/* String-hashed entry constructor; 12-bit index plus four flag bits as mixed short/char bitfields
 * (separate read-modify-write per field), loop pointer assigned after the length call so it stays
 * in a1; default compiler. */
typedef struct R {
    unsigned hash; int w4; int w8; char *name; int v0; int v1; int v2; int f28; int f32; int f36;
    short f40;
    unsigned short idx : 12;
    unsigned char c4 : 1;
    unsigned char c5 : 1;
    unsigned char c6 : 1;
    unsigned char c7 : 1;
} R;
int strlen(char *);
void FUN_00245020(R *, char *);
R *FUN_0023e160(R *arg0, int arg1, short arg2, char *arg3, int *arg4, int arg5, int arg6, int arg7) {
    int s0 = 0;
    int n;
    char *p;
    int t;
    n = strlen(arg3);
    p = arg3;
    while (n-- != 0) {
        s0 = s0 + (*p + ((s0 << 5) + (s0 << 2)));
        p++;
    }
    arg0->hash = arg5 ^ s0;
    arg0->w4 = 0;
    arg0->w8 = 0;
    FUN_00245020(arg0, p);
    arg0->name = arg3;
    arg0->v0 = arg4[0];
    arg0->v1 = arg4[1];
    arg0->v2 = arg4[2];
    arg0->f28 = arg5;
    arg0->f32 = arg1;
    arg0->f36 = 0;
    arg0->f40 = arg2;
    arg0->idx = arg7;
    t = *(char *)arg4 != 0x10;
    if (t != 0) {
        t = **(char **)(arg5 + 12) != 0;
    }
    arg0->c4 = t;
    arg0->c5 = 1;
    arg0->c6 = 0;
    arg0->c7 = arg6;
    return arg0;
}
