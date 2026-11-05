/* 0x003314a0
 * Returns the published default descriptor of igMemoryDescriptorMetaField: the cached instance that the
 * class's registration wrapper creates on first use (cell at 0x00586be0, the class
 * handle 0x00586bd8 plus 8, filled the same way as the descriptors in
 * list-metadata-access.c, finding 888). */
extern int g_igMemoryDescriptorMetaField_descriptor_00586be0[4];
int Gap__Core__igMemoryDescriptorMetaField__vfunc_23(void) {
    return g_igMemoryDescriptorMetaField_descriptor_00586be0[0];
}
