/* 0x00331490: published MetaObject accessor of Gap::Core::igMemoryDescriptorMetaField.
 * A 12-byte leaf (lui/lw) that returns the class handle slot g_igMemoryDescriptorMetaField_metaObject_00586bd8,
 * the "published MetaObject slot" passed to igMetaObject_RegisterClass in
 * src/engine/igMemoryDescriptorMetaField_Register.c; the same shape as igObjectList_GetPublishedMetaObject
 * (rule `published-accessor`, docs/engine/naming.md). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igMemoryDescriptorMetaField_metaObject_00586bd8[4];
int Gap__Core__igMemoryDescriptorMetaField__vfunc_22(void) {
    return g_igMemoryDescriptorMetaField_metaObject_00586bd8[0];
}
