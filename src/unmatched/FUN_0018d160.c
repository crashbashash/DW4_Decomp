struct A { char p[8]; float f8; float f12; float f16; };
struct B { char p[8]; float f8; float f12; float f16; float f20; };
int FUN_0018d0b0();
void FUN_0018d160(struct A *arg0, struct B *arg1) {
    float v[3];
    float t = arg1->f20;
    if (!(t < 0.0f)) {
        v[0] = arg1->f8 + t * arg0->f8;
        v[1] = arg1->f12 + t * arg0->f12;
        v[2] = arg1->f16 + t * arg0->f16;
        FUN_0018d0b0(arg0, v);
    }
}
