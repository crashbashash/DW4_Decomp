struct A { char pad[32]; int f; };
extern "C" int Gap__Gfx__igParticleArray__vfunc_13();
extern "C" void Gap__Bec__ParticleArray__vfunc_11(A *arg0) {
    Gap__Gfx__igParticleArray__vfunc_13();
    if (arg0->f == 0) {
        arg0->f = 0xB4;
    }
}
