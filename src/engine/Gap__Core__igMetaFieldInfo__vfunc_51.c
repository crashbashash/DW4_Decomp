/* 0x002fc620
 * Class-handle getter: returns the cached metaobject pointer in the global at
 * 0x587190, the same global the field constructor 0x2fc630 reads for a field's
 * `_typeIndex` (finding 367, config/SLUS-20836/names/ObjectModel.tsv).  The getter idiom
 * matches the other `*_metaObject_<addr>` accessors in this folder. */
extern int g_igMetaFieldInfo_metaObject_00587190[4];
int Gap__Core__igMetaFieldInfo__vfunc_51(void) {
    return g_igMetaFieldInfo_metaObject_00587190[0];
}
