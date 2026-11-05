/* 0x00331180
 * Returns the cached default descriptor of igRefMetaField, the word 8 bytes
 * after the class handle 0x585a60 (docs/engine/array-storage.md).  No lazy
 * registration here (the lazy creator is FUN_002bb930). */
extern int g_igRefMetaField_descriptor_00585a68[4];
int Gap__Core__igRegistry__vfunc_47(void) {
    return g_igRefMetaField_descriptor_00585a68[0];
}
