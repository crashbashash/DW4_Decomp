class V1 { public: virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59(); virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63(); virtual void v264(void *); };
class V2 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void *v220(unsigned int, int); };
struct O { char p72_[72]; unsigned int f72; int f76; void *f80; int f84; unsigned int f88; };
extern "C" {
V1 *FUN_00165cc0(...);
int FUN_001903d0(...);
int FUN_00191f30(...);
int Matrix44_SetTranslation(...);
void FUN_00165d30(O *arg0, unsigned int arg1, int arg2);
}
void FUN_00165d30(O *arg0, unsigned int arg1, int arg2) {
    int sp5C;
    int v[3];
    void *s0;
    unsigned int i;
    int off;
    int src;
    char *s1;

    arg0->f72 = arg1;
    arg0->f84 = arg2;
    if (arg0->f88 < arg1) {
        s0 = arg0->f80;
        if (s0 != 0) {
            FUN_00165cc0(arg0)->v264(s0);
            arg0->f80 = 0;
        }
        arg0->f80 = ((V2 *)FUN_00165cc0(arg0))->v220(arg1 << 6, 0x10);
        arg0->f88 = arg1;
    }
    s1 = (char *)arg0->f80;
    for (i = 0; i < arg1; i++) {
        off = i << 6;
        FUN_00191f30(&sp5C, s1, arg0->f84 + off);
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
        Matrix44_SetTranslation(s1, v);
        FUN_001903d0(s1);
        s1 += 0x40;
    }
    arg0->f76 = arg0->f76 + 1;
}
