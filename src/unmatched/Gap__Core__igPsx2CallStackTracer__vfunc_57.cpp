extern "C" {
void *memset_(...);
int memset(...);
int FUN_0032ae00(...);
extern int DAT_004c2610[4];
extern int DAT_00587220[64];
extern int DAT_00587320[4];
}
class Tr { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual int v19(); };
struct S { int a, b, c, d; };
extern "C" void Gap__Core__igPsx2CallStackTracer__vfunc_57(Tr *self, int *out) {
    S s;
    unsigned int i;
    int v = self->v19();
    if (v == -1) {
        v = DAT_00587320[0];
    }
    memset(&s, 0, 16);
    i = 0;
    do {
        int t = DAT_00587220[i];
        if (t != 0) {
            FUN_0032ae00(t, &s);
        }
        i += 1;
    } while (i < 64);
    memset(out, 255, 84);
    out[0] = -1;
    out[1] = v - DAT_004c2610[0];
    out[2] = DAT_00587320[0] - DAT_004c2610[0];
    out[3] = s.d << 12;
    out[4] = s.b << 12;
    out[5] = -1;
}
