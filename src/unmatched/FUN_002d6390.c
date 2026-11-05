typedef struct { char p[8]; int a; int n; } S;
int FUN_002d60b0();
int FUN_002d6390(S *arg0) {
    if (arg0->a == 0) {
        FUN_002d60b0();
    }
    if (arg0->n <= 0) {
        return 0;
    }
    return arg0->a;
}
