extern "C" {
char *FUN_0030d1d0(void *, int);
void strncpy(char *, char *, int);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct Entry { int key; int f4; int f8; int f12; int f16; };
struct Dat { char p[8]; int count; char p12[4]; int *data; };
struct Dat2 { char p[16]; Entry *data; };
class LV { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int v120(int); };
class LT : public LV { public: char p4[12]; Dat2 *f16; Dat *f20; void *f24; void *f28; };
extern "C" void Gap__Core__igLocationTable__vfunc_27(int *arg0, LT *arg1, int arg2, char *arg3, int arg4, int *arg5, char *arg6, int arg7, int *arg_sp0);
void Gap__Core__igLocationTable__vfunc_27(int *arg0, LT *arg1, int arg2, char *arg3, int arg4, int *arg5, char *arg6, int arg7, int *arg_sp0) {
    int h; 
    int n; 
    int i; 
    int res; 
    int *idx;
    Dat *d;
    Entry *e;
    char *s;
    char *s2;

    h = arg1->v120(arg2);
    d = arg1->f20;
    res = DAT_004fb418[0];
    n = d->count;
    idx = d->data;
    i = 0;
    do {
        if (idx[h] == -1) {
            *arg0 = res;
            return;
        }
        e = &arg1->f16->data[idx[h]];
        if (e->key == arg2) {
            if (arg3 != 0) {
                if ((s = FUN_0030d1d0(arg1->f24, e->f4)) != 0) {
                    strncpy(arg3, s, arg4);
                } else {
                    *arg3 = 0;
                }
            }
            *arg5 = e->f8;
            if (arg6 != 0) {
                if ((s2 = FUN_0030d1d0(arg1->f28, e->f12)) != 0) {
                    strncpy(arg6, s2, arg7);
                } else {
                    *arg6 = 0;
                }
            }
            *arg_sp0 = e->f16;
            res = DAT_004fb410[0];
            break;
        }
        h++;
        if (h >= n) {
            h = 0;
        }
        i++;
    } while (i < n);
    *arg0 = res;
}
