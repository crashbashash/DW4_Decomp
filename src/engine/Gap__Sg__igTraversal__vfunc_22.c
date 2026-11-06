/* 0x001e2880
 * Metaobject accessor: returns the class handle of igTraversal (slot 0 of
 * g_igTraversal_metaObject), without the lazy registration of the *_GetMetaObject helpers. */
extern int g_igTraversal_metaObject[4];
int Gap__Sg__igTraversal__vfunc_22(void) {
    return g_igTraversal_metaObject[0];
}
