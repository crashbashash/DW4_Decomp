/* 0x00181070
 * Class-handle getter: vtable slot 46 of Gap::Core::igParticleFormat returns the metaobject slot of
 * igContextExt (global at 0x5868e8), not of igParticleFormat itself (see igContextExt_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igContextExt_metaObject_005868e8[4];
int Gap__Core__igParticleFormat__vfunc_46(void) {
    return g_igContextExt_metaObject_005868e8[0];
}
