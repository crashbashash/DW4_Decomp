/* 0x00331350
 * Returns the published default descriptor of igFloatArrayMetaField: the cached instance that the
 * class's registration wrapper creates on first use (cell at 0x00586390, the class
 * handle 0x00586388 plus 8, filled the same way as the descriptors in
 * list-metadata-access.c, finding 888). */
extern int g_igFloatArrayMetaField_descriptor[4];
int Gap__Core__igFloatArrayMetaField__vfunc_23(void) {
    return g_igFloatArrayMetaField_descriptor[0];
}
