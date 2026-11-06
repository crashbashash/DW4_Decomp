/* 0x003311a0
 * Returns the cached default descriptor of igRawRefArrayMetaField, the word 8
 * bytes after the class handle 0x585a90.  No lazy registration here (the
 * lazy creator is FUN_002bc000). */
extern int g_igRawRefArrayMetaField_descriptor[4];
int Gap__Core__igRawRefArrayMetaField__vfunc_23(void) {
    return g_igRawRefArrayMetaField_descriptor[0];
}
