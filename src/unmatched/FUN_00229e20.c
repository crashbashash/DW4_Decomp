struct L { char p[8]; int n; };
int *FUN_00229270(int *p);
int FUN_0022a030(struct L *);
int *FUN_00229fb0(int *, int);
int FUN_00229f90(int *, int *);
int FUN_00229f70(int *, int *);
void StringRef_Destruct_00130720(int *, int);

int FUN_00229e20(struct L *arg0, int *arg1) {
    int h;
    int lo, hi, mid, base, res;
    FUN_00229270(&h);
    lo = 0;
    hi = arg0->n - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        base = FUN_0022a030(arg0);
        FUN_00229fb0(&h, base + mid * 4);
        if (FUN_00229f90(&h, arg1) != 0) { lo = mid + 1; continue; }
        if (FUN_00229f70(&h, arg1) != 0) { hi = mid - 1; continue; }
        StringRef_Destruct_00130720(&h, -1);
        res = mid;
        goto done;
    }
    if (arg0->n == 0) {
        StringRef_Destruct_00130720(&h, -1);
        res = -1;
    } else {
        base = FUN_0022a030(arg0);
        FUN_00229fb0(&h, base + lo * 4);
        if (FUN_00229f90(arg1, &h) != 0 || FUN_00229f70(arg1, &h) != 0) {
            StringRef_Destruct_00130720(&h, -1);
            res = -1;
        } else {
            StringRef_Destruct_00130720(&h, -1);
            res = lo;
        }
    }
done:
    return res;
}
