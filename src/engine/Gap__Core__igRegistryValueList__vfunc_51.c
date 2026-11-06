/* 0x00331960
 * Returns the cached default descriptor of igShortMetaField, the word 8 bytes
 * after the class handle 0x585948.  No lazy registration here (the lazy
 * creator is igShortMetaField_GetDefaultDescriptor). */
extern int g_igShortMetaField_descriptor[4];
int Gap__Core__igRegistryValueList__vfunc_51(void) {
    return g_igShortMetaField_descriptor[0];
}
