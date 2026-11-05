/* 0x003313a0
 * Class-handle getter: vtable slot 22 of Gap::Core::igEventTracker returns the cached metaobject
 * pointer in the global at 0x586480,
 * the slot the class registration fills (see igEventTracker_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igEventTracker_metaObject_00586480[4];
int Gap__Core__igEventTracker__vfunc_22(void) {
    return g_igEventTracker_metaObject_00586480[0];
}
