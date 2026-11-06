/* Per-slot listing with duplicate-object scan and virtual lookups; found-flag as bool, declaration
 * order found by permutation search; default compiler. */
extern "C" {
int sprintf(...);
int strncpy(char *, char *, int);
int FUN_002dcc50(void *);
extern char *DAT_00586dc8[4];
extern char DAT_004fab08[];
}
struct R { int a; };
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(int); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual R v176(char *); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual VB * v356(); };
extern "C" void FUN_002f78b0(VA *arg0);
void FUN_002f78b0(VA *arg0) {
    char sp70[256];

    bool s0;
    VB *s1;
    int s2;
    int s3;
    int s4;

    VB *t;
    R r;
    s4 = 0;
    s0 = false;
    do {
        t = *(VB **)((char *)arg0 + s4 * 144 + 20);
        if (t != 0) {
            s1 = (VB *)t->v356();
            s2 = 0;
            if (s1 != 0) {
                s3 = 0;
                while (s3 < s4) {
                    t = *(VB **)((char *)arg0 + s3 * 144 + 20);
                    if (t != 0 && t->v356() == s1) {
                        s2 = 1;
                        break;
                    }
                    s3 += 1;
                }
                if (s2 == 0 && s1 != 0) {
                    sp70[255] = 0;
                    if (!s0) {
                        if (s4 == 0 || s4 == 1) {
                            strncpy(sp70, DAT_00586dc8[0] + 528, 255);
                            s0 = true;
                        } else {
                            goto b16;
                        }
                    } else {
b16:
                        if (s4 == 4) {
                            strncpy(sp70, DAT_00586dc8[0] + 656, 255);
                        } else {
                            sp70[0] = 0;
                        }
                    }
                    if (sp70[0] == 0) {
                        sprintf(sp70, DAT_004fab08, arg0->v104(s4));
                    }
                    if (FUN_002dcc50(s1) != 0) {
                        r = s1->v176(sp70);
                    }
                }
            }
        }
        s4 += 1;
    } while (s4 < 46);
}
