extern "C" int Gap__Sg__igCommonTraversal__vfunc_09(...);
extern "C" int igObject_Destroy(...);
struct R { int word0; int references; };
class V128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); };
struct O { char p0[28]; R *ref; char p1[196]; unsigned int flags; char p2[316]; V128 *v; };
extern R *DAT_00562760[4];
extern "C" void Gap__Sg__igFrustCullTraversal__vfunc_09(O *arg0, int arg1);
void Gap__Sg__igFrustCullTraversal__vfunc_09(O *arg0, int arg1) {
    R *s0;
    R *a0;
    Gap__Sg__igCommonTraversal__vfunc_09(arg0, arg1);
    if (arg1 == 0) {
        s0 = DAT_00562760[0];
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = arg0->ref;
        if (a0 != 0) {
            a0->references = a0->references - 1;
            if (((unsigned long long)(long long)a0->references & 0x7fffffULL) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->ref = s0;
        arg0->flags = arg0->flags | 0x200;
        arg0->v->vX(0);
    }
}
