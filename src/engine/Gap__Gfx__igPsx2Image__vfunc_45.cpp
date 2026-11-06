struct S { char pad[24]; int f24; };
extern "C" bool Gap__Gfx__igPsx2Image__vfunc_45(S *p);
extern "C" bool Gap__Gfx__igPsx2Image__vfunc_45(S *p) {
    bool r = true;
    if (p->f24 == 0x64) {
        p->f24 = 0x66;
    } else if (p->f24 == 0x66) {
        p->f24 = 0x64;
    } else {
        r = false;
    }
    return r;
}
