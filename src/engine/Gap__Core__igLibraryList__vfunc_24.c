/* Element-class getter: returns the metaobject slot of igLibrary, the class the list holds. Read
 * through the array extern so the load stays absolute. */
extern int g_igLibrary_metaObject[4];
int Gap__Core__igLibraryList__vfunc_24(void) {
    return g_igLibrary_metaObject[0];
}
