/* 0x003312a0
 * Returns the published default descriptor of igLongMetaField: the cached instance that the
 * class's registration wrapper creates on first use (cell at 0x00586058, the class
 * handle 0x00586050 plus 8, filled the same way as the descriptors in
 * list-metadata-access.c, finding 888). */
extern int g_igLongMetaField_descriptor[4];
int Gap__Core__igLongMetaField__vfunc_23(void) {
    return g_igLongMetaField_descriptor[0];
}
