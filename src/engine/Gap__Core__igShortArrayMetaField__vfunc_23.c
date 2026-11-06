/* Returns the cached default descriptor of igShortArrayMetaField, the word 8 bytes after the class
 * handle. No lazy registration here (the lazy creator is FUN_002ba580). */
extern int g_igShortArrayMetaField_descriptor[4];
int Gap__Core__igShortArrayMetaField__vfunc_23(void) {
    return g_igShortArrayMetaField_descriptor[0];
}
