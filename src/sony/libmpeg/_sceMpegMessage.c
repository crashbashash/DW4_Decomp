typedef struct { int type; char *msg; int pad[2]; } CbData;
typedef struct { char p0[12]; int m; char p1[2144]; void *cb; } X;
int FUN_00109208(void *, CbData *);
int FUN_00109ac8(char *);
int _sceMpegMessage(X *x, char *msg) {
    CbData d;
    if (x->cb != 0 && x != 0 && x->m != 0) {
        d.type = 0;
        d.msg = msg;
        return FUN_00109208(x->cb, &d);
    }
    return FUN_00109ac8(msg);
}
