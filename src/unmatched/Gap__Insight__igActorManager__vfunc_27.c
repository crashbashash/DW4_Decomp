/* The list pointer is re-read (volatile) in the body and in the loop test, with a `0 < n` guard. */
typedef struct L { char pad[8]; int n; int p; int *arr; } L;
typedef struct A { char pad[24]; L *f24; } A;
int igObject_IsKindOf(A *, int);
int FUN_00467030(int, int);
int igActorInfo_GetMetaObject(void);
#define F24 (*(L * volatile *)&arg1->f24)
int Gap__Insight__igActorManager__vfunc_27(int arg0, A *arg1) {
    int i;
    int off;
    if (igObject_IsKindOf(arg1, igActorInfo_GetMetaObject()) != 0) {
        i = 0;
        if (0 < arg1->f24->n) {
            off = 0;
            do {
                FUN_00467030(arg0, *(int *)((char *)F24->arr + off));
                i++;
                off += 4;
            } while (i < F24->n);
        }
        return 1;
    }
    return 0;
}
