/* 0x001d0120
 * Metaobject accessor: returns the class handle of igGeometry (slot 0 of
 * g_igGeometry_metaObject), without the lazy registration of the *_GetMetaObject helpers. */
extern int g_igGeometry_metaObject[4];
int Gap__Sg__igGeometry__vfunc_22(void) {
    return g_igGeometry_metaObject[0];
}
