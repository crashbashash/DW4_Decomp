/* Returns the metaobject slot of the sibling class igShortMetaField, not of igRegistryValueList;
 * read through the array extern so the load stays absolute. */
extern int g_igShortMetaField_metaObject[4];
int FUN_00331950(void) {
    return g_igShortMetaField_metaObject[0];
}
