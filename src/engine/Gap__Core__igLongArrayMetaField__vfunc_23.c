/* 0x003312c0
 * Returns the published default descriptor of igLongArrayMetaField: the cached instance that the
 * class's registration wrapper creates on first use (cell at 0x00586068, the class
 * handle 0x00586060 plus 8, filled the same way as the descriptors in
 * list-metadata-access.c, finding 888). */
extern int g_igLongArrayMetaField_descriptor[4];
int Gap__Core__igLongArrayMetaField__vfunc_23(void) {
    return g_igLongArrayMetaField_descriptor[0];
}
