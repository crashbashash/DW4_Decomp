struct S { char pad[44]; int p; int cap; int pad2; int len; };
int FUN_00300e50(struct S *, int, int);
int igObject_AllocateStorage(struct S *, int);
void FUN_0032b5b0(struct S *arg0, int arg1) {
    int n;
    if (arg0->cap < arg1) {
        if (arg1 > 0x100000) {
            n = arg1 + 0x100000;
        } else {
            n = arg1 * 2;
        }
        if (arg0->p != 0) {
            arg0->p = FUN_00300e50(arg0, arg0->p, n);
        } else {
            arg0->p = igObject_AllocateStorage(arg0, n);
        }
        arg0->cap = n;
    }
    arg0->len = arg1;
}

