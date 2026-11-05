class M { public: char pad[28]; int f28; char pad2[12]; unsigned char f44; };
class R { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(M *); int refs; int f8; int f12; };
class B { public: char pad[24]; int f24; int f28; int f32; int f36; char pad40[8]; M *f48; };
class A { public: char pad[32]; R *obj; };
extern "C" {
int igObject_Destroy(...);
unsigned char FUN_003ae680(A *arg0, B *arg1, R *arg2);
}
unsigned char FUN_003ae680(A *arg0, B *arg1, R *arg2) {
    unsigned char var_v0;
    R *temp_a0;

    var_v0 = 0;
    if (arg0->obj == 0) {
        if (arg2 != 0) {
            arg2->refs = arg2->refs + 1;
        }
        temp_a0 = arg0->obj;
        if (temp_a0 != 0) {
            temp_a0->refs = temp_a0->refs - 1;
            if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->obj = arg2;
        arg0->obj->vX(arg1->f48);
        arg1->f48->f28 = arg0->obj->f12;
        arg1->f48->f44 = 0;
        arg1->f24 = 1;
        arg1->f36 = 0;
        arg1->f32 = 0;
        arg1->f28 = 0;
        arg1->f28 = 1;
        arg1->f36 = 0;
        arg1->f32 = 0;
        arg1->f32 = 1;
        arg1->f36 = 0;
        var_v0 = 1;
    }
    return var_v0;
}
