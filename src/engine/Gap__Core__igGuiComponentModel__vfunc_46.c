/* 0x00458310
 * Metaobject accessor in the Gap::Core::igGuiComponentModel vtable that returns the cached
 * igMetaObject of igGeometryElement (global named below), not of igGuiComponentModel itself;
 * presumably the metaclass of its element/companion type (hypothesis, from
 * the global's name only). */
extern int g_igGeometryElement_metaObject[4];
int Gap__Core__igGuiComponentModel__vfunc_46(void) {
    return g_igGeometryElement_metaObject[0];
}
