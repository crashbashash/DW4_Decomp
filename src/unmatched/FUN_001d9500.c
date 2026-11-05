typedef struct E { char pad8[8]; int *f8; } E;
typedef struct L { char pad8[8]; int cnt; char pad12[4]; E **arr; } L;
typedef struct S { char pad16[16]; L *l; } S;
int FUN_0012a110();
extern int DAT_004e0858[4];
int FUN_001d9500(S *arg0, int arg1) {
    int i;
    int *p;

    for (i = 0; i < arg0->l->cnt; i++) {
        p = arg0->l->arr[i]->f8;
        p = p != 0 ? p : &DAT_004e0858[0];
        if (FUN_0012a110(p, arg1) == 0) {
            return i;
        }
    }
    return -1;
}
