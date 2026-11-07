class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int v156(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual float *v180(int); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual unsigned char v240(); };
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_66(VC *arg0);
void Gap__Sg__igTransformSequence1_5__vfunc_66(VC *arg0) {
    int n, i; float *a; float *b; float dot;
    if (arg0->v240() & 2) {
        n = arg0->v156();
        for (i = 0; i < n - 1; i++) {
            a = arg0->v180(i);
            b = arg0->v180(i + 1);
            dot = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
            if (dot < -0.999989986f) {
                b[0] = -b[0]; b[1] = -b[1]; b[2] = -b[2]; b[3] = -b[3];
            }
        }
    }
}
