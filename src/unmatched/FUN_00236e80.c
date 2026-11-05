typedef struct L { char pad8[8]; int cnt; char pad12[4]; int *arr; } L;
typedef struct A { char pad104[104]; L *f68; } A;
int FUN_00236e20();

void FUN_00236e80(A *arg0) {
    int i;

    for (i = arg0->f68->cnt - 1; i >= 0; i--) {
        FUN_00236e20(arg0, arg0->f68->arr[i]);
    }
}
