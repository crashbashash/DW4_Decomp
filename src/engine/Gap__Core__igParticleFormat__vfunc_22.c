/* 0x00181060
 * Class-handle getter: vtable slot 22 of Gap::Core::igParticleFormat returns the cached metaobject
 * pointer in the global at 0x55fca0, the slot the class registration fills (see igParticleFormat_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igParticleFormat_metaObject_0055fca0[4];
int Gap__Core__igParticleFormat__vfunc_22(void) {
    return g_igParticleFormat_metaObject_0055fca0[0];
}
