/* Returns the metaobject slot of the sibling class igRefMetaField, not of igRegistry; read through
 * the array extern so the load stays absolute. */
extern int g_igRefMetaField_metaObject[4];
int Gap__Core__igRegistry__vfunc_46(void) {
    return g_igRefMetaField_metaObject[0];
}
