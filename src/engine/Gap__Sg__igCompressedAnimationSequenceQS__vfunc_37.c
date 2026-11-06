int igObject_Destroy();
struct R { int vt; unsigned int rc; };
struct S { char pad0[8]; struct R *p8; char pad1[44]; unsigned char f56; };

void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_37(struct S *arg0) {
    struct R *temp_a0;

    arg0->f56 = arg0->f56 & 0xFE;
    temp_a0 = arg0->p8;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if ((temp_a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->p8 = 0;
}
