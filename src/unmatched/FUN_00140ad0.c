/* 0x00140ad0 - FUN_00140ad0. Stores a retained object into slot arg2 of a retained-object array (slot 0 is a separate field at +48), growing the array on first use; refcount decrement/destroy written out with the 23-bit mask; declaration order s1,s0,n,a0,v1,a0b found by permdecl; alternate compiler -O3. */
typedef struct L { char p[8]; int n; int p1; int *d; } L;
typedef struct T { char p[48]; int *f48; char q[4]; int f56; int f60; L *f64; } T;
int ObjectList_ResizeRetained(L *, int);
int igObject_Destroy(int *);
void FUN_00140ad0(T *arg0, int *arg1, int arg2) {
    L *s1;
    int s0;
    int n;
    int *a0;
    int v1;
    int *a0b;
    if (arg2 == 0) {
        if (arg1 != 0) {
            arg1[1] = arg1[1] + 1;
        }
        a0 = arg0->f48;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f48 = arg1;
        return;
    }
    if (arg0->f64->n == 0) {
        ObjectList_ResizeRetained(arg0->f64, arg0->f60 - 1);
    }
    s1 = arg0->f64;
    if (arg1 != 0) {
        arg1[1] = arg1[1] + 1;
    }
    s0 = arg2 * 4;
    a0b = *(int **)((char *)s1->d + s0 - 4);
    if (a0b != 0) {
        a0b[1] = a0b[1] - 1;
        if ((a0b[1] & 0x7FFFFF) == 0) {
            igObject_Destroy(a0b);
        }
    }
    n = s1->n;
    v1 = arg2 - 1;
    if (n != 0 && v1 >= 0 && v1 < n) {
        *(int **)(s0 + (int)s1->d - 4) = arg1;
    }
}
