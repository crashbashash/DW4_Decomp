typedef struct { int pad[5]; int a; int b; } S;
extern S DAT_00555fd8;
int FUN_0010d498(int arg0, int arg1) {
    S *p = &DAT_00555fd8;
    int r = p->a;
    p->a = arg0;
    p->b = arg1;
    return r;
}
