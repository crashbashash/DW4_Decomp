/* published MetaObject accessor of Gap::Core::igSymbolTable. A 12-byte leaf (lui/lw) that returns
 * the class handle slot g_igSymbolTable_metaObject, the "published MetaObject slot" passed to
 * igMetaObject_RegisterClass in src/engine/igSymbolTable_Register.c; the same shape as
 * igObjectList_GetPublishedMetaObject (rule `published-accessor`). The slot is read through the
 * array extern so the load stays absolute. */
extern int g_igSymbolTable_metaObject[4];
int Gap__Core__igSymbolTable__vfunc_22(void) {
    return g_igSymbolTable_metaObject[0];
}
