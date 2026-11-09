class V188 { public: virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual int v188(int *); };
class V96 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void v96(int *, int, int, int); };
struct O { char p0[24]; void *f24; char p28[364]; int f392; };
extern "C" {
int FUN_0015cb60(...);
int igObject_Destroy(...);
void FUN_00176a50(O *arg0, V96 *arg1, int *arg2, int arg3, int arg4);
}
struct R { int w0; int rc; };
void FUN_00176a50(O *arg0, V96 *arg1, int *arg2, int arg3, int arg4) {
    int sp6C;
    int temp_v1;
    R *a0;

    if (arg1 != 0) {
        ((R *)arg1)->rc = ((R *)arg1)->rc + 1;
    }
    a0 = (R *)arg0->f24;
    if (a0 != 0) {
        a0->rc = a0->rc - 1;
        if ((a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->f24 = arg1;
    if (((V188 *)arg0)->v188(arg2) == 0) {
        FUN_0015cb60(arg0, arg1, arg2, arg3, (arg4 & ~0x10) | 4);
        return;
    }
    sp6C = *arg2;
    if ((((unsigned int)(*arg2 & 0xF0000) >> 0x10) & 0xFF) == 1) {
        temp_v1 = sp6C & 0xFFF0FFFF;
        sp6C = temp_v1;
        sp6C = sp6C | 0x20000;
    }
    arg1->v96((int *)&sp6C, arg3, arg4 | 0x10, arg0->f392);
}
