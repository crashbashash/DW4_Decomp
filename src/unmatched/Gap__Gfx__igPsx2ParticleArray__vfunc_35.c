void Gap__Gfx__igPsx2ParticleArray__vfunc_35(int *arg0, float fparg0) {
    *(float *)(arg0 + 6) = fparg0;
    if (arg0[20] & 2) {
        *(float *)(arg0[25] + 28) = fparg0;
        return;
    }
    *(int *)(arg0[25] + 28) = 0x7f800000;
}
