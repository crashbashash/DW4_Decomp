/* Vtable slot 22 (GetMetaObject): returns the first word of the igMessage class's metaobject
 * handle at 0x0056dad8 (class name from data/reflection.json; slot 22 is the metaobject accessor).
 * The receiver is not touched, so the function takes no parameters. */
extern int g_igMessage_metaObject[4];
int Gap__Core__igMessage__vfunc_22(void) {
    return g_igMessage_metaObject[0];
}
