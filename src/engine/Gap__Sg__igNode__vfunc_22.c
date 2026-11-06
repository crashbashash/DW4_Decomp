/* 0x001c5b20
 * Metaobject accessor: returns the class handle of igNode (slot 0 of
 * g_igNode_metaObject), without the lazy registration of the *_GetMetaObject helpers. */
extern int g_igNode_metaObject[4];
int Gap__Sg__igNode__vfunc_22(void) {
    return g_igNode_metaObject[0];
}
