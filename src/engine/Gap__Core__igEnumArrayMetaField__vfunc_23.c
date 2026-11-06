/* 0x003313c0: igEnumArrayMetaField virtual getter 23.  Returns the type
 * descriptor object (the igEnumArrayMetaField instance that is created once from
 * the class metaobject at 0x005865b0 and finalised with igMetaField_FinalizeDescriptor
 * in FUN_002c6620).  Its class metaobject is returned by the preceding slot, vfunc_22. */
extern int g_igEnumArrayMetaField_descriptor[4];
int Gap__Core__igEnumArrayMetaField__vfunc_23(void) {
    return g_igEnumArrayMetaField_descriptor[0];
}
