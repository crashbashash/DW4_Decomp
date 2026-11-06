struct S;
extern "C" void Gap__Core__igPsx2VertexArray1_1__vfunc_45(struct S *arg0, int arg1, int arg2, float fparg0);
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned int * vX(); };

struct S : VC { char p[28]; float *f32; };
void Gap__Core__igPsx2VertexArray1_1__vfunc_45(S *arg0, int arg1, int arg2, float fparg0) {
    float *temp_s0 = arg0->f32;
    temp_s0[arg1 + arg2 * ((((*arg0->vX()) & 0xF0) >> 4) & 0xFF)] = fparg0;
}
