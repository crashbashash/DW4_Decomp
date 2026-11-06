/* 0x00331540
 * Class-handle getter: vtable slot 22 of Gap::Core::igPageMemoryPool returns the cached metaobject
 * pointer in the global at 0x586a30, the slot the class registration fills (see igPageMemoryPool_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igPageMemoryPool_metaObject[4];
int Gap__Core__igPageMemoryPool__vfunc_22(void) {
    return g_igPageMemoryPool_metaObject[0];
}
