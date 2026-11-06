/* Streams in a record's resource: loads it when none is held, otherwise refreshes it and marks the
 * shared header; returns whether the resource is ready; alternate compiler -O3; C++ bool result
 * (daddiu flag, no andi), byte flag at +28, shared header pointer loaded once. */
typedef struct Q { char p[20]; int f20; char p2[4]; unsigned char f28; } Q;
typedef struct R { int f0; Q *f4; int f8; int f12; int f16; int f20; } R;
typedef struct A1 { char p[16]; R *f16; } A1;
typedef struct Ob { char p[328]; A1 *f328; } Ob;
extern "C" {
int FUN_0016aea0(Ob *, int, int, int);
int FUN_001ea420(int);
int FUN_001ea430(int, int, int, int);
int FUN_001f05a0(int, int);
int FUN_0020b270(int);
int FUN_0020bb20(int *, int, int);
int FUN_0020c800(int);
extern int DAT_0048a4e0[4];
extern int DAT_0048a4ec[4];
}
extern "C" bool FUN_0016b090(Ob *arg0, int arg1);
extern "C" bool FUN_0016b090(Ob *arg0, int arg1) {
    int sp5C;
    bool v;
    int h;
    int r;
    R *s;
    Q *q;
    s = arg0->f328->f16 + arg1;
    v = true;
    if (s->f8 == 0 || s->f4->f28 != 0) {
        if (s->f8 != 0) {
            h = FUN_001ea420(s->f8);
            FUN_0020c800(h);
            FUN_001f05a0(2, FUN_0020b270(h));
            q = s->f4;
            q->f28 = 1;
            FUN_0016aea0(arg0, s->f12, s->f16, q->f20);
        } else {
            s->f8 = FUN_001ea430(DAT_0048a4e0[s->f12], 0, DAT_0048a4ec[0], s->f16);
        }
        s->f4->f28 = 0;
    }
    if (s->f20 != 5) {
        sp5C = FUN_001ea420(s->f8);
        v = FUN_0020bb20(&sp5C, 0, 0) != 0;
    }
    s->f20 = 4;
    return v;
}
