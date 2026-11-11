bool Gap__Gfx__igPsx2Image__vfunc_45(S_16f250 *p) {
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

