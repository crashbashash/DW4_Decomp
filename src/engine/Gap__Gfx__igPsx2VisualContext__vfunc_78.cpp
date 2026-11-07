extern "C" {
struct E { char p[148]; unsigned char f148; char p2[11]; };
struct Lst { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; short *f12; E *f16; };
}
class Buf { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual int vB(short *p, int n); };
class Obj { public: virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59(); virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63(); virtual void a64(); virtual void a65(); virtual void a66(); virtual void a67(); virtual void a68(); virtual void a69(); virtual void a70(); virtual void a71(); virtual void a72(); virtual void a73(); virtual void a74(); virtual void a75(); virtual void a76(); virtual void vA(int a, int b); char pad[1332]; Lst *f1336; };
extern "C" Buf *Memory_FindBufferOwner(Lst *l);
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_78(Obj *arg0, int arg1);
void Gap__Gfx__igPsx2VisualContext__vfunc_78(Obj *arg0, int arg1) {
    E *e = arg0->f1336->f16 + arg1;
    Lst *l;
    if (e != 0 && e != 0) {
        if (e->f148 != 0) {
            arg0->vA(arg1, 0);
        }
        l = arg0->f1336;
        if (arg1 < l->f0 && arg1 >= 0) {
            if (l->f4 >= l->f2) {
                Buf *b = Memory_FindBufferOwner(l);
                l->f2 = l->f2 + 8;
                l->f12 = (short *)b->vB(l->f12, l->f2 * 2);
            }
            l->f12[l->f4] = arg1;
            l->f4 = l->f4 + 1;
        }
    }
}
