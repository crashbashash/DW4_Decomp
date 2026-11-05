extern "C" {
typedef struct F {
    char p0[48];
    char *f48;
    char *f52;
    char *f56;
    unsigned char f60;
    unsigned char f61;
    unsigned char f62;
    unsigned char f63;
    int f64;
    int f68;
    char p72[8];
    int f80;
    char p84[12];
    void *f96;
} F;
int memcpy(char *, char *, int);
int FUN_002620d8(void *, int, char *);
int FUN_00262510(void *);
int FUN_00262540(void *);
char *FUN_002ed2b0(int, int, void *);
int FUN_00304430(int *);
int FUN_00304680();
int FUN_00333990(F *);
void *igObject_GetAllocator(F *);
extern int DAT_00500070[4];
int Gap__igAdxFile__vfunc_25(F *arg0, char *arg1, int arg2, int arg3) {
    int total;
    int n;
    int rem;
    int done;
    int a;
    int t;
    total = arg2 * arg3;
    if (arg0->f62 == 0) {
        n = total / arg0->f80;
        if (total % arg0->f80 != 0) {
            n += 1;
        }
        t = FUN_00262510(arg0->f96);
        if (t < FUN_00262540(arg0->f96)) {
            t = n + FUN_00262510(arg0->f96);
            if (FUN_00262540(arg0->f96) < t) {
                n = FUN_00262540(arg0->f96) - FUN_00262510(arg0->f96);
            }
            FUN_002620d8(arg0->f96, n, arg1);
        }
        if (arg0->f60 == 0 || arg0->f61 != 0) {
            FUN_00333990(arg0);
        }
        return arg3;
    }
    if (arg0->f63 == 0) {
        n = arg0->f64 / arg0->f80;
        t = FUN_00262510(arg0->f96);
        if (t < FUN_00262540(arg0->f96)) {
            t = n + FUN_00262510(arg0->f96);
            if (FUN_00262540(arg0->f96) < t) {
                n = FUN_00262540(arg0->f96) - FUN_00262510(arg0->f96);
            }
            FUN_002620d8(arg0->f96, n, arg0->f48);
        }
        if (arg0->f60 == 0 || arg0->f61 != 0) {
            FUN_00333990(arg0);
        }
        arg0->f68 = 0;
        arg0->f63 = 1;
    }
    rem = arg0->f64 - arg0->f68;
    if (total < rem) {
        arg0->f52 = arg0->f48 + arg0->f68;
        memcpy(arg1, arg0->f52, total);
        arg0->f68 = arg0->f68 + total;
        if (arg0->f68 > arg0->f64 - 1) {
            arg0->f63 = 0;
        }
        return arg3;
    }
    if (arg0->f56 == 0) {
        arg0->f56 = FUN_002ed2b0(arg0->f64, 0x40, igObject_GetAllocator(arg0));
        if (arg0->f56 == 0) {
            return 0;
        }
    }
    done = 0;
    if (0 < total) {
        do {
            n = arg0->f64 / arg0->f80;
            t = FUN_00262510(arg0->f96);
            if (t < FUN_00262540(arg0->f96)) {
                t = n + FUN_00262510(arg0->f96);
                if (FUN_00262540(arg0->f96) < t) {
                    n = FUN_00262540(arg0->f96) - FUN_00262510(arg0->f96);
                }
                FUN_002620d8(arg0->f96, n, arg0->f56);
            } else {
                FUN_00304430(&DAT_00500070[0]);
                FUN_00304680();
            }
            if (arg0->f60 == 0 || arg0->f61 != 0) {
                FUN_00333990(arg0);
            }
            if (arg0->f68 < arg0->f64 - 1) {
                arg0->f52 = arg0->f48 + arg0->f68;
                memcpy(arg1, arg0->f52, rem);
                done += rem;
                rem = total - done;
            }
            arg0->f68 = 0;
            a = arg0->f64;
            if (a < rem) {
                rem = a;
            }
            arg0->f52 = arg0->f56;
            arg0->f56 = arg0->f48;
            arg0->f48 = arg0->f52;
            memcpy(arg1 + done, arg0->f52, rem);
            done += rem;
            arg0->f68 = arg0->f68 + rem;
        } while (done < total);
    }
    return arg3;
}
}
