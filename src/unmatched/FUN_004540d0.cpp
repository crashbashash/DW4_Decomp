class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual float *vX(int); };
class V96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); char pad[20]; float f24; float f28; float f32; float f36; };
struct E { char pad[8]; V96 *f8; V92 *f12; };
struct L { char pad[8]; int count; char pad1[4]; E **data; };
struct S { char pad[8]; int f8; char pad1[28]; L *f40; };
extern "C" {
void FUN_004540d0(S *arg0);
}
void FUN_004540d0(S *arg0) {
    int i;
    E *e;
    float *v;
    V96 *o;

    for (i = 0; i < arg0->f40->count; i++) {
        e = arg0->f40->data[i];
        v = e->f12->vX(arg0->f8);
        o = e->f8;
        o->f24 = v[0];
        o->f28 = v[1];
        o->f32 = v[2];
        o->f36 = v[3];
        o->vX();
    }
}
