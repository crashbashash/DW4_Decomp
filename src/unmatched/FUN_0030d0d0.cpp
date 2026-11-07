extern "C" {
int List_Resize(...);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void FUN_0030d0d0(int *arg0, void *arg1, int arg2);
}
struct L {
    int pad[2];
    int count;
    int cap;
    char *data;
    void SetCount(int n) {
        if (n >= 0) {
            if (n <= cap) {
                count = n;
            } else {
                List_Resize(this, n, 1);
            }
        }
    }
};
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void v100(int); };
struct O { char pad[12]; int f12; L *l; };
void FUN_0030d0d0(int *arg0, void *arg1, int arg2) {
    int i;
    int hits;
    char *data;
    L *l;
    int n;
    l = ((O *)arg1)->l;
    data = l->data;
    n = l->count;
    hits = 0;
    if (arg2 == 0) {
        l->SetCount(0);
        ((VC *)arg1)->v100(((O *)arg1)->f12);
        *arg0 = DAT_004fb410[0];
    } else {
        for (i = 0; i < n; i++) {
            if (*data == 0) {
                hits++;
                if (hits == arg2) {
                    l->SetCount(i + 1);
                    *arg0 = DAT_004fb410[0];
                    return;
                }
            }
        }
        *arg0 = DAT_004fb418[0];
    }
}
