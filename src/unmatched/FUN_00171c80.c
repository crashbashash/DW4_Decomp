/* 0x00171c80 - FUN_00171c80. typed float member through a pointer member, forwarded argument; alternate compiler -O3 Verified byte-identical by tools/verify.py. */
typedef struct T { char pad64[64]; float f64; } T;
typedef struct S0 { char pad1344[1344]; T *f1344; } S0;
int FUN_00172330();
extern int DAT_00560908[4];
void FUN_00171c80(S0 *arg0, float fparg0) {
    if (arg0->f1344->f64 == fparg0) {
        DAT_00560908[0] += 1;
    }
    arg0->f1344->f64 = fparg0;
    FUN_00172330(arg0, arg0->f1344);
}
