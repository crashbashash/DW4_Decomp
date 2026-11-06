/* 0x00180ef0
 * Class-handle getter: vtable slot 22 of Gap::Core::igPrimLengthArray1_1 returns the cached metaobject
 * pointer in the global at 0x55fb00, the slot the class registration fills (see igPrimLengthArray1_1_Register.c).
 * Same accessor idiom as the other `*_metaObject_<addr>` getters in this folder; the array extern
 * keeps the load absolute. */
extern int g_igPrimLengthArray1_1_metaObject[4];
int Gap__Core__igPrimLengthArray1_1__vfunc_22(void) {
    return g_igPrimLengthArray1_1_metaObject[0];
}
