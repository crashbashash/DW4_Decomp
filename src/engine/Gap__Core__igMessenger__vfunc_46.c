/* 0x00237010
 * Vtable slot 46 of the igMessenger vtable (0x0052cf20): returns the first word of
 * the igInfoManager metaobject handle at 0x0056dc38 (class name from
 * data/reflection.json).  Why igMessenger answers with igInfoManager's metaobject
 * is unproven; the vtable is attributed to igMessenger by its GetVTable accessor
 * (config/SLUS-20836/names/GetVTableSlots.tsv).  The receiver is not touched. */
extern int g_igInfoManager_metaObject_0056dc38[4];
int Gap__Core__igMessenger__vfunc_46(void) {
    return g_igInfoManager_metaObject_0056dc38[0];
}
