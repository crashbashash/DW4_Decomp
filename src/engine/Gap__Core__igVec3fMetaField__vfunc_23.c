/* 0x00193d70
 * Returns the published default descriptor of igVec3fMetaField: the cached instance that the
 * class's registration wrapper creates on first use (cell at 0x00560f78, filled the same
 * way as the descriptors in list-metadata-access.c, finding 888). */
extern int g_igVec3fMetaField_descriptor[4];
int Gap__Core__igVec3fMetaField__vfunc_23(void) {
    return g_igVec3fMetaField_descriptor[0];
}
